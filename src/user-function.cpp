/** \file
 * User Function class definition.
 * $Id: user-function.cpp,v 1.2 2008/04/12 12:58:46 mina86 Exp $
 */

#include "config.hpp"

#include "user-function.hpp"
#include "expression.hpp"
#include "environment.hpp"


namespace calc {

UserFunction::~UserFunction() {
	delete expr;
}

bool UserFunction::argumentsCountOK(unsigned count) const {
	return count == names.size();
}

void UserFunction::free() {
	delete this;
}

real UserFunction::execute(Environment &env, const real *args, 
                           unsigned count) const {
	if (count != names.size()) {
		throw InvalidNumberOfArguments();
	}

	return env.ExecuteInNewScope(expr, names, args);
}


}
