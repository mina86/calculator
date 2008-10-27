/** \file
 * Enviroment defintion.
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
	catch (const ExpressionException &e) {
		error( e.what() );
	}
	catch (EscapeException &e) {
		if (verbose) {
			instruction(e.getValue());
		}
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
