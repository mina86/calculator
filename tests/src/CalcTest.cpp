/**
 * file: CalcTest.cpp
 * author: Jakub Księżniak
 */
#include <iostream>
#include "CalcTest.h"
#include <fstream>
#include <time.h>

#define MAX_EXPONENT 10


std::vector<std::string> CalcTest::functions;
std::vector<std::string> CalcTest::operators;

void CalcTest::init()
{
	static bool initialised = false;
	if (initialised)
	{
		return;
	}

	initialised = true;

	srand( time(NULL) );

	functions.reserve(6);
	functions.push_back("sqrt" );
	functions.push_back("e"    );
	functions.push_back("l"    );
	functions.push_back("c"    );
	functions.push_back("s"    );
	functions.push_back("a"    );

	operators.reserve(5);
	operators.push_back(" + ");
	operators.push_back(" - ");
	operators.push_back(" * ");
	operators.push_back(" / ");
	operators.push_back("^");
}


std::string CalcTest::getRName()
{
	std::string rname;
	for (int i = 0; i < 4; ++i)
		rname.push_back((char) (rand()%20) + 'a');
	return rname;
}


void CalcTest::generateExpr(std::ostream &out, unsigned length,
                            bool useFunctions) {
	int newExpr;
	std::string strOp;
	std::string strFunc;

	while (length--)
	{
		if(rand() % 2 == 0)
		{
			out << getRValue();
		}
		else {
			newExpr = rand() % 4;
			if(newExpr > 0)
			{
				if(rand() % 2 == 0 && useFunctions)
				{
					strFunc = getFunction();
					out << strFunc;
				}
				out << "( ";
				if(strFunc == "e")
					out << rand() % MAX_EXPONENT;
				else if(strFunc == "sqrt")
					out << getRValue();
				else
					generateExpr(out, newExpr, useFunctions);
				out << " )";
				strFunc = "";
			}
			else {
				out << getRValue();
			}
		}
		if(length > 0)
		{
			strOp = getOperator();
			out << strOp;

			if(strOp == "^")
			{
				out << rand() % MAX_EXPONENT << getOperator(true);
			}
		}
	}
}


void CalcTest::generateTest(unsigned count, unsigned maxLen,
                            bool useFunctions, bool vars)
{
	std::ofstream fcal(calcFile.c_str());
	std::ofstream fbc(bcFile.c_str());

	fcal << "define l(x) = ln(x)\n"
	        "define s(x) = sin(x)\n"
	        "define c(x) = cos(x)\n"
	        "define a(x) = atan(x)\n";

	if (!vars) {
		std::ostringstream outStr;

		while (count--)
		{
			generateExpr(outStr, rand() % maxLen + 1, useFunctions);
			outStr << '\n';
		}

		fcal << outStr.str();
		fbc << outStr.str();
		std::cout << outStr.str();
	} else {
		std::string rname;

		while (count--)
		{
			std::ostringstream outStr;
			rname = getRName();
			fcal << "define " + rname + "() = ";
			fbc  << "define " + rname + "() { return (";
			generateExpr(outStr, rand() % maxLen + 1, useFunctions);
			fcal << outStr.str() << '\n' ;
			fbc  << outStr.str() << "); }\n";
			std::cout << outStr.str() << '\n';

			fcal << rname << "=" << rname << "();\n"
			     << rname << "() !=" << rname << '\n';
			fbc  << rname << "=" << rname << "();\n"
			     << rname << "() !=" << rname << '\n';
		}
	}
}

