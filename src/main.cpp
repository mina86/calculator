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
	{
		calc::Environment::Variables &consts = env->constants();
#if defined M_El
		consts["e"] = M_El;
#elif defined M_E
		consts["e"] = M_E;
#endif
#if defined M_LOG2El
		consts["log2e"] = M_LOG2El;
#elif defined M_LOG2E
		consts["log2e"] = M_LOG2E;
#endif
#if defined M_LOG10El
		consts["log10e"] = M_LOG10El;
#elif defined M_LOG10E
		consts["log10e"] = M_LOG10E;
#endif
#if defined M_LN2l
		consts["ln2"] = M_LN2l;
#elif defined M_LN2
		consts["ln2"] = M_LN2;
#endif
#if defined M_LN10l
		consts["ln10"] = M_LN10l;
#elif defined M_LN10
		consts["ln10"] = M_LN10;
#endif
#if defined M_PIl
		consts["pi"] = M_PIl;
#elif defined M_PI
		consts["pi"] = M_PI;
#endif
#if defined M_PI_2l
		consts["pi_2"] = M_PI_2l;
#elif defined M_PI_2
		consts["pi_2"] = M_PI_2;
#endif
#if defined M_PI_4l
		consts["pi_4"] = M_PI_4l;
#elif defined M_PI_4
		consts["pi_4"] = M_PI_4;
#endif
#if defined M_1_PIl
		consts["_1_pi"] = M_1_PIl;
#elif defined M_1_PI
		consts["_1_pi"] = M_1_PI;
#endif
#if defined M_2_PIl
		consts["_2_pi"] = M_2_PIl;
#elif defined M_2_PI
		consts["_2_pi"] = M_2_PI;
#endif
#if defined M_2_SQRTPIl
		consts["_2_sqrtpi"] = M_2_SQRTPIl;
#elif defined M_2_SQRTPI
		consts["_2_sqrtpi"] = M_2_SQRTPI;
#endif
#if defined M_SQRT2l
		consts["sqrt2"] = M_SQRT2l;
#elif defined M_SQRT2
		consts["sqrt2"] = M_SQRT2;
#endif
#if defined M_SQRT1_2l
		consts["sqrt1_2"] = M_SQRT1_2l;
#elif defined M_SQRT1_2
		consts["sqrt1_2"] = M_SQRT1_2;
#endif
	}

	/* Register functions */
#if 0
	{
		/* FIXME: TODO */
		Environment::Functions &funcs = env->funcs();
		funcs["sqrt" ] = calc::func_sqrt;
		funcs["cbrt" ] = calc::func_cbrt;
		funcs["e"    ] = calc::func_exp;
		funcs["exp"  ] = calc::func_exp;
		funcs["log"  ] = calc::func_log;
		funcs["ln"   ] = calc::func_log;
		funcs["log10"] = calc::func_log10;
		funcs["log2" ] = calc::func_log2;
		funcs["cos"  ] = calc::func_cos;
		funcs["sin"  ] = calc::func_sin;
		funcs["tan"  ] = calc::func_tan;
		funcs["acos" ] = calc::func_acos;
		funcs["asin" ] = calc::func_asin;
		funcs["atan" ] = calc::func_atan;
		funcs["cosh" ] = calc::func_cosh;
		funcs["sinh" ] = calc::func_sinh;
		funcs["tanh" ] = calc::func_tanh;
		funcs["acosh"] = calc::func_acosh;
		funcs["asinh"] = calc::func_asinh;
		funcs["atanh"] = calc::func_atanh;
	}
#endif

	/* Run */
	calc::FILELexer lexer;
	yy::Parser parser(lexer, *env);
	parser.parse();

	/* Print variables */
	calc::Environment::Variables::const_iterator it = env->global().begin();
	calc::Environment::Variables::const_iterator end = env->global().end();
	for (; it != end; ++it) {
		std::cout << it->first << " = " << it->second << '\n';
	}

	delete env;
	return 0;
}
