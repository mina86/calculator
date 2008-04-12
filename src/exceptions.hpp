/** \file
 * Exception definitions.
 * $Id: exceptions.hpp,v 1.2 2008/04/12 02:12:04 mina86 Exp $
 */
#ifndef H_EXCEPTIONS_HPP
#define H_EXCEPTIONS_HPP


#include <stdexcept>


namespace calc {



/** An I/O exception class. */
struct IOException : public std::runtime_error {
	/**
	 * Constructs exception and sets error message.
	 * \param message_ error message.
	 */
	IOException(const std::string &message) throw()
		: std::runtime_error(message) { }
};


/** Exception class regarding functions. */
struct FunctionException : public std::runtime_error {
	/**
	 * Constructs exception and sets error message.
	 * \param message_ error message.
	 */
	FunctionException(const std::string &message) throw()
		: std::runtime_error(message) { }
};


/**
 * Exception thrown when an invalid number of arguments was passed to
 * function.
 */
struct InvalidNumberOfArguments : public FunctionException {
	/** Constructos exception. */
	InvalidNumberOfArguments() throw()
		: FunctionException("invalid number of arguments") { }
};


/**
 * Exception thrown when function that does not exist was called.
 */
struct NoSuchFunction : public FunctionException {
	/** Constructos exception. */
	NoSuchFunction() throw() : FunctionException("no such function") { }
};


}

#endif
