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

#ifndef _TRAN_SRHT_H
#define _TRAN_SRHT_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/** 
 * srht - Apply subsampled randomized Hadamard transform
 * @X:    n-by-p data matrix buffer
 * @S:    n-by-p transformed matrix buffer, but users will only use m
 *        rows of S indexed by idx
 * @rin:  Rademacher vector, NULL to generate a new one
 * @rout: Rademacher vector used, copied from rin, if rin is not NULL
 * @idx:  n-element subsampling indexes, contains 0 to n-1, and the first
 *        m elements are the selected indexes
 */
extern int srht(const double *X, const double *rin,
		size_t m, size_t n, size_t p, uint64_t seed,
		double *S, double *rout, double *idx );

#ifdef __cplusplus
}
#endif

#endif /* _TRAN_SRHT_H */
