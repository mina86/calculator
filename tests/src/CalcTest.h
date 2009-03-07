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
 * file: CalcTest.h
 * author: Jakub Księżniak
 */
#ifndef CALCTEST_H_
#define CALCTEST_H_

#include <stdlib.h>

#include <map>
#include <vector>
#include <string>
#include <sstream>

struct CalcTest {
	/**
	 * Constructor.
	 * \param count      number of generated expressions
	 * \param len        length of generated expressions
	 * \param filename1  name of file written for calc
	 * \param filename2  name of file written for bc
	 */
	CalcTest(const std::string &filename1, const std::string &filename2)
		: calcFile(filename1), bcFile(filename2) {
		init();
	}

	/**
	 * Prepares test.
	 * \param count number of expressions.
	 * \param len maximal length of an expression.
	 * \param useFunctions whether to use functions.
	 * \param vars whether to test variables.
	 */
	void generateTest(unsigned count = 10, unsigned maxLen = 10,
	                  bool useFunctions = false, bool vars = false);



private:
	static std::vector<std::string> functions; /** Available functions. */
	static std::vector<std::string> operators; /** Available operators. */

	/** Initialises functions and operators. */
	static void init();

	/**
	 * Returns random value.
	 * \param abs whether to return abstract value (non-negative number).
	 */
	static double getRValue(bool abs = false) {
		double value = (double) rand() / (double) rand();
		return abs && value < 0 ? -value : value;
	}

	/** Returns random name. */
	static std::string getRName();

	/**
	 * Returns random operator.
	 * \param skipExp whether to skip '^' operator.
	 */
	static std::string getOperator(bool skipExp = false)
	{
		return operators[rand() % (operators.size() - skipExp)];
	}

	/* Returns random math function. */
	static std::string getFunction()
	{
		return functions[rand() % functions.size()];
	}

	/**
	 * Generates expression.
	 * \param out output stream to write expression to.
	 * \param len length of an expression.
	 * \param useFunctions whether to use functions.
	 */
	static void generateExpr(std::ostream &outStr, unsigned length,
	                         bool useFunctions);


	std::string calcFile; /**< Calc input file name. */
	std::string bcFile;   /**< bc input file name. */
};

#endif /*CALCTEST_H_*/
