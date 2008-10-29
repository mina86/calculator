/** \file
 * User Function class definition.
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


real UserFunction::execute(Environment &env, const Arguments &args) const
{
	throwIfArgumentsCountNotOK(args.size());

	std::auto_ptr<Environment::Variables> vars(new Environment::Variables());
	std::transform(names.begin(), names.end(), args.begin(),
	               std::inserter(*vars, vars->begin()),
	               &std::make_pair<const std::string, real>);

	try {
		return env.executeInNewScope(expr, vars);
	}
	catch (ReturnException &e) {
		if (e.end()) {
			return e.getValue();
		} else {
			throw;
		}
	}
}


real UserFunction::execute(Environment &env,
                           const std::vector<Expression *> &args) const
{
	throwIfArgumentsCountNotOK(args.size());

	std::auto_ptr<Environment::Variables> vars(new Environment::Variables());
	std::vector<Expression*>::const_iterator it(args.begin()),end(args.end());
	Names::const_iterator n(names.begin());
	for (; it != end; ++it, ++n) {
		vars->insert(std::make_pair(*n, (*it)->execute(env)));
	}
	try {
		return env.executeInNewScope(expr, vars);
	}
	catch (ReturnException &e) {
		if (e.end()) {
			return e.getValue();
		} else {
			throw;
		}
	}
}

}
