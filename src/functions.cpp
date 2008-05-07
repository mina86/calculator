/** \file
 * Calculator functions implementation.
 * $Id: functions.cpp,v 1.5 2008/05/07 17:54:28 mina86 Exp $
 */
#ifndef H_VARIABLES_HPP
#define H_VARIABLES_HPP

#include "functions.hpp"
#include "exceptions.hpp"
#include "math.hpp"

#include <vector>

namespace calc {
bool BuiltInFunction::argumentsCountOK(unsigned count) const {
    return minArgs <= count && count <= maxArgs;
}

void BuiltInFunction::free() { }


#define CALC_FUNC_PASS(func) \
	real Func_ ## func::execute(Environment &env, const Arguments &args)\
		const {															\
		(void)env; /* silence warning */								\
		throwIfArgumentsCountNotOK(args.size());						\
		return m::func(args[0]);										\
	}

CALC_FUNC_PASS(sqrt)
CALC_FUNC_PASS(cbrt)
CALC_FUNC_PASS(exp)

real Func_log::execute(Environment &env, const Arguments &args) const {
	(void)env;
	switch (args.size()) {
	case  1: return m::log(args[0]);
	case  2: return m::log(args[0]) / m::log(args[1]);
	default: throw InvalidNumberOfArguments();
	}
}

CALC_FUNC_PASS(log10)
CALC_FUNC_PASS(log2)
CALC_FUNC_PASS(cos)
CALC_FUNC_PASS(sin)
CALC_FUNC_PASS(tan)
CALC_FUNC_PASS(acos)
CALC_FUNC_PASS(asin)

real Func_atan::execute( Environment &env, const Arguments &args ) const {
	(void)env; /* silence warning */
	switch (args.size()) {
	case  1: return m::atan (args[0]);
	case  2: return m::atan (args[0], args[1]);
	default: throw InvalidNumberOfArguments();
	}
}

CALC_FUNC_PASS(cosh)
CALC_FUNC_PASS(sinh)
CALC_FUNC_PASS(tanh)
CALC_FUNC_PASS(acosh)
CALC_FUNC_PASS(asinh)
CALC_FUNC_PASS(atanh)

real Func_max::execute( Environment &env, const Arguments &args ) const {
	(void)env; /* silence warning */
	Arguments::size_type size = args.size();
	throwIfArgumentsCountNotOK(size);
	const real *it = &args[0];
	real val = *it;
	while (--size) {
		const real v = *++it;
		if (v > val) val = v;
	}
	return val;
}

real Func_min::execute( Environment &env, const Arguments &args ) const {
	(void)env; /* silence warning */
	Arguments::size_type size = args.size();
	throwIfArgumentsCountNotOK(size);
	const real *it = &args[0];
	real val = *it;
	while (--size) {
		const real v = *++it;
		if (v < val) val = v;
	}
	return val;
}

real Func_avg::execute( Environment &env, const Arguments &args ) const {
	(void)env; /* silence warning */
	Arguments::size_type size = args.size();
	throwIfArgumentsCountNotOK(size);
	const real *it = &args[0];
	real val = *it;
	while (--size) {
		val += *++it;
	}
	return val / args.size();
}


}
#endif
