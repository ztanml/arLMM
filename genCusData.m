function [X, y, Z, Beta, H, s2] = genCusData(n,p,d,m,alpha)
% Sample from an LMM with given parameters.
%
% Copyright (c) Zilong Tan (ztan@cs.duke.edu)
% 03/10/2018

% set random group sizes
nj = round(n*drchrnd(ones(1,m)*alpha,1))';
nj(end) = n - sum(nj(1:end-1));

X = cell(m,1);
for j = 1:m
    X{j} = randn(nj(j),p);
end

Z = cell(m,1);
for j = 1:m
    Z{j} = rand(nj(j),d);
end

Beta = randn(p,1);

H = randn(d,d);
H = H*H';

s2 = rand()*d;
y = lmmGen(X,Z,Beta,H,sqrt(s2));

end
