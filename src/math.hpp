/** \file
 * Wrapper around C mathematical functions.
 * $Id: math.hpp,v 1.2 2008/02/29 20:48:00 mina86 Exp $
 */
#ifndef H_MATH_HPP
#define H_MATH_HPP

#include "config.hpp"

#include <stdlib.h>
#include <math.h>


namespace calc {

/**
 * Namespace cotnaining a wrappers around C mathematical functions.
 * Those are overloaded functions which take either <tt>long
 * double</tt> or \c double argument and call apropriet C function.
 * If underlying implementation does not have a <tt>long double</tt>
 * variants of mathematical functions only versions for \c double
 * types are provided.
 *
 * An exception is ator function which comes in only one version
 * taking a poiter to const char and returning either <tt>long
 * double</tt> or \c double depending if \c strtold function is
 * available.
 */
namespace m {
#if HAVE_LONG_DOUBLE_FUNCTIONS
	inline long double abs  (long double x) { return ::fabsl (x); }

	inline long double pow  (long double x, long double y) {
		return ::powl  (x, y);
	}
	inline long double sqrt (long double x) { return ::sqrtl (x); }
	inline long double cbrt (long double x) { return ::cbrtl (x); }
	inline long double exp  (long double x) { return ::expl  (x); }
	inline long double log  (long double x) { return ::logl  (x); }
	inline long double log10(long double x) { return ::log10l(x); }
	inline long double log2 (long double x) { return ::log2l (x); }

	inline long double cos  (long double x) { return ::cosl  (x); }
	inline long double sin  (long double x) { return ::sinl  (x); }
	inline long double tan  (long double x) { return ::tanl  (x); }
	inline long double acos (long double x) { return ::acosl (x); }
	inline long double asin (long double x) { return ::asinl (x); }
	inline long double atan (long double x) { return ::atanl (x); }
	inline long double atan (long double x, long double y) {
		return ::atan2l(x, y);
	}

	inline long double cosh (long double x) { return ::coshl (x); }
	inline long double sinh (long double x) { return ::sinhl (x); }
	inline long double tanh (long double x) { return ::tanhl (x); }
	inline long double acosh(long double x) { return ::acoshl(x); }
	inline long double asinh(long double x) { return ::asinhl(x); }
	inline long double atanh(long double x) { return ::atanhl(x); }

	inline long double ator (const char *str) { return strtold(str, 0); }
#else

#  if HAVE_LONG_DOUBLE
	inline long double abs  (long double x) { return x < 0 ? -x : x}
#  endif

	inline double ator (const char *str) { return strtod(str, 0); }
#endif

	inline double abs  (double x) { return ::fabs  (x); }

	inline double pow  (double x, double y) { return ::pow  (x, y); }
	inline double sqrt (double x) { return ::sqrt  (x); }
	inline double cbrt (double x) { return ::cbrt  (x); }
	inline double exp  (double x) { return ::exp   (x); }
	inline double log  (double x) { return ::log   (x); }
	inline double log10(double x) { return ::log10 (x); }
	inline double log2 (double x) { return ::log2  (x); }

	inline double cos  (double x) { return ::cos   (x); }
	inline double sin  (double x) { return ::sin   (x); }
	inline double tan  (double x) { return ::tan   (x); }
	inline double acos (double x) { return ::acos  (x); }
	inline double asin (double x) { return ::asin  (x); }
	inline double atan (double x) { return ::atan  (x); }
	inline double atan (double x, double y) { return ::atan2 (x, y); }

	inline double cosh (double x) { return ::cosh  (x); }
	inline double sinh (double x) { return ::sinh  (x); }
	inline double tanh (double x) { return ::tanh  (x); }
	inline double acosh(double x) { return ::acosh (x); }
	inline double asinh(double x) { return ::asinh (x); }
	inline double atanh(double x) { return ::atanh (x); }
}

}


#endif
