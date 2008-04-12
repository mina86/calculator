/** \file
 * User Function class definition.
 * $Id: user-function.cpp,v 1.3 2008/04/12 13:54:37 mina86 Exp $
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
	throwIfArgumentsCountNotOK(count);
	return env.ExecuteInNewScope(expr, names, args);
}


}
