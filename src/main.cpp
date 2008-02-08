#include "config.hpp"

#include <math.h>

#include <iostream>

#include "functions.hpp"
#include "environment.hpp"
#include "file-lexer.hpp"


/**
 * A "Verbose" environment which prints result of each
 * instruction.
 */
struct VerboseEnvironment : public calc::Environment {
	void instruction(calc::real value) {
		std::cout << value << '\n';
	}
};


int main(void) {
	calc::Environment *env = new VerboseEnvironment();

	/* Register constants */
#if defined M_El
	env->constants["e"] = M_El;
#elif defined M_E
	env->constants["e"] = M_E;
#endif
#if defined M_LOG2El
	env->constants["log2e"] = M_LOG2El;
#elif defined M_LOG2E
	env->constants["log2e"] = M_LOG2E;
#endif
#if defined M_LOG10El
	env->constants["log10e"] = M_LOG10El;
#elif defined M_LOG10E
	env->constants["log10e"] = M_LOG10E;
#endif
#if defined M_LN2l
	env->constants["ln2"] = M_LN2l;
#elif defined M_LN2
	env->constants["ln2"] = M_LN2;
#endif
#if defined M_LN10l
	env->constants["ln10"] = M_LN10l;
#elif defined M_LN10
	env->constants["ln10"] = M_LN10;
#endif
#if defined M_PIl
	env->constants["pi"] = M_PIl;
#elif defined M_PI
	env->constants["pi"] = M_PI;
#endif
#if defined M_PI_2l
	env->constants["pi_2"] = M_PI_2l;
#elif defined M_PI_2
	env->constants["pi_2"] = M_PI_2;
#endif
#if defined M_PI_4l
	env->constants["pi_4"] = M_PI_4l;
#elif defined M_PI_4
	env->constants["pi_4"] = M_PI_4;
#endif
#if defined M_1_PIl
	env->constants["_1_PI"] = M_1_PIl;
#elif defined M_1_PI
	env->constants["_1_PI"] = M_1_PI;
#endif
#if defined M_2_PIl
	env->constants["_2_PI"] = M_2_PIl;
#elif defined M_2_PI
	env->constants["_2_PIl"] = M_2_PI;
#endif
#if defined M_2_SQRTPIl
	env->constants["_2_SQRTPI"] = M_2_SQRTPIl;
#elif defined M_2_SQRTPI
	env->constants["_2_SQRTPI"] = M_2_SQRTPI;
#endif
#if defined M_SQRT2l
	env->constants["sqrt2"] = M_SQRT2l;
#elif defined M_SQRT2
	env->constants["sqrt2"] = M_SQRT2;
#endif
#if defined M_SQRT1_2l
	env->constants["sqrt1_2"] = M_SQRT1_2l;
#elif defined M_SQRT1_2
	env->constants["sqrt1_2"] = M_SQRT1_2;
#endif

	/* Register functions */
	env->functions["sqrt" ] = calc::func_sqrt;
	env->functions["cbrt" ] = calc::func_cbrt;
	env->functions["e"    ] = calc::func_exp;
	env->functions["exp"  ] = calc::func_exp;
	env->functions["log"  ] = calc::func_log;
	env->functions["ln"   ] = calc::func_log;
	env->functions["log10"] = calc::func_log10;
	env->functions["log2" ] = calc::func_log2;
	env->functions["cos"  ] = calc::func_cos;
	env->functions["sin"  ] = calc::func_sin;
	env->functions["tan"  ] = calc::func_tan;
	env->functions["acos" ] = calc::func_acos;
	env->functions["asin" ] = calc::func_asin;
	env->functions["atan" ] = calc::func_atan;
	env->functions["cosh" ] = calc::func_cosh;
	env->functions["sinh" ] = calc::func_sinh;
	env->functions["tanh" ] = calc::func_tanh;
	env->functions["acosh"] = calc::func_acosh;
	env->functions["asinh"] = calc::func_asinh;
	env->functions["atanh"] = calc::func_atanh;

	/* Run */
	calc::FILELexer lexer;
	yy::Parser parser(lexer, *env);
	parser.parse();

	/* Print variables */
	calc::Environment::Variables::const_iterator it = env->variables.begin();
	calc::Environment::Variables::const_iterator end = env->variables.end();
	for (; it != end; ++it) {
		std::cout << it->first << " = " << it->second << '\n';
	}

	delete env;
	return 0;
}
