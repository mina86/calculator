/*
 * Copyright 2008-2009 by Michal Nazarewicz (mina86/AT/mina86.com)
 *                     by Jakub Ksiezniak
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

/** \file
 * A configuration file which should be modified accordingly to host's
 * C++ implementation.
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
