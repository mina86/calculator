/** \file
 * Enviroment defintion.
 * $Id: environment.cpp,v 1.5 2008/05/10 10:05:26 kuba Exp $
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

void Environment::execute(const Expression *expr, const bool &verbose) {
	try {
		double result = expr->execute(*this);
		if (verbose) {
			instruction(result);
		}
	}
	catch(ExpressionException &e) {
		error( e.what() );
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


}
