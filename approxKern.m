function [ K, A, nsamp, D, Idx ] = approxKern( X, phi, eps, r, nsamp )
% Compute the approximate kernel K \approx X*(phi.*X') = A*A'
%
% X is the n-by-p covariate matrix
% phi is the p-by-1 vector of diagonal entries of the prior covariance of beta
% eps >= 0 specifies the SRHT approximation error (0 means exact inference)
% r specifies the rank of X which can be set to min(size(X))
%
% Optional:
%    nsamp: if specified, ignores eps; otherwise, compute nsamp from eps
%
% Copyright (c) Zilong Tan (ztan@cs.duke.edu)
% 03/10/2018

n = size(X,1);

if nargin < 3
    r = n;
end

p  = size(X,2);
pp = 2^ceil(log(p)/log(2));

% Append some zero columns to have a power of two columns
X = [X zeros(n,pp - p)];
Gamma = [phi; zeros(pp-p,1)];

% use specified nsamp
if nargin < 5
    nsamp = ceil(6*(sqrt(r) + sqrt(8*log(r*pp)))^2*log(r)/eps^2);
    nsamp = min(pp,nsamp);
end

rv = 2*(rand(pp,1) > 0.5) - 1;
ss = rv.*sqrt(Gamma)/sqrt(nsamp);
[A,D,Idx]  = SRHT(X',ss,nsamp);
K  = A'*A;

end
