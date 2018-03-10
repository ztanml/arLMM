# arLMM
Approximate Ridge Linear Mixed Models (arLMM)

## Installation

To use the Matlab implementation, you will need to compile the SRHT mex plugin. Suppose that you are running Linux with the GCC C compiler, the compilation can be done by the following Matlab commands:
```
cd mex/
mex -v -g CFLAGS='-march=native -O3 -fPIC' srht.c tran_srht.c
```
Then, you obtain the compiled 'srht.mex*' plugin, and copy it into the parent directory. A pre-compiled plugin for 64-bit Linux is provided.
