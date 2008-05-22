/** \file
 * Wrapper around C mathematical functions.
 * $Id: math.hpp,v 1.7 2008/05/22 13:44:09 mina86 Exp $
 */
#ifndef H_MATH_HPP
#define H_MATH_HPP

#include "config.hpp"

#include <stdlib.h>
#include <math.h>

/* We must use boost library under Windows, through lack of many
 * many functions.
 */
#ifdef _WIN32
#include <boost/math/complex.hpp>
#endif

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
	static inline long double abs  (long double x) { return ::fabsl (x); }

	static inline long double pow  (long double x, long double y) {
		return ::powl  (x, y);
	}
	static inline long double sqrt (long double x) { return ::sqrtl (x); }
	static inline long double exp  (long double x) { return ::expl  (x); }
	static inline long double log  (long double x) { return ::logl  (x); }
	static inline long double log  (long double x, long double y) {
		return ::log(x) / ::log(y);
	}
	static inline long double log10(long double x) { return ::log10l(x); }


	static inline long double cos  (long double x) { return ::cosl  (x); }
	static inline long double sin  (long double x) { return ::sinl  (x); }
	static inline long double tan  (long double x) { return ::tanl  (x); }
	static inline long double acos (long double x) { return ::acosl (x); }
	static inline long double asin (long double x) { return ::asinl (x); }
	static inline long double atan (long double x) { return ::atanl (x); }
	static inline long double atan (long double x, long double y) {
		return ::atan2l(x, y);
	}

	static inline long double cosh (long double x) { return ::coshl (x); }
	static inline long double sinh (long double x) { return ::sinhl (x); }
	static inline long double tanh (long double x) { return ::tanhl (x); }

#  ifdef _WIN32
	static inline long double cbrt (long double x) {
		return ::powl (x, 1.0/3.0);
	}
	static inline long double log2 (long double x) {
#    if defined M_LN2l
		return ::logl(x)/M_LN2l;
#    elif defined M_LN2
		return ::logl(x)/M_LN2;
#    else
		return ::logl(x)/::logl(2.0);
#    endif
	}

	static inline long double acosh(long double x) {
		return boost::math::acosh<long double>(x).real();
	}
	static inline long double asinh(long double x) {
		return boost::math::asinh<long double>(x).real();
	}
	static inline long double atanh(long double x) {
		return boost::math::atanh<long double>(x).real();
	}

	static inline long double ator (const char *str, char **end = 0) {
		return strtod(str, end);
	}
#  else
	static inline long double cbrt (long double x) { return ::cbrtl (x); }
	static inline long double log2 (long double x) { return ::log2l (x); }

	static inline long double acosh(long double x) { return ::acoshl(x); }
	static inline long double asinh(long double x) { return ::asinhl(x); }
	static inline long double atanh(long double x) { return ::atanhl(x); }

	static inline long double ator (const char *str, char **end = 0) {
		return strtold(str, end);
	}
#  endif
#else

#  if HAVE_LONG_DOUBLE
	static inline long double abs  (long double x) { return x < 0 ? -x : x; }
#  endif

	static inline double ator (const char *str, char **end = 0) {
		return strtod(str, end);
	}
#endif

	static inline double abs  (double x) { return ::fabs  (x); }

	static inline double pow  (double x, double y) { return ::pow  (x, y); }
	static inline double sqrt (double x) { return ::sqrt  (x); }
	static inline double exp  (double x) { return ::exp   (x); }
	static inline double log  (double x) { return ::log   (x); }
	static inline double log  (double x, double y) {
		return ::log(x) / ::log(y);
	}
	static inline double log10(double x) { return ::log10 (x); }

	static inline double cos  (double x) { return ::cos   (x); }
	static inline double sin  (double x) { return ::sin   (x); }
	static inline double tan  (double x) { return ::tan   (x); }
	static inline double acos (double x) { return ::acos  (x); }
	static inline double asin (double x) { return ::asin  (x); }
	static inline double atan (double x) { return ::atan  (x); }
	static inline double atan (double x, double y) { return ::atan2 (x, y); }

	static inline double cosh (double x) { return ::cosh  (x); }
	static inline double sinh (double x) { return ::sinh  (x); }
	static inline double tanh (double x) { return ::tanh  (x); }

#  ifdef _WIN32
	static inline double cbrt (double x) { return ::pow (x, 1.0/3.0); }
	static inline double log2 (double x) {
#    if defined M_LN2
		return ::log(x)/M_LN2;
#    else
		return ::log(x)/::log(2.0);
#    endif
	}

	static inline double acosh(double x) {
		return boost::math::acosh<double>(x).real();
	}
	static inline double asinh(double x) {
		return boost::math::asinh<double>(x).real();
	}
	inline double atanh(double x) {
		return boost::math::atanh<double>(x).real();
	}
#  else
	static inline double cbrt (double x) { return ::cbrt (x); }
	static inline double log2 (double x) { return ::log2 (x); }

	static inline double acosh(double x) { return ::acosh (x); }
	static inline double asinh(double x) { return ::asinh (x); }
	static inline double atanh(double x) { return ::atanh (x); }
#  endif
}

}


#endif
