/** \file
 * User Function class declaration.
 * $Id: user-function.hpp,v 1.3 2008/04/16 11:57:16 mina86 Exp $
 */
#ifndef H_USER_FUNCTION_HPP
#define H_USER_FUNCTION_HPP

#include "config.hpp"

#include "function.hpp"
#include "exceptions.hpp"


namespace calc {


struct Expression;


/** Class representing a user-defined function. */
struct UserFunction : public Function {
	/** Names of function's formal arguments. */
	typedef std::vector<std::string> Names;

	/**
	 * Constructor.
	 * \param e function's body.
	 * \param n function's formal arguments' names.
	 */
	UserFunction(Expression *e, const Names &n)
		: expr(e), names(n) { }

	/** Deletes function's body. */
	~UserFunction();

	/**
	 * Returns \c true iff \a count equals <code>names.size()</code>.
	 * \param count number of arguements.
	 */
	virtual bool argumentsCountOK(unsigned count) const;

	virtual real execute(Environment &env, const real *args, unsigned count)
		const;

	/** Delets object. */
	virtual void free();

private:
	/** Function's body. */
	Expression *expr;
	/** Names of function's formal arguments. */
	Names names;
};


}

#endif
