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
 * Calculator functions.
 */
#ifndef H_FUNCTIONS_HPP
#define H_FUNCTIONS_HPP

#include "config.hpp"

#include "function.hpp"


namespace calc {

struct Environment;

/** Namespace for built in functions. */
namespace builtin {


/** Internal namespace. */
namespace _ {

/** An built in function class. */
struct Function : public calc::Function {
	virtual void free();
};

/** An one or two argument built in function class. */
struct OneOrTwoArgFunction : public Function {
	virtual bool argumentsCountOK(unsigned count) const;
};

/** An one argument built in function class. */
struct OneArgFunction : public Function {
	virtual bool argumentsCountOK(unsigned count) const;
};

/** At least one argument built in function class. */
struct OneOrMoreArgFunction : public Function {
	virtual bool argumentsCountOK(unsigned count) const;
};

}

/**
 * Defines a built in function class with name \a func and acepting
 * number of arguments specified by \a acount where it may be
 * <tt>One</tt>, <tt>OneOrTwo</tt> or <tt>OneOrMoree</tt>.
 */
#define CALC_FUNC(func, acount) \
	struct func : public _:: acount ##ArgFunction { \
		real execute(Environment &env, const Arguments &args) const; \
		static func *get() { static func singleton; return &singleton; } \
	}

	CALC_FUNC(sqrt  , One);
	CALC_FUNC(cbrt  , One);
	CALC_FUNC(exp   , One);
	CALC_FUNC(log   , OneOrTwo);
	CALC_FUNC(log10 , One);
	CALC_FUNC(log2  , One);
	CALC_FUNC(cos   , One);
	CALC_FUNC(sin   , One);
	CALC_FUNC(tan   , One);
	CALC_FUNC(cosh  , One);
	CALC_FUNC(sinh  , One);
	CALC_FUNC(tanh  , One);
	CALC_FUNC(acos  , One);
	CALC_FUNC(asin  , One);
	CALC_FUNC(atan  , OneOrTwo);
	CALC_FUNC(acosh , One);
	CALC_FUNC(asinh , One);
	CALC_FUNC(atanh , One);
	CALC_FUNC(min   , OneOrMore);
	CALC_FUNC(max   , OneOrMore);
	CALC_FUNC(avg   , OneOrMore);
	CALC_FUNC(Break , OneOrTwo);
	CALC_FUNC(Return, OneOrTwo);
	CALC_FUNC(print , One);

#undef CALC_FUNC


struct read : public _::Function {
	virtual bool argumentsCountOK(unsigned count) const;
	real execute(Environment &env, const Arguments &args) const;
	static read *get() { static read singleton; return &singleton; }
};



}

}

#endif
