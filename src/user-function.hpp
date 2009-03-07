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

/** \file
 * User Function class declaration.
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
	 * Returns \c true if \a count equals <code>names.size()</code>.
	 * \param count number of arguements.
	 */
	virtual bool argumentsCountOK(unsigned count) const;

	virtual real execute(Environment &env, const Arguments &args) const;
	virtual real execute(Environment &env,
	                     const std::vector<Expression *> &args) const;

	/** Deletes object. */
	virtual void free();

private:
	/** Function's body. */
	Expression *expr;
	/** Names of function's formal arguments. */
	Names names;
};


}

#endif
