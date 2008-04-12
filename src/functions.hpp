/** \file
 * Calculator functions.
 * $Id: functions.hpp,v 1.3 2008/04/12 12:59:08 mina86 Exp $
 */
#ifndef H_FUNCTIONS_HPP
#define H_FUNCTIONS_HPP

#include "config.hpp"

#include "environment.hpp"
#include "function.hpp"


namespace calc {

typedef  std::vector<real> FunctionArguments;


/**
 * Returns the squere root of its argument.
 * \param arguments function argument(s).
 */
real func_sqrt (const FunctionArguments &arguments);

/**
 * Returns the cube root of its argument.
 * \param arguments function argument(s).
 */
real func_cbrt (const FunctionArguments &arguments);


/**
 * Returns the value of the base of natural logarithms to the power
 * given as argument.
 * \param arguments function argument(s).
 */
real func_exp  (const FunctionArguments &arguments);

/**
 * If called with one argument returns the natural logarithm of its
 * argument.  If called with two arguments returns logarithm with base
 * specified by second argument of the first argument.
 * \param arguments function argument(s).
 */
real func_log  (const FunctionArguments &arguments);

/**
 * Returns the the base 10 logarithm of its argument.
 * \param arguments function argument(s).
 */
real func_log10(const FunctionArguments &arguments);

/**
 * Returns the the base 2 logarithm of its argument.
 * \param arguments function argument(s).
 */
real func_log2 (const FunctionArguments &arguments);


/**
 * Returns the cosine of its argument.
 * \param arguments function argument(s).
 */
real func_cos  (const FunctionArguments &arguments);

/**
 * Returns the sine of its argument.
 * \param arguments function argument(s).
 */
real func_sin  (const FunctionArguments &arguments);

/**
 * Returns the tangent of its argument.
 * \param arguments function argument(s).
 */
real func_tan  (const FunctionArguments &arguments);

/**
 * Returns the arcus cosine of its argument.
 * \param arguments function argument(s).
 */
real func_acos (const FunctionArguments &arguments);

/**
 * Returns the arcus sine of its argument.
 * \param arguments function argument(s).
 */
real func_asin (const FunctionArguments &arguments);

/**
 * Returns the arcus tangent of its argument(s).  If only one argument
 * is given uses \c tan() function.  If two arguments are given uses
 * \c tan2() function.
 * \param arguments function argument(s).
 */
real func_atan (const FunctionArguments &arguments);


/**
 * Returns the hyperbolic cosine of its argument.
 * \param arguments function argument(s).
 */
real func_cosh (const FunctionArguments &arguments);

/**
 * Returns the hyperbolic sine of its argument.
 * \param arguments function argument(s).
 */
real func_sinh (const FunctionArguments &arguments);

/**
 * Returns the hyperbolic tangent of its argument.
 * \param arguments function argument(s).
 */
real func_tanh (const FunctionArguments &arguments);

/**
 * Returns inverse hyperbolic cosine of its argument.
 * \param arguments function argument(s).
 */
real func_acosh(const FunctionArguments &arguments);

/**
 * Returns the inverse hyperbolic sine of its argument.
 * \param arguments function argument(s).
 */
real func_asinh(const FunctionArguments &arguments);

/**
 * Returns the inverse hyperbolic tangent of its argument.
 * \param arguments function argument(s).
 */
real func_atanh(const FunctionArguments &arguments);


/**
 * Returns the bigest of its arguments.
 * \param arguments function argument(s).
 */
real func_max  (const FunctionArguments &arguments);

/**
 * Returns the smallest of its arguments.
 * \param arguments function argument(s).
 */
real func_min  (const FunctionArguments &arguments);

/**
 * Returns the average value of its arguments.
 * \param arguments function argument(s).
 */
real func_avg  (const FunctionArguments &arguments);


}


#endif
