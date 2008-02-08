/** \file
 * Wrapper around C mathematical functions.  Depending on value of \C
 * HAVE_LONG_DOUBLE_FUNCTIONS functions defined here call either
 * a <tt>long double</tt> or <tt>double</tt> versions of mathematical
 * functions from C library.
 * $Id: math.hpp,v 1.1 2008/02/08 21:47:32 mina86 Exp $
 */
#ifndef H_MATH_HPP
#define H_MATH_HPP

#include "config.hpp"

#include <stdlib.h>
#include <math.h>


namespace calc {
#if HAVE_LONG_DOUBLE_FUNCTIONS
	inline real pow  (real x, real y) { return ::powl  (x, y); }
	inline real sqrt (real x) { return ::sqrtl (x); }
	inline real cbrt (real x) { return ::cbrtl (x); }
	inline real exp  (real x) { return ::expl  (x); }
	inline real log  (real x) { return ::logl  (x); }
	inline real log10(real x) { return ::log10l(x); }
	inline real log2 (real x) { return ::log2l (x); }

	inline real cos  (real x) { return ::cosl  (x); }
	inline real sin  (real x) { return ::sinl  (x); }
	inline real tan  (real x) { return ::tanl  (x); }
	inline real acos (real x) { return ::acosl (x); }
	inline real asin (real x) { return ::asinl (x); }
	inline real atan (real x) { return ::atanl (x); }
	inline real atan2(real x, real y) { return ::atan2l(x, y); }

	inline real cosh (real x) { return ::coshl (x); }
	inline real sinh (real x) { return ::sinhl (x); }
	inline real tanh (real x) { return ::tanhl (x); }
	inline real acosh(real x) { return ::acoshl(x); }
	inline real asinh(real x) { return ::asinhl(x); }
	inline real atanh(real x) { return ::atanhl(x); }

	inline real ator (const char *str) { return strtold(str, 0); }
#else
	inline real pow  (real x, real y) { return ::pow  (x, y); }
	inline real sqrt (real x) { return ::sqrt  (x); }
	inline real cbrt (real x) { return ::cbrt  (x); }
	inline real exp  (real x) { return ::exp   (x); }
	inline real log  (real x) { return ::log   (x); }
	inline real log10(real x) { return ::log10 (x); }
	inline real log2 (real x) { return ::log2  (x); }

	inline real cos  (real x) { return ::cos   (x); }
	inline real sin  (real x) { return ::sin   (x); }
	inline real tan  (real x) { return ::tan   (x); }
	inline real acos (real x) { return ::acos  (x); }
	inline real asin (real x) { return ::asin  (x); }
	inline real atan (real x) { return ::atan  (x); }
	inline real atan2(real x, real y) { return ::atan2 (x, y); }

	inline real cosh (real x) { return ::cosh  (x); }
	inline real sinh (real x) { return ::sinh  (x); }
	inline real tanh (real x) { return ::tanh  (x); }
	inline real acosh(real x) { return ::acosh (x); }
	inline real asinh(real x) { return ::asinh (x); }
	inline real atanh(real x) { return ::atanh (x); }

	inline real ator (const char *str) { return strtod(str, 0); }
#endif
}


#endif
