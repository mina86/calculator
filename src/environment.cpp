/** \file
 * Enviroment defintion.
 * $Id: environment.cpp,v 1.3 2008/04/12 12:57:11 mina86 Exp $
 */
#include "config.hpp"

#include "assert.h"

#include <iostream>

#include "environment.hpp"
#include "function.hpp"
#include "expression.hpp"


namespace calc {

Environment::~Environment() {
	Functions::iterator it = functions().begin(), end = functions().end();
	while (it != end) {
		it->second->free();
		++it;
	}
}

void Environment::error(const yy::position &pos, const std::string &msg) {
	std::cerr << *pos.filename << ':' << pos.line << ':'
	          << pos.column << ": " << msg << '\n';
}

void Environment::error(const std::string &msg) {
	std::cerr << msg << '\n';
}


void Environment::instruction(real value) {
	(void)value;
}




real Environment::ExecuteInNewScope(Expression *expr,
                                const UserFunction::Names &names,
                                const real *values) {
	NewScope local_scope(_stack);
	Environment::Variables &vars = local();
	UserFunction::Names::const_iterator n = names.begin(), end = names.end();
	while (n != end) {
		vars[*n] = *values;
		++values;
		++n;
	}

	return expr->execute(*this);
}

}
