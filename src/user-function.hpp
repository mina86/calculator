/** \file
 * User Function class declaration.
 * $Id: user-function.hpp,v 1.1 2008/04/12 02:19:15 mina86 Exp $
 */
#ifndef H_USER_FUNCTION_HPP
#define H_USER_FUNCTION_HPP

#include "config.hpp"

#include "function.hpp"
#include "exceptions.hpp"


namespace calc {


struct Expression;


struct UserFunction : public Function {
	typedef std::vector<std::string> Names;

	UserFunction(Expression *e, const Names &n)
		: expr(e), names(n) { }
	~UserFunction();

	virtual bool argumentsCountOK(unsigned count) const;
	virtual real execute(Environment &env, const Arguments &args) const;
	virtual void free();

private:
	Expression *expr;
	Names names;
};


}

#endif
