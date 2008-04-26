/** \file
 * Calculator functions implementation.
 * $Id: functions.cpp,v 1.3 2008/04/26 19:08:28 kuba Exp $
 */
#ifndef H_VARIABLES_HPP
#define H_VARIABLES_HPP

#include "functions.hpp"
#include "exceptions.hpp"
#include "math.hpp"

#include <vector>

namespace calc {
#if 0
	/**
	 * Checks number of arguments and if it is invalid throws exception.
	 * \param a   arguments.
	 * \param num desired number of arguments.
	 * \throw InvalidNumberOfArguments if number of arguments in \a
	 *                                 a is not \a num.
	 */
	static inline void check_arg_count(const Arguments &a,
	                                   Arguments::size_type num = 1) {
		if (a.size() != num) {
			throw InvalidNumberOfArguments();
		}
	}

	real func_sqrt (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::sqrt (arguments[0]);
	}

	real func_cbrt (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::cbrt (arguments[0]);
	}


	real func_exp  (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::exp  (arguments[0]);
	}

	real func_log  (const FunctionArguments &arguments) {
		switch (arguments.size()) {
		case  1: return m::log(arguments[0]);
		case  2: return m::log(arguments[0]) / m::log(arguments[1]);
		default: throw InvalidNumberOfArguments();
		}
	}

	real func_log10(const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::log10(arguments[0]);
	}

	real func_log2 (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::log2 (arguments[0]);
	}


	real func_cos  (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::cos  (arguments[0]);
	}

	real func_sin  (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::sin  (arguments[0]);
	}

	real func_tan  (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::tan  (arguments[0]);
	}

	real func_acos (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::acos (arguments[0]);
	}

	real func_asin (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::asin (arguments[0]);
	}

	real func_atan (const FunctionArguments &arguments) {
		switch (arguments.size()) {
		case  1: return m::atan (arguments[0]);
		case  2: return m::atan (arguments[0], arguments[1]);
		default: throw InvalidNumberOfArguments();
		}
	}


	real func_cosh (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::cosh (arguments[0]);
	}

	real func_sinh (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::sinh (arguments[0]);
	}

	real func_tanh (const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::tanh (arguments[0]);
	}

	real func_acosh(const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::acosh(arguments[0]);
	}

	real func_asinh(const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::asinh(arguments[0]);
	}

	real func_atanh(const FunctionArguments &arguments) {
		check_arg_count(arguments);
		return m::atanh(arguments[0]);
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
#endif


    /**
     * Square root function class
     */
    Func_sqrt * Func_sqrt::get()
    {
        static Func_sqrt fun;
        return &fun;
    }

    real Func_sqrt::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::sqrt (args[0]);
    }

    /**
    * Cube root function class
    */
    Func_cbrt * Func_cbrt::get()
    {
        static Func_cbrt fun;
        return &fun;
    }

    real Func_cbrt::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::cbrt (args[0]);
    }

    /**
    * Exponential function class
    */
    Func_exp * Func_exp::get()
    {
        static Func_exp fun;
        return &fun;
    }

    real Func_exp::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::exp  (args[0]);
    }

    /**
     * Natural logarithm function class
     */
    Func_log * Func_log::get()
    {
        static Func_log fun;
        return &fun;
    }

    real Func_log::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        switch (args.size()) {
        case  1: return m::log(args[0]);
        case  2: return m::log(args[0]) / m::log(args[1]);
        default: throw InvalidNumberOfArguments();
        }
    }


    /**
     * the base 10 logarithm function class
     */
    Func_log10 * Func_log10::get()
    {
        static Func_log10 fun;
        return &fun;
    }

    real Func_log10::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::log10(args[0]);
    }


    /**
     * The base 2 logarithm function class
     */
    Func_log2 * Func_log2::get()
    {
        static Func_log2 fun;
        return &fun;
    }

    real Func_log2::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::log2 (args[0]);
    }

    /**
     * Cosine function class
     */
    Func_cos * Func_cos::get()
    {
        static Func_cos fun;
        return &fun;
    }

    real Func_cos::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::cos (args[0]);
    }

    /**
     * Sine function class
     */
    Func_sin * Func_sin::get()
    {
        static Func_sin fun;
        return &fun;
    }

    real Func_sin::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::sin (args[0]);
    }

    /**
     * Tangent function class
     */
    Func_tan * Func_tan::get()
    {
        static Func_tan fun;
        return &fun;
    }

    real Func_tan::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::tan (args[0]);
    }

    /**
     * arcus cosine function class
     */
    Func_acos * Func_acos::get()
    {
        static Func_acos fun;
        return &fun;
    }

    real Func_acos::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::acos (args[0]);
    }

    /**
     * arcus sine function class
     */
    Func_asin * Func_asin::get()
    {
        static Func_asin fun;
        return &fun;
    }

    real Func_asin::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::asin (args[0]);
    }

    /**
     * arcus tangent function class
     */
    Func_atan * Func_atan::get()
    {
        static Func_atan fun;
        return &fun;
    }

    real Func_atan::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        switch (args.size()) {
        case  1: return m::atan (args[0]);
        case  2: return m::atan (args[0], args[1]);
        default: throw InvalidNumberOfArguments();
        }
    }

    /**
     * the hyperbolic cosine function class
     */
    Func_cosh * Func_cosh::get()
    {
        static Func_cosh fun;
        return &fun;
    }

    real Func_cosh::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::cosh (args[0]);
    }

    /**
     * the hyperbolic sine function class
     */
    Func_sinh * Func_sinh::get()
    {
        static Func_sinh fun;
        return &fun;
    }

    real Func_sinh::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::sinh (args[0]);
    }

    /**
     * the hyperbolic tangent function class
     */
    Func_tanh * Func_tanh::get()
    {
        static Func_tanh fun;
        return &fun;
    }

    real Func_tanh::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::tanh (args[0]);
    }

    /**
     * inverse hyperbolic cosine function class
     */
    Func_acosh * Func_acosh::get()
    {
        static Func_acosh fun;
        return &fun;
    }

    real Func_acosh::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::acosh (args[0]);
    }

    /**
     * inverse hyperbolic sine function class
     */
    Func_asinh * Func_asinh::get()
    {
        static Func_asinh fun;
        return &fun;
    }

    real Func_asinh::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::asinh (args[0]);
    }

    /**
     * inverse hyperbolic tangent function class
     */
    Func_atanh * Func_atanh::get()
    {
        static Func_atanh fun;
        return &fun;
    }

    real Func_atanh::execute( Environment &env, const Arguments &args ) const
    {
        throwIfArgumentsCountNotOK(args.size());
        return m::atanh (args[0]);
    }

    /**
     * Max function class
     */
    Func_max * Func_max::get()
    {
        static Func_max fun;
        return &fun;
    }

    real Func_max::execute( Environment &env, const Arguments &args ) const
    {
        Arguments::size_type size = args.size();
        if (!size) {
            throw InvalidNumberOfArguments();
        }
        const real *it = &args[0];
        real val = *it;
        while (--size) {
            const real v = *++it;
            if (v > val) val = v;
        }
        return val;
    }

    /**
     * Min function class
     */
    Func_min * Func_min::get()
    {
        static Func_min fun;
        return &fun;
    }

    real Func_min::execute( Environment &env, const Arguments &args ) const
    {
        Arguments::size_type size = args.size();
        if (!size) {
            throw InvalidNumberOfArguments();
        }
        const real *it = &args[0];
        real val = *it;
        while (--size) {
            const real v = *++it;
            if (v < val) val = v;
        }
        return val;
    }

    /**
     * Average function class
     */
    Func_avg * Func_avg::get()
    {
        static Func_avg fun;
        return &fun;
    }

    real Func_avg::execute( Environment &env, const Arguments &args ) const
    {
        Arguments::size_type size = args.size();
        if (!size) {
            throw InvalidNumberOfArguments();
        }
        const real *it = &args[0];
        real val = *it;
        while (--size) {
            val += *++it;
        }
        return val / args.size();
    }
}
#endif
