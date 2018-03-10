function [ Beta, c, Gamma, H, s2, cr ] = arLMM( X, y, Z, varargin )
% Approximate Ridge (L2-regularized) Linear Mixed Model (arLMM)
% Model Specification:
%    y ~ X*Beta + Z*Gamma + c*ones(n,1) + Noise, where
%      X:       feature matrix, each row corresponds to an observation
%      Beta:    fixed effects coefficients (spherical Gaussian, covariance
%               diagonal entries given by Phi
%      Z:       design matrix for the random effect
%      Gamma:   random effect coefficients
%      c:       fixed intercept
%
% Input variables are cells with each element corresponds to one class
%
% Optional:
%    maxiter: max number of iterations, (default:50)
%        phi: vector of diagonal elements of the covariance of Beta (Phi)
%        eps: approximation error, 0 for exact inference (default)
%
% Returns:
%    Beta, Gamma - estimated fixed- and rand-effect coefficients
%    c   - estimated intercept
%    H   - covariance of intraclass random-effect covariance
%    s2  - noise variance
%    cr  - the fraction of subsamples used
%
% Copyright (C) Zilong Tan (ztan@cs.duke.edu)
% 03/02/2018

p = size(X{1},2);
q = size(Z{1},2);
m = length(X);

opt = inputParser;
opt.addParameter( 'maxiter',  20,          @(x) floor(x) > 0 );
opt.addParameter( 'phi',      ones(p,1),   @(x) prod(size(x) == [p,1]) );
opt.addParameter( 'eps',      0,           @(x) isnumeric(x) & (x >= 0) );
opt.parse(varargin{:});
opt = opt.Results;

% Calculate the total number of observations
n  = 0; nj = zeros(m,1);
for j = 1:m
    nj(j) = size(Z{j},1);
    n = n + nj(j);
end

% Full matrices
XF = []; yF = []; ZF = [];
for j = 1:m
    XF = [XF; X{j}];
    yF = [yF; y{j}];
    ZF = blkdiag(ZF,Z{j});
end

s2 = 1; H  = eye(q); V  = cell(m,1);
Gamma = cell(m,1); err = cell(m,1);
c  = 0;
cr = 1;

% Compute the exact or approximate kernel
if opt.eps == 0
    K = XF*(opt.phi.*XF');
else
    % Assuming X is full-rank here, faster if low-rank and replace last
    % argument with the rank
    [K,A,nsamp,D,Idx] = approxKern(XF,opt.phi,opt.eps,min(size(XF)));
    pp = size(D,1);
    cr = nsamp/pp;
    ppones = ones(pp,1);
    XF = A'; % transformed data
    pos = 1;
    for j = 1:m
        X{j} = XF(pos:(pos+nj(j)-1),:);
        pos = pos + nj(j);
    end
end

for i = 1:opt.maxiter
    % Compute V
    VF = [];
    IVF = [];
    for j = 1:m
        V{j} = Z{j}*H*Z{j}';
        V{j}(1:nj(j)+1:end) = V{j}(1:nj(j)+1:end) + s2;
        VF  = blkdiag(VF,V{j});
        IVF = blkdiag(IVF,inv(V{j}));
    end
    % Estimate Beta
    T = inv(VF + K);
    rs = sum(IVF);
    ss = sum(sum(IVF));
    IVL = IVF - rs'/ss*rs;
    KIVL = K*IVL;
    KIVL(1:n+1:end) = KIVL(1:n+1:end) + 1;
    if opt.eps == 0
        Beta = opt.phi.*XF'*IVL/KIVL*yF;
    else
        Beta = A*IVL/KIVL*yF;
    end
    % Estimate c
    c = rs/ss*(yF-XF*Beta);
    % Estimate H
    G   = zeros(q,q);
    pos = 1;
    for j = 1:m
        Gamma{j} = H*Z{j}'*T(pos:(pos+nj(j)-1),:)*(yF-c);
        G = G + Gamma{j}*Gamma{j}' - ...
            H*Z{j}'*T(pos:(pos+nj(j)-1),pos:(pos+nj(j)-1))*Z{j}*H;
        pos = pos + nj(j);
    end
    H = H + G/m;
    % Estimate s2
    res = 0;
    for j = 1:m
        err{j} = y{j} - X{j}*Beta - Z{j}*Gamma{j} - c;
        res = res + sum(err{j}.^2);
    end
    s2 = s2 + (res - s2^2*trace(T))/n;
end

% Reconstruct the full Beta
if opt.eps > 0
    z = zeros(pp,1);
    z(Idx) = Beta;
    Beta = D.*SRHT(z,ppones,pp);
    Beta = Beta(1:p);
end

end
