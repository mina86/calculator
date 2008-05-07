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


/** Prints help. */
static void help();
/** Prints syntax help. */
static void helpSyntax();
/** Printsss list of built-in functions. */
static void listFunc();
/** Prints list of built-in constants. */
static void listConst();
/** Prints list of operators. */
static void listOp();


int main(int argc, char **argv) {
	bool verbose = false, quiet = false, finish = false;

	int i = 1;
	for (; i < argc && argv[i][0] == '-' && argv[i][1]; ++i) {
		if (argv[i][1] == '-' && argv[i][2] == 0) {
			++i;
			break;
		}

		for (char *ch = argv[i]; *++ch; ) {
			switch (*ch) {
			case 'v': verbose = true;               break;
			case 'q': quiet   = true;               break;
			case 'h': finish  = true; help();       break;
			case 's': finish  = true; helpSyntax(); break;
			case 'f': finish  = true; listFunc();   break;
			case 'c': finish  = true; listConst();  break;
			case 'o': finish  = true; listOp();     break;
			default:
				std::cerr << "invalid option: " << *ch << '\n';
				return 1;
			}
		}
	}

	if (i < argc) {
		std::cerr << "enexpected argument: " << argv[i] << '\n';
		return 1;
	}

	if (finish) {
		return 0;
	}


	/** Create environment. */
	calc::Environment *env =
		verbose ? new VerboseEnvironment() : new calc::Environment();


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
    calc::Environment::Functions &funcs = env->functions();
    funcs["sqrt" ] = calc::Func_sqrt::get();
    funcs["cbrt" ] = calc::Func_cbrt::get();
    funcs["e"    ] = calc::Func_exp::get();
    funcs["exp"  ] = calc::Func_exp::get();
    funcs["log"  ] = calc::Func_log::get();
    funcs["ln"   ] = calc::Func_log::get();
    funcs["log10"] = calc::Func_log10::get();
    funcs["log2" ] = calc::Func_log2::get();
    funcs["cos"  ] = calc::Func_cos::get();
    funcs["sin"  ] = calc::Func_sin::get();
    funcs["tan"  ] = calc::Func_tan::get();
    funcs["acos" ] = calc::Func_acos::get();
    funcs["asin" ] = calc::Func_asin::get();
    funcs["atan" ] = calc::Func_atan::get();
    funcs["cosh" ] = calc::Func_cosh::get();
    funcs["sinh" ] = calc::Func_sinh::get();
    funcs["tanh" ] = calc::Func_tanh::get();
    funcs["acosh"] = calc::Func_acosh::get();
    funcs["asinh"] = calc::Func_asinh::get();
    funcs["atanh"] = calc::Func_atanh::get();


	/* Run */
	calc::FILELexer lexer;
	yy::Parser parser(lexer, *env);
	parser.parse();


	/* Print variables */
	if (!quiet) {
		calc::Environment::Variables::const_iterator
			it = env->global().begin(), end = env->global().end();
		for (; it != end; ++it) {
			std::cout << it->first << " = " << it->second << '\n';
		}
	}


	/* Finish */
	delete env;
	return 0;
}



static void help() {
	std::cout <<
		"usage: ./calc [-vqhsofc]\n"
		"  -v  print result of each instruction terminated with a new line\n"
		"  -q  do not print values of all global variables at the end\n"
		"  -h  print this help screen and exit\n"
		"  -s  print syntax\n"
		"  -o  print list of oeprators and exit\n"
		"  -f  print list of built-in functions and exit\n"
		"  -c  print list of built-in constants and exit\n";
}


static void helpSyntax() {
	std::cout <<
"Calculator reads in-fix expressions (similar to C) from standard\n"
"input.  Expressions may end with a semicolon or a new line.  In the\n"
"later case if a -v switch was given expression's result will be\n"
"printed.\n"
"\n"
"To access a variable simply state its name.  It will refer to local\n"
"variable (see functions below).  To refer to global variable prefix it\n"
"with a dolar sign ('$') and to refer to a constant prefix it with\n"
"a hash ('#').\n"
"\n"
"To call a function simply put it name followd by a comma-separated\n"
"list of arguments in parens.  If function takes no arguments you must\n"
"still put empty parens.\n"
"\n"
"To define a user function use the 'define' keyword, as follows:\n"
"  define name(arg1, arg2, arg3) = expression\n"
"\n"
"When user function is called expression that defines it is called in\n"
"a separate scope with it's own local variables.\n"
"\n"
"If you end a line by a single slash the new line character is ignored\n"
"and the next line is treated as continuation of the current one.  Also\n"
"all white space (including new lines) after a comma are ignored.\n"
"\n"
"If you call a non-existant function or assign value to already defined\n"
"constant an error is triggered and the state of the enviroment is\n"
"undefined (ie. parts of the expressions may have been executed).\n";
}


static void listFunc() {
	std::cout << "Available funxtions:\n"
		"  sqrt(x)   returns square root of x\n"
		"  cbrt(x)   returns cube root of x\n"
		"  e(x)      synonym of exp(x)\n"
		"  exp(x)    returns e raised to the power of x \n"
		"  log(x)    synonym of ln(x)\n"
		"  ln(x)     returns the natural logarithm of x\n"
		"  log10(x)  returns base 10 logarithm of x\n"
		"  log2(x)   returns base 2 logarithm of x\n"
		"  cos(x)    returns cosine of x (given in radians)\n"
		"  sin(x)    returns sine of x (given in radians)\n"
		"  tan(x)    returns tangent of x (given in radians)\n"
		"  acos(x)   returns arc cosine of x (given in radians)\n"
		"  asin(x)   returns arc sine of x (given in radians)\n"
		"  atan(x)   returns arc tangent of x (given in radians)\n"
		"  atan(x,y) returns arc tangent of y/x (given in radians)\n"
		"  cosh(x)   returns hyperbolic cosine of x\n"
		"  sinh(x)   returns hyperbolic sine of x\n"
		"  tanh(x)   returns hyperbolic tangent od x\n"
		"  acosh(x)  is an inverse of cosh\n"
		"  asinh(x)  is an inverse of sinh\n"
		"  atanh(x)  is an inverse of tanh\n";
}


static void listConst() {
	std::cout << "Available constants:\n"
#if defined M_E
		"  e         base of a natural logarithm\n"
#endif
#if defined M_LOG2E
		"  log2e     a base 2 logarithm of e\n"
#endif
#if defined M_LOG10E
		"  log10e    a base 10 logarithm of e\n"
#endif
#if defined M_LN2
		"  ln2       a natural logarithm of 2\n"
#endif
#if defined M_LN10
		"  ln10      a natural logarithm of 10\n"
#endif
#if defined M_PI
		"  pi        Pi\n"
#endif
#if defined M_PI_2
		"  pi_2      Pi/2\n"
#endif
#if defined M_PI_4
		"  pi_4      Pi/4\n"
#endif
#if defined M_1_PI
		"  _1_pi     1/Pi\n"
#endif
#if defined M_2_PI
		"  _2_pi     2/Pi\n"
#endif
#if defined M_2_SQRTPI
		"  _2_sqrtpi 2/sqrt(Pi)\n"
#endif
#if defined M_SQRT2
		"  sqrt2     square root of 2\n"
#endif
#if defined M_SQRT1_2
		"  sqrt1_2   1/sqrt(2)\n"
#endif
		;
}


static void listOp() {
	std::cout << "Available operators (from highest priority):\n"
		"  Prefix          + - !             right-to-left\n"
		"  Power           ^                 right-to-left\n"
		"  Multiplicative  * /               left-to-right\n"
		"  Additive        + -               left-to-right\n"
		"  Relation        > < >= <=         left-to-right\n"
		"  Compare         == !=             left-to-right\n"
		"  Logic and       &&                left-to-right\n"
		"  Logic xor       ^^                left-to-right\n"
		"  Logic or        ||                left-to-right\n"
		"  Ternary         ?:                right-to-left\n"
		"  Assigment       = += -= *= /= ^=  right-to-left\n"
		"  Comma           ,                 left-to-right\n";
}
