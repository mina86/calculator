/**
 * file: CalcTest.h
 * author: Jakub Księżniak
 */
#ifndef CALCTEST_H_
#define CALCTEST_H_

#include <map>
#include <deque>
#include <string>
#include <sstream>

class CalcTest
{
	typedef std::map<std::string, int> FUNC_MAP;
	typedef std::deque<std::string> STR_DEQUE;
	
	// helper structures
	STR_DEQUE functions;
	STR_DEQUE operators;
	
	std::string calcFile;
	std::string bcFile;
	std::stringstream outStr;
	
	// number of generated expressions and their length
	const int exprCount, maxExprLength;
	
	// determines if functions are used in expressions
	bool useFunctions;
	
	// gets random value
	double getRValue();
	
	// gets random name for variable
	std::string getRName();

	// function gets random operator
	std::string getOperator() const;
	
	// function gets random math-function
	std::string getFunction() const;
	
	// generates expression
	void generateExpr(int length);
public:
	/*
	 * /param count      number of generated expressions
	 * /param len        length of generated expressions
	 * /param filename1  name of file written for calc
	 * /param filename2  name of file written for bc
	 */
	CalcTest(const int &count, const int &len, const std::string &filename1, const std::string &filename2);
	virtual ~CalcTest();
	
	/*
	 * runs standard test.
	 */
	void runTest();
	
	/*
	 * Tests variables and user defined functions
	 */
	void variablesCheck();
	
	/*
	 * Sets usage of math functions with expressions. 
	 */
	void setUsingFunctions(const bool &use) { useFunctions = use; };
};

#endif /*CALCTEST_H_*/
