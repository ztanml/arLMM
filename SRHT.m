function [ S, D, Idx ] = SRHT( X, D, m )
% Subsampled randomized Hadamard transform with m samples
%
% Optional:
%    D is the Rademacher vector to use. If not specified, create a new one
%
% Returns the transformed X and the Rademacher vector used
%
% Copyright (c) Zilong Tan (ztan@cs.duke.edu)
% 03/10/2018

[S, D, Idx] = srht(X, D, m);

Idx = Idx(1:m);
S = S(Idx,:);

end
