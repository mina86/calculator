/*
 * Copyright 2008-2009 by Michal Nazarewicz (mina86/AT/mina86.com)
 *                     by Jakub Ksiezniak
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

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

	CalcTest test("testcalc", "testbc");
	test.generateTest(count, maxExpr, useFunctions, varCheck);
	return 0;
}
