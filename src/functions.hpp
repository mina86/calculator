/** \file
 * Calculator functions.
 * $Id: functions.hpp,v 1.4 2008/04/26 19:08:28 kuba Exp $
 */
#ifndef H_FUNCTIONS_HPP
#define H_FUNCTIONS_HPP

#include "config.hpp"

#include "environment.hpp"
#include "function.hpp"
#include "built-in-function.hpp"


namespace calc {

/**
 * Structure executes the squere root function.
 */
//real func_sqrt (const FunctionArguments &arguments);
struct Func_sqrt :  public BuiltInFunction
{
    Func_sqrt() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_sqrt *get();
};


/**
 * Structure executes the cube root function.
 */
//real func_cbrt (const FunctionArguments &arguments);
struct Func_cbrt :  public BuiltInFunction
{
    Func_cbrt() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_cbrt *get();
};


/**
 * Structure executes the base of natural logarithms to the power
 * given as argument.
 */
//real func_exp  (const FunctionArguments &arguments);
struct Func_exp :  public BuiltInFunction
{
    Func_exp() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_exp *get();
};

/**
 * Structure executes the natural logarithm if called with one argument
 * If called with two arguments structure executes logarithm with base
 * specified by second argument of the first argument.
 */
//real func_log  (const FunctionArguments &arguments);
struct Func_log :  public BuiltInFunction
{
    Func_log() : BuiltInFunction(1,2) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_log *get();
};

/**
 * Structure executes the the base 10 logarithm function.
 */
//real func_log10(const FunctionArguments &arguments);
struct Func_log10 :  public BuiltInFunction
{
    Func_log10() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_log10 *get();
};

/**
 * Structure executes the the base 2 logarithm function.
 */
//real func_log2 (const FunctionArguments &arguments);
struct Func_log2 :  public BuiltInFunction
{
    Func_log2() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_log2 *get();
};

/**
 * Structure executes the cosine function.
 */
//real func_cos  (const FunctionArguments &arguments);
struct Func_cos :  public BuiltInFunction
{
    Func_cos() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_cos *get();
};

/**
 * Structure executes the sine function.
 */
// real func_sin  (const FunctionArguments &arguments);
struct Func_sin :  public BuiltInFunction
{
    Func_sin() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_sin *get();
};

/**
 * Structure executes the tangent function.
 */
//real func_tan  (const FunctionArguments &arguments);
struct Func_tan :  public BuiltInFunction
{
    Func_tan() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_tan *get();
};

/**
 * Structure executes the arcus cosine function.
 */
//real func_acos (const FunctionArguments &arguments);
struct Func_acos :  public BuiltInFunction
{
    Func_acos() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_acos *get();
};

/**
 * Structure executes the arcus sine function.
 */
//real func_asin (const FunctionArguments &arguments);
struct Func_asin :  public BuiltInFunction
{
    Func_asin() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_asin *get();
};

/**
 * Structure executes the arcus tangent function.  If only one argument
 * is given uses \c tan() function.  If two arguments are given uses
 * \c tan2() function.
 */
//real func_atan (const FunctionArguments &arguments);
struct Func_atan :  public BuiltInFunction
{
    Func_atan() : BuiltInFunction(1,2) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_atan *get();
};



/**
 * Structure executes the hyperbolic cosine function.
 */
//real func_cosh (const FunctionArguments &arguments);
struct Func_cosh :  public BuiltInFunction
{
    Func_cosh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_cosh *get();
};

/**
 * Structure executes the hyperbolic sine function.
 */
//real func_sinh (const FunctionArguments &arguments);
struct Func_sinh :  public BuiltInFunction
{
    Func_sinh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_sinh *get();
};

/**
 * Structure executes the hyperbolic tangent function.
 */
//real func_tanh (const FunctionArguments &arguments);
struct Func_tanh :  public BuiltInFunction
{
    Func_tanh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_tanh *get();
};

/**
 * Structure executes inverse hyperbolic cosine function.
 */
//real func_acosh(const FunctionArguments &arguments);
struct Func_acosh :  public BuiltInFunction
{
    Func_acosh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_acosh *get();
};

/**
 * Structure executes the inverse hyperbolic sine function.
 */
//real func_asinh(const FunctionArguments &arguments);
struct Func_asinh :  public BuiltInFunction
{
    Func_asinh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_asinh *get();
};

/**
 * Structure executes the inverse hyperbolic tangent function.
 */
//real func_atanh(const FunctionArguments &arguments);
struct Func_atanh :  public BuiltInFunction
{
    Func_atanh() : BuiltInFunction(1) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_atanh *get();
};


/**
 * Structure executes the biggest function.
 */
//real func_max  (const FunctionArguments &arguments);
struct Func_max :  public BuiltInFunction
{
    Func_max() : BuiltInFunction(1,2) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_max *get();
};

/**
 * Structure executes the smallest function.
 */
//real func_min  (const FunctionArguments &arguments);
struct Func_min :  public BuiltInFunction
{
    Func_min() : BuiltInFunction(1,2) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_min *get();
};

/**
 * Structure executes the average value function.
 */
//real func_avg  (const FunctionArguments &arguments);
struct Func_avg :  public BuiltInFunction
{
    Func_avg() : BuiltInFunction(1,2) {};

    real execute(Environment &env, const Arguments &args) const;

    static Func_avg *get();
};

}


#endif
