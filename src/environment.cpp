/** \file
 * Enviroment defintion.
 * $Id: environment.cpp,v 1.7 2008/06/05 20:35:34 mina86 Exp $
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
	for (; it != end; ++it) {
		it->second->free();
	}
}

void Environment::execute(const Expression *expr, bool verbose) {
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
