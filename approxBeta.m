function [ Beta, c, cr ] = approxBeta( X, y, V, phi, eps, r )
% Compute the approximate Beta
% X is the n-by-p covariate matrix
% y is the n-by-1 response vector
% V is the n-by-n estimated marginal covariance
% phi is the p-by-1 vector of diagonal entries of the prior covariance of beta
% eps >= 0 specifies the SRHT approximation error (0 means exact inference)
% r specifies the rank of X which can be set to min(size(X))
% 
% Copyright (c) Zilong Tan (ztan@cs.duke.edu)
% 03/10/2018

n = size(X,1);

IV = inv(V);
rs = sum(IV);
ss = sum(rs);
IVL = IV - rs'/ss*rs;

[K,A,nsamp,D,Idx] = approxKern(X,phi,eps,r);
pp = size(D,1);
cr = nsamp/pp;
z  = zeros(pp,1);
KIVL = K*IVL;
KIVL(1:n+1:end) = KIVL(1:n+1:end) + 1;
z(Idx) = A*IVL/KIVL*y;
c = rs/ss*(y-A'*z(Idx));
Beta = D.*SRHT(z,ones(pp,1),pp);
Beta = Beta(1:size(X,2));

end
