/** \file
 * User Function class definition.
 * $Id: user-function.cpp,v 1.1 2008/04/12 02:19:15 mina86 Exp $
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

real UserFunction::execute(Environment &env, const Arguments &args) const {
	if (args.size() != names.size()) {
		throw InvalidNumberOfArguments();
	}

	Environment::Variables &local = env.enter();
	Names::const_iterator n = names.begin(), end = names.end();
	Arguments::const_iterator a = args.begin();
	while (n != end) {
		local[*n] = *a;
		++n;
		++a;
	}

	real val = expr->execute(env);

	env.leave();

	return val;
}


}
