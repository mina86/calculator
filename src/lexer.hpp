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
 * Defines an abstract lexer.
 */
#ifndef H_LEXER_HPP
#define H_LEXER_HPP


#include <string>

#include "parser.hpp"
#include "position.hh"
#include "location.hh"


namespace calc {


/** Abstract lexer structure. */
struct Lexer {
	/** An empty virtual destructor. */
	virtual ~Lexer() { }

	/**
	 * Returns next token from stream.
	 * \param value structure to save value to.
	 * \param location structure to update location in stream of given
	 *        token.
	 * \return read token.
	 */
	virtual int nextToken(yy::Parser::semantic_type &value,
	                      yy::location &location) = 0;

	/** Returns current position in stream. */
	const yy::position &getPosition() const { return current; }


protected:
	/** Current position in stream. */
	yy::position current;

	/**
	 * Intialises lexer.
	 * \param filename_ name of the file we are reading from.
	 * \param line line number we are at.
	 * \param col column number we are at.
	 */
	Lexer(const std::string &filename_, unsigned line = 1, unsigned col = 1)
		: filename(filename_) {
		current.filename = &filename;
		current.line = line;
		current.column = col;
	}


private:
	/** Name of the file we are reading from. */
	std::string filename;

	/** No default constructor. */
	Lexer() { }

	/**
	 * Copying not allowed.
	 * \param lexer object to copy.
	 */
	Lexer(const Lexer &lexer) { (void)lexer; }
};


}


#endif
