/** \file
 * Calculator functions implementation.
 * $Id: functions.cpp,v 1.1 2008/02/08 21:47:32 mina86 Exp $
 */
#ifndef H_VARIABLES_HPP
#define H_VARIABLES_HPP

#include "functions.hpp"
#include "exceptions.hpp"
#include "math.hpp"

#include <vector>

namespace calc {
	/**
	 * Checks number of arguments and if it is invalid throws exception.
	 * \param a   arguments.
	 * \param num desired number of arguments.
	 * \throw InvalidNumberOfArguments if number of arguments in \a
	 *                                 a is not \a num.
	 */
	static inline void check_arg_count(const FunctionArguments &a,
	                                   FunctionArguments::size_type num = 1) {
		if (a.size() != num) {
			throw InvalidNumberOfArguments();
		}
	}


	real func_sqrt (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return sqrt (arguments[0]);
	}

	real func_cbrt (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return cbrt (arguments[0]);
	}


	real func_exp  (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return exp  (arguments[0]);
	}

	real func_log  (const FunctionArguments &arguments) {
		switch (arguments.size()) {
		case  1: return log(arguments[0]);
		case  2: return log(arguments[0]) / log(arguments[1]);
		default: throw InvalidNumberOfArguments();
		}
	}

	real func_log10(const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return log10(arguments[0]);
	}

	real func_log2 (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return log2 (arguments[0]);
	}


	real func_cos  (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return cos  (arguments[0]);
	}

	real func_sin  (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return sin  (arguments[0]);
	}

	real func_tan  (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return tan  (arguments[0]);
	}

	real func_acos (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return acos (arguments[0]);
	}

	real func_asin (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return asin (arguments[0]);
	}

	real func_atan (const FunctionArguments &arguments) {
		switch (arguments.size()) {
		case  1: return atan (arguments[0]);
		case  2: return atan2(arguments[0], arguments[1]);
		default: throw InvalidNumberOfArguments();
		}
	}


	real func_cosh (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return cosh (arguments[0]);
	}

	real func_sinh (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return sinh (arguments[0]);
	}

	real func_tanh (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return tanh (arguments[0]);
	}

	real func_acosh(const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return acosh(arguments[0]);
	}

	real func_asinh(const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return asinh(arguments[0]);
	}

	real func_atanh(const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return atanh(arguments[0]);
	}


	real func_max  (const FunctionArguments &arguments) {
		FunctionArguments::size_type size = arguments.size();
		if (!size) {
			throw InvalidNumberOfArguments();
		}
		const real *it = &arguments[0];
		real val = *it;
		while (--size) {
			const real v = *++it;
			if (v > val) val = v;
		}
		return val;
	}

	real func_min  (const FunctionArguments &arguments) {
		FunctionArguments::size_type size = arguments.size();
		if (!size) {
			throw InvalidNumberOfArguments();
		}
		const real *it = &arguments[0];
		real val = *it;
		while (--size) {
			const real v = *++it;
			if (v < val) val = v;
		}
		return val;
	}

	real func_avg  (const FunctionArguments &arguments) {
		FunctionArguments::size_type size = arguments.size();
		if (!size) {
			throw InvalidNumberOfArguments();
		}
		const real *it = &arguments[0];
		real val = *it;
		while (--size) {
			val += *++it;
		}
		return val / arguments.size();
	}

}


#endif
