/**
 * file: CalcTest.cpp
 * author: Jakub Księżniak
 */
#include <iostream>
#include "CalcTest.h"
#include <fstream>

#define MAX_EXPONENT 10

CalcTest::CalcTest(const int &count, const int &len, const std::string &filename1, const std::string &filename2)
	: exprCount(count), maxExprLength(len)
{
    functions.push_back("sqrt" );
    functions.push_back("e"    );
    functions.push_back("l"    );
    functions.push_back("c"    );
    functions.push_back("s"    );
    functions.push_back("a"    );

    operators.push_back(" + ");
    operators.push_back(" - ");
    operators.push_back(" * ");
    operators.push_back(" / ");
    operators.push_back("^");

    srand( time(NULL) );

    useFunctions = false;
    calcFile = filename1;
    bcFile = filename2;
}

CalcTest::~CalcTest()
{
}

double CalcTest::getRValue()
{
	double value = (double) rand() / (double) rand();
	if(useFunctions)
		return value < 0? -value: value;
	else
		return value;
}

std::string CalcTest::getRName()
{
	std::string rname;
	for(int i = 0; i < 4; ++i)
		rname.push_back((char) rand()%20+65);
	return rname;
}

std::string CalcTest::getOperator() const
{
	return operators[rand() % operators.size()];
}

std::string CalcTest::getFunction() const
{
	return functions[rand() % functions.size()];
}

void CalcTest::generateExpr(int length)
{
	int newExpr;
	std::string strOp;
	std::string strFunc;

	while(--length >= 0)
	{
		if(rand() % 2 == 0)
		{
			outStr << getRValue();
		}
		else {
			newExpr = rand() % 4;
			if(newExpr > 0)
			{
				if(rand() % 2 == 0 && useFunctions)
				{
					strFunc = getFunction();
					outStr << strFunc;
				}
				outStr << "( ";
				if(strFunc == "e")
					outStr << rand() % MAX_EXPONENT;
				else if(strFunc == "sqrt")
					outStr << getRValue();
				else
					generateExpr(newExpr);
				outStr << " )";
				strFunc = "";
			}
			else {
				outStr << getRValue();
			}
		}
		if(length > 0)
		{
			strOp = getOperator();
			outStr << strOp;

			while(strOp == "^")
			{
				outStr << rand() % MAX_EXPONENT;
				strOp = operators[rand() % (operators.size()-1)];
				outStr << strOp;
			}
		}
	}
}

void CalcTest::runTest()
{
	int count = exprCount;
	while (--count > 0)
	{
		int length = rand() % maxExprLength;
		generateExpr(length);
		outStr << std::endl;
	}

	std::ofstream fcal(calcFile.c_str());
	std::ofstream fbc(bcFile.c_str());
	fcal << "define l(x) = ln(x)\n"
			"define s(x) = sin(x)\n"
			"define c(x) = cos(x)\n"
			"define a(x) = atan(x)\n";
	fcal << outStr.str();
	fbc << outStr.str();
	std::cout << outStr.str();
}

void CalcTest::variablesCheck()
{
	std::string rname;

	std::ofstream fcal(calcFile.c_str());
	std::ofstream fbc(bcFile.c_str());

	int count = exprCount;
	while (--count > 0)
	{
		int length = rand() % maxExprLength;
		rname = getRName();

		fcal << "define " + rname + "() = ";
		fbc << "define " + rname + "() { return (";
		generateExpr(length);
		fcal << outStr.str() << std::endl;
		fbc << outStr.str() << "); }\n";
		outStr.flush();
		outStr << rname << "=" << rname << "();" << std::endl;
		outStr << rname << "() !=" << rname << std::endl;
		fcal << outStr.str();
		fbc << outStr.str();
		outStr.flush();
	}
}

