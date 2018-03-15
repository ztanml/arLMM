/* The MIT License

   Copyright (C) 2017 Zilong Tan (eric.zltan@gmail.com)

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include <math.h>
#include "tran_srht.h"

#define _swap(a, b)							\
  do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

#define RAND_NR_DOUBLE(x)			\
  (5.42101086242752217E-20 * (x))

#define RAND_XORSHIFT(x, a, b, c) do {		\
    (x) ^= (x) << (a);				\
    (x) ^= (x) >> (b);				\
    (x) ^= (x) << (c);				\
  } while (0)

#define RAND_XORSHIFT64(x) RAND_XORSHIFT(x, 21, 35, 4)

#define RAND_SAMPLE(_n, _r, _buf, _seed) do {		\
    int64_t _i, _k, _pop = (_n);			\
    uint64_t _rn = (_seed);				\
    for (_i = (int64_t)(_r), _k = 0; _i >= 0; --_i) {	\
      RAND_XORSHIFT64(_rn);				\
      double _z = 1., _x = RAND_NR_DOUBLE(_rn);		\
      while (_x < _z) _z -= _z * _i / (_pop--);		\
      if (_k != (int64_t)(_n) - _pop - 1)		\
	_swap((_buf)[_k], (_buf)[(_n) - _pop - 1]);	\
      ++_k;						\
    }							\
  } while (0)

#define RAND_INT_MIX64(h) ({			\
      (h) += ~((h) << 32);			\
      (h) ^= ((h) >> 22);			\
      (h) += ~((h) << 13);			\
      (h) ^= ((h) >> 8);			\
      (h) += ((h) << 3);			\
      (h) ^= ((h) >> 15);			\
      (h) += ~((h) << 27);			\
      (h) ^= ((h) >> 31); })

static inline void 
_srht_vec(const double *in, const double *d, double *out, size_t n)
{
	size_t u;

	if (n == 0)
		return;
	if (n == 1)
		*out = *d * *in;
	else {
		n >>= 1;
		_srht_vec(in, d, out, n);
		_srht_vec(in + n, d + n, out + n, n);
		for (u = 0; u < n; ++u) {
			out[u] += out[u + n];
			out[u + n] = out[u] - 2*out[u + n];
		}
	}
}

int srht(const double *X, const double *rin,
	 size_t m, size_t n, size_t p, uint64_t seed,
	 double *S, double *rout, double *idx )
{
	uint64_t rnum;
	size_t written, u;
	double c = 1.0 / sqrt(m);
	int i;

	if (n & (n-1))
		return -1;

	// Randomize the seed
	RAND_INT_MIX64(seed);

	// Create Rademacher vector if not given
	if (rin == NULL) {
		for (written = 0; written < n;) {
			RAND_XORSHIFT64(seed);
			rnum = seed;
			for (i = 0; i < 64 && written < n; ++i, ++written) {
				rout[written] = (((int64_t)(rnum & 1) << 1) - 1) * c;
				rnum >>= 1;
			}
		}
	} else {
		for (u = 0; u < n; ++u)
			rout[u] = rin[u];
	}

	for (written = 0, u = 0;
	     u < p; ++u, written += n) {
		_srht_vec(X + written, rout, S + written, n);
	}

	RAND_SAMPLE(n, m, idx, seed);

	return 0;
}
