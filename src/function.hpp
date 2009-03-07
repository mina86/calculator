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
 * Function class declaration.
 */
#ifndef H_FUNCTION_HPP
#define H_FUNCTION_HPP

#include "config.hpp"

#include <string>
#include <vector>

#include "exceptions.hpp"


namespace calc {


struct Environment;
struct Expression;


/** A function available in environment. */
struct Function {
	typedef std::vector<real> Arguments;

	/** Virtual, empty destructor. */
	virtual ~Function();

	/**
	 * Returns whether number of arguments is OK.
	 * \param count number of arguments.
	 */
	virtual bool argumentsCountOK(unsigned count) const = 0;

	/**
	 * Executes function in given environment.
	 * \param env environment to run function in.
	 * \param args array of function call arguments.
	 * \return function's value.
	 * \throw InvalidNumberOfArguments if wrong number of arguments
	 *                                 was given.
	 * \throw NoSuchFunction if non-existing function was called.
	 * \throw ReturnException when 'return' pseudofunction was called.
	 * \throw BreakException  when 'break' pseudofunction was called.
	 */
	virtual real execute(Environment &env, const Arguments &args) const = 0;


	/**
	 * Executes function in given environment.
	 * \param env environment to run function in.
	 * \param args array of function call arguments.
	 * \return function's value.
	 * \throw InvalidNumberOfArguments if wrong number of arguments
	 *                                 was given.
	 * \throw NoSuchFunction if non-existing function was called.
	 * \throw ReturnException when 'return' pseudofunction was called.
	 * \throw BreakException  when 'break' pseudofunction was called.
	 */
	virtual real execute(Environment &env,
	                     const std::vector<Expression *> &args) const;

	/**
	 * Frees function object.  It is needed as some objects function
	 * objects are intended to be singletons and should never be
	 * deleted.  For such objects this method would do nothing.  Code
	 * that want to free a Function object must not use delete
	 * operator but rather this method.
	 */
	virtual void free() = 0;

	/**
	 * Throws InvalidNumberOfArguments exception if number of
	 * arguments is not OK.
	 * \param count number of arguments.
	 * \throw InvalidNumberOfArguments if wrong number of arguments
	 *                                 was given.
	 */
	void throwIfArgumentsCountNotOK(unsigned count) const {
		if (!argumentsCountOK(count)) {
			throw InvalidNumberOfArguments();
		}
	}


protected:
	/** Empty default constructor. */
	Function() { }

private:
	/**
	 * No copying allowed.
	 * \param func object to copy.
	 */
	Function(const Function &func) { (void)func; }
};


}

#endif
