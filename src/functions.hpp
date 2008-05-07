/** \file
 * Calculator functions.
 * $Id: functions.hpp,v 1.5 2008/05/07 17:54:28 mina86 Exp $
 */
#ifndef H_FUNCTIONS_HPP
#define H_FUNCTIONS_HPP

#include "config.hpp"

#include "environment.hpp"
#include "function.hpp"


namespace calc {


/**
 * A Built-in Functions base class
 */
struct BuiltInFunction : public Function {
	virtual bool argumentsCountOK(unsigned count) const;
	virtual void free();

protected:
	/** Constructor available only for child classes */
	BuiltInFunction(const unsigned &nargs)
		: minArgs(nargs), maxArgs(nargs) { }
	BuiltInFunction(const unsigned &min, const unsigned &max)
		: minArgs(min), maxArgs(max) { }

private:
	/** Minimal number of arguments passed to function */
	const unsigned minArgs;

	/** Maximal number of arguments passed to function */
	const unsigned maxArgs;
};


/**
 * Makro for defining get() static methods of built in functions.
 */
#define CALC_FUNC_GET(func) \
	static Func_ ## func *get() { \
		static Func_ ## func f; \
		return &f; \
	}


/**
 * Structure executes the squere root function.
 */
struct Func_sqrt :  public BuiltInFunction {
    Func_sqrt() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(sqrt)
};


/**
 * Structure executes the cube root function.
 */
struct Func_cbrt :  public BuiltInFunction {
    Func_cbrt() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(cbrt)
};


/**
 * Structure executes the base of natural logarithms to the power
 * given as argument.
 */
struct Func_exp :  public BuiltInFunction {
    Func_exp() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(exp)
};

/**
 * Structure executes the natural logarithm if called with one argument
 * If called with two arguments structure executes logarithm with base
 * specified by second argument of the first argument.
 */
struct Func_log :  public BuiltInFunction {
    Func_log() : BuiltInFunction(1,2) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(log)
};

/**
 * Structure executes the the base 10 logarithm function.
 */
struct Func_log10 :  public BuiltInFunction {
    Func_log10() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(log10)
};

/**
 * Structure executes the the base 2 logarithm function.
 */
struct Func_log2 :  public BuiltInFunction {
    Func_log2() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(log2)
};

/**
 * Structure executes the cosine function.
 */
struct Func_cos :  public BuiltInFunction {
    Func_cos() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(cos)
};

/**
 * Structure executes the sine function.
 */
struct Func_sin :  public BuiltInFunction {
    Func_sin() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(sin)
};

/**
 * Structure executes the tangent function.
 */
struct Func_tan :  public BuiltInFunction {
    Func_tan() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(tan)
};

/**
 * Structure executes the arcus cosine function.
 */
struct Func_acos :  public BuiltInFunction {
    Func_acos() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(acos)
};

/**
 * Structure executes the arcus sine function.
 */
struct Func_asin :  public BuiltInFunction {
    Func_asin() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(asin)
};

/**
 * Structure executes the arcus tangent function.  If only one argument
 * is given uses \c tan() function.  If two arguments are given uses
 * \c tan2() function.
 */
struct Func_atan :  public BuiltInFunction {
    Func_atan() : BuiltInFunction(1,2) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(atan)
};



/**
 * Structure executes the hyperbolic cosine function.
 */
struct Func_cosh :  public BuiltInFunction {
    Func_cosh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(cosh)
};

/**
 * Structure executes the hyperbolic sine function.
 */
struct Func_sinh :  public BuiltInFunction {
    Func_sinh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(sinh)
};

/**
 * Structure executes the hyperbolic tangent function.
 */
struct Func_tanh :  public BuiltInFunction {
    Func_tanh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(tanh)
};

/**
 * Structure executes inverse hyperbolic cosine function.
 */
struct Func_acosh :  public BuiltInFunction {
    Func_acosh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(acosh)
};

/**
 * Structure executes the inverse hyperbolic sine function.
 */
struct Func_asinh :  public BuiltInFunction {
    Func_asinh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(asinh)
};

/**
 * Structure executes the inverse hyperbolic tangent function.
 */
struct Func_atanh :  public BuiltInFunction {
    Func_atanh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(atanh)
};


/**
 * Structure executes the biggest function.
 */
struct Func_max :  public BuiltInFunction {
    Func_max() : BuiltInFunction(1, -1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(max)
};

/**
 * Structure executes the smallest function.
 */
struct Func_min :  public BuiltInFunction {
    Func_min() : BuiltInFunction(1, -1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(min)
};

/**
 * Structure executes the average value function.
 */
struct Func_avg :  public BuiltInFunction {
    Func_avg() : BuiltInFunction(1, -1) {};

    real execute(Environment &env, const Arguments &args) const;

    CALC_FUNC_GET(avg)
};



#undef CALC_FUNC_GET

}

#endif
