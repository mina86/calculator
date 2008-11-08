/** \file
 * Lexer reading from FILE stream declaration.
 */
#ifndef H_FILE_LEXER_HPP
#define H_FILE_LEXER_HPP

#include "config.hpp"

#include <stdio.h>
#include <string.h>

#include "lexer.hpp"


namespace calc {


/**
 * Lexer structure reading data from a FILE (as defined in C language).
 */
struct FILELexer : public Lexer {
	/**
	 * Creates lexer reading from a file.  If \a stream_ is \c NULL
	 * constructor will try to open file specified by \a filename_,
	 * otherwise it will use \a stream_ as input stream and assume
	 * filename_ is corresponding file name.
	 *
	 * \param filename_ file name, NULL means standard input.
	 * \param stream_ input stream to read from or \c NULL.
	 * \throw IOException if file could not be opened.
	 */
	explicit FILELexer(const char *filename_ = 0, FILE *stream_ = 0)
		: Lexer (filename_ ? filename_ : stdin_filename),
		  stream(stream_ ?stream_ : (filename_? openFile(filename_) : stdin)),
		  closeStream(!stream_ && filename_), previous(current) { }

	/**
	 * Closes stream unless it was given directly in constructor.
	 */
	~FILELexer();

	virtual int nextToken(yy::Parser::semantic_type &value,
	                      yy::location &location);


private:
	/**
	 * Opens given file in read only mode.
	 * \param filename name of the file to open.
	 * \return opened stream.
	 * \throw IOException on error.
	 */
	static FILE *openFile(const char *filename);

	/** Returns next character from file and updates location. */
	int getChar();
	/** Reads a string character preceeded by "\" and returns it. */
	char getDecodedChar();
	/**
	 * "Ungets" character from file and updates location.
	 * \param ch character to unget.
	 */
	void ungetChar(int ch);

	/** Name of a standard input stream. */
	static const std::string stdin_filename;

	/** Stream to read data from. */
	FILE *stream;

	/** Whether stream should be closed by destructor. */
	bool closeStream;

	/** A position in stream before last character was read. */
	yy::position previous;
};



}


#endif
