/**
 * file: main.cpp
 * author: Jakub Księżniak
 * Description: App generating test expressions for calc and bc.
 */

#include <iostream>
#include <cstdlib>
#include "CalcTest.h"

#define DEFAULT_COUNT 10
#define DEFAULT_MAXEXPR 10

int main (int argc, char *argv[])
{
	int count = DEFAULT_COUNT;
	int maxExpr = DEFAULT_MAXEXPR;
	bool useFunctions = false;
	bool varCheck = false;
	
	int i = 1;
	for ( ; i < argc && argv[i][0] == '-' && argv[i][1]; ++i)
	{
		if (argv[i][1] == '-' && argv[i][2] == 0)
		{
			++i;
			break;
		}

		for (char *ch = argv[i]; *++ch; )
		{
			switch (*ch)
			{
			case 'f':
				useFunctions = true;               
				break;			
			case 'v':
				varCheck = true;
				break;
			case 'h':
				std::cout << "usage: ./calc_test [-fvh]\n"
							 " f - uses mathematic functions in expressions\n"
							 " v - expressions testing variables for calc\n"
							 " h - print this help\n";
			default:
				std::cerr << "invalid option: " << *ch << '\n';
				return 1;
			}
		}
	}
	
	CalcTest test(count, maxExpr, "testcalc", "testbc");

	test.setUsingFunctions(useFunctions);
	
	if(!varCheck)
		test.runTest();
	else
		test.variablesCheck();
	return 0;
}


