/** \file
 * Defines an abstract lexer.
 * $Id: lexer.hpp,v 1.1 2008/02/08 21:47:32 mina86 Exp $
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
