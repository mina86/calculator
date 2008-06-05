/** \file
 * Calculator functions implementation.
 * $Id: functions.cpp,v 1.8 2008/06/05 20:37:20 mina86 Exp $
 */
#ifndef H_VARIABLES_HPP
#define H_VARIABLES_HPP

#include "functions.hpp"
#include "exceptions.hpp"
#include "math.hpp"
#include "environment.hpp"

#include <algorithm>
#include <vector>

namespace calc {

namespace builtin {


namespace _ {

void Function::free() { }

bool OneArgFunction::argumentsCountOK(unsigned count) const {
	return count == 1;
}

bool OneOrTwoArgFunction::argumentsCountOK(unsigned count) const {
	return count == 1 || count == 2;
}

bool OneOrMoreArgFunction::argumentsCountOK(unsigned count) const {
	return count >= 1;
}

}


/**
 * Defines a virtual execute() method for class \a func which accepts
 * one argument and calls \a m::func function.
 */
#define CALC_FUNC(func) \
	real func::execute(Environment &env, const Arguments &args) const { \
		(void)env; throwIfArgumentsCountNotOK(args.size()); \
		return m::func(args[0]); \
	}

	CALC_FUNC(sqrt )
	CALC_FUNC(cbrt )
	CALC_FUNC(exp  )
	CALC_FUNC(log10)
	CALC_FUNC(log2 )
	CALC_FUNC(cos  )
	CALC_FUNC(sin  )
	CALC_FUNC(tan  )
	CALC_FUNC(cosh )
	CALC_FUNC(sinh )
	CALC_FUNC(tanh )
	CALC_FUNC(acos )
	CALC_FUNC(asin )
	CALC_FUNC(acosh)
	CALC_FUNC(asinh)
	CALC_FUNC(atanh)

#undef CALC_FUNC

/**
 * Defines a virtual execute() method for class \a func which accepts
 * one or two arguments and calls \a m::func function.
 */
#define CALC_FUNC(func) \
	real func::execute(Environment &env, const Arguments &args) const { \
		(void)env; \
		switch (args.size()) { \
		case 1: return m::func(args[0]); \
		case 2: return m::func(args[0], args[1]); \
		default: throw InvalidNumberOfArguments(); \
		} \
	}

	CALC_FUNC(log  )
	CALC_FUNC(atan )

#undef CALC_FUNC



real min::execute(Environment &env, const Arguments &args) const {
	Arguments::size_type size = args.size();
	(void)env; throwIfArgumentsCountNotOK(size);
	return *std::min_element(args.begin(), args.end());
}

real max::execute(Environment &env, const Arguments &args) const {
	Arguments::size_type size = args.size();
	(void)env; throwIfArgumentsCountNotOK(size);
	return *std::max_element(args.begin(), args.end());
}

real avg::execute(Environment &env, const Arguments &args) const {
	Arguments::size_type size = args.size();
	(void)env; throwIfArgumentsCountNotOK(size); \
	const real *it = &args[0];
	real val = *it;
	while (--size) {
		val += *++it;
	}
	return val / args.size();
}


}

}
#endif
