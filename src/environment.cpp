/** \file
 * Enviroment defintion.
 * $Id: environment.cpp,v 1.2 2008/04/12 02:10:32 mina86 Exp $
 */
#include "config.hpp"

#include "assert.h"

#include <iostream>

#include "environment.hpp"
#include "function.hpp"


namespace calc {

Environment::~Environment() {
	delete _stack.back();
	_stack.pop_back();
	assert(_stack.size() == 0);

	{
		Functions::iterator it = functions().begin(), end = functions().end();
		while (it != end) {
			it->second->free();
			++it;
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
