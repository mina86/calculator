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
