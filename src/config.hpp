/** \file
 * A configuration file which should be modified accordingly to host's
 * C++ implementation.
 * $Id: config.hpp,v 1.3 2008/04/12 02:03:34 mina86 Exp $
 */

#ifndef H_CONFIG_HPP
#define H_CONFIG_HPP

/**
 * Whether C++ implementation support a <tt>long double</tt> type.  If
 * this is set to non-zero value program will use <tt>long double</tt>
 * type to store and manipulate values thus increasing precision.  If
 * it is set to zero program will use \c double type for that.
 */
#define HAVE_LONG_DOUBLE 1

/**
 * Whether C++ implementation has mathematical functions operating on
 * long double values such as powl, sqrtl, etc.  If this is set to
 * non-zero value program will use those functions and thus increase
 * precision of implemented functions, otherwise functions taking \c
 * double argument and returning \a double value will be used.
 */
#define HAVE_LONG_DOUBLE_FUNCTIONS 1


#if !HAVE_LONG_DOUBLE
#  if HAVE_LONG_DOUBLE_FUNCTIONS
#    undef HAVE_LONG_DOUBLE_FUNCTIONS
#  endif
#else
#  if HAVE_LONG_DOUBLE_FUNCTIONS
/** Defined so taht <tt>stdlib.h</tt> will provide \c strtold prototype. */
#    define _XOPEN_SOURCE 600  /* for strtold */
#  endif
#endif


/**
 * Namespace containing implementation of calculator's lexer,
 * mathematical gunctions, etc.
 */
namespace calc {

/** Type used to store floating point values. */
#if HAVE_LONG_DOUBLE
#  if __GNUC__
	__extension__
#  endif
	typedef long double real;
#else
	typedef double real;
#endif

}

#endif
