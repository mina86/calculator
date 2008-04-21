/** \file
 * Function class declaration.
 * $Id: function.hpp,v 1.5 2008/04/21 08:27:39 mina86 Exp $
 */
#ifndef H_FUNCTION_HPP
#define H_FUNCTION_HPP

#include "config.hpp"

#include <string>
#include <vector>

#include "exceptions.hpp"


namespace calc {


struct Environment;


/** A function available in enviroment. */
struct Function {
	typedef std::vector<real> Arguments;

	/** Virtual, empty destructor. */
	virtual ~Function() { };

	/**
	 * Returns whether number of arguments is OK.
	 * \param count number of arguements.
	 */
	virtual bool argumentsCountOK(unsigned count) const = 0;

	/**
	 * Executes function in given enviroment.
	 * \param env enviroment to run function in.
	 * \param args array of function call arguments.
	 * \param count number of arguments.
	 * \return function's value.
	 * \throw InvalidNumberOfArguments if wrong number of arguments
	 *                                 was given.
	 * \throw NoSuchFunction if non-existing function was called.
	 */
	virtual real execute(Environment &env, const Arguments &args) const = 0;

	/**
	 * Frees function object.  It is needed as some objects function
	 * objects are intended to be singletons and shuld never be
	 * deleted.  For such objects this method would do nothing.  Code
	 * that want to free a Function object must not use delete
	 * operator but rather this method.
	 */
	virtual void free() = 0;

	/**
	 * Throws InvalidNumberOfArguments exception if number of
	 * arguments is not OK.
	 * \param count number of arguements.
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
