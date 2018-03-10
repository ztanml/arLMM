function [ y, Gamma ] = lmmGen( X, Z, Beta, H, sigma )
% Generate samples from an LMM.
%
% X is an array of features for each group, X{i} is the feature matrix of
%   group i
% Z is an array of design matrices for each group
% y is also an array of the responses for each group
% Beta, H, sigma are LMM parameters
%
% Copyright (c) Zilong Tan (ztan@cs.duke.edu)
% 03/10/2018

m = length(X);
y = cell(m,1);

Gamma = cell(m,1);

for i = 1:m
    Gamma{i} = mvnrnd(zeros(1,size(H,1)),H)';
end

for i = 1:m
    ni = size(X{i},1);
    y{i} = X{i}*Beta + Z{i}*Gamma{i} + sigma*randn(ni,1);
end

end
