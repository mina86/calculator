/** \file
 * Enviroment defintion.
 * $Id: environment.cpp,v 1.1 2008/02/08 21:47:32 mina86 Exp $
 */
#include "config.hpp"

#include <iostream>

#include "environment.hpp"


namespace calc {

Environment::~Environment() { }

void Environment::error(const yy::position &pos, const std::string &msg) {
	std::cerr << *pos.filename << ':' << pos.line << ':'
	          << pos.column << ": " << msg << '\n';
}

void Environment::instruction(real value) {
	(void)value;
}

}
