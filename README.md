# arLMM
Approximate Ridge Linear Mixed Models (arLMM)

Code for our UAI 2018 paper "Scalable Algorithms for Learning High-Dimensional Linear Mixed Models": https://arxiv.org/pdf/1803.04431.pdf

## Example: Fitting an LMM on randomly generated data
```matlab
% Generate synthetic data
n = 1000; % 1000 observations
p = 100;  % 100 fixed effects
d = 3;    % 3 random effects
m = 20;   % observations correspond to 20 groups
alpha = 1;% for generating approximately the same #observations per group
[X,y,Z,Beta,H,s2] = genCusData(n,p,d,m,alpha);

disp('Fitting the LMM ...')
[estBeta,~,~,estH,ests2,cr] = arLMM(X,y,Z);

disp('Real vs estimated random-effect covariances:')
disp(H); disp(estH)
pause(3);
disp('[Real_noise_var  Estimated_noise_var]:')
disp([s2 ests2]);
pause(3);
disp("Corr(Real_Beta,Estimated_Beta):" + num2str(corr(Beta,estBeta)));
```

The output would be like:
```
>> Example
Fitting the LMM ...
Real vs estimated random-effect covariances:
   11.6581    0.1008    2.1193
    0.1008    2.9977    1.6877
    2.1193    1.6877    7.0714

   11.7331    0.4766    6.9986
    0.4766    3.2664    2.1220
    6.9986    2.1220    8.1317

[Real_noise_var  Estimated_noise_var]:
    0.8800    0.9187

Corr(Real_Beta,Estimated_Beta):0.99933
```

## Installation

### Matlab/Octave Mex Plugin Compilation

To use the Matlab implementation, you will need to compile the SRHT mex plugin. Suppose that you are running Linux with the GCC C compiler, the compilation can be done by the following Matlab commands:
```
cd mex/
mex -v -g CFLAGS='-march=native -O3 -fPIC' srht.c tran_srht.c
```
Then, you obtain the compiled 'srht.mex*' plugin, and copy it into the parent directory. A pre-compiled plugin for 64-bit Linux is provided. Compilation for octave is similar:
```
cd mex/
mkoctfile --mex srht.c tran_srht.c
```

### For C/C++:
We used Matlab to generate a C shared library under c_dist/. The c_dist/MatlabRuntime.install is provided by Matlab 2017b which includes necessary runtime libraries.
