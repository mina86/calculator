/** \file
 * User Function class definition.
 * $Id: user-function.cpp,v 1.5 2008/04/21 10:14:04 mina86 Exp $
 */

#include "config.hpp"

#include <memory>
#include <iterator>

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
	throwIfArgumentsCountNotOK(args.size());

	std::auto_ptr<Environment::Variables> vars(new Environment::Variables());
	Names::const_iterator ni(names.begin()), ne(names.end());
	Arguments::const_iterator it(args.begin());
	for (; ni != ne; ++ni, ++it) {
		vars->insert(std::make_pair(*ni, *it));
	}

	return env.executeInNewScope(expr, vars.release());
}


real UserFunction::execute(Environment &env,
                           const std::vector<Expression *> &args) const {
	throwIfArgumentsCountNotOK(args.size());

	throwIfArgumentsCountNotOK(args.size());

	std::auto_ptr<Environment::Variables> vars(new Environment::Variables());
	Names::const_iterator ni(names.begin()), ne(names.end());
	std::vector<Expression*>::const_iterator it(args.begin());
	for (; ni != ne; ++ni, ++it) {
		vars->insert(std::make_pair(*ni, (*it)->execute(env)));
	}

	return env.executeInNewScope(expr, vars.release());
}

}
