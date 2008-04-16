/** \file
 * Exception definitions.
 * $Id: exceptions.hpp,v 1.4 2008/04/16 11:57:16 mina86 Exp $
 */
#ifndef H_EXCEPTIONS_HPP
#define H_EXCEPTIONS_HPP


#include <stdexcept>


namespace calc {



/** An I/O exception class. */
struct IOException : public std::runtime_error {
	/**
	 * Constructs exception and sets error message.
	 * \param message error message.
	 */
	IOException(const std::string &message) throw()
		: std::runtime_error(message) { }
};


/** Base Exception thrown by Expression classes. */
struct ExpressionException : public std::runtime_error {
protected:
	/**
	 * Constructs exception and sets error message.
	 * \param message error message.
	 */
	ExpressionException(const std::string &message) throw()
		: std::runtime_error(message) { }
};

/**
 * Thrown by SetConstExpression when trying to set already defined
 * constant's value.
 */
struct ConstAlreadyDefined : public ExpressionException {
	/** Constructos exception. */
	ConstAlreadyDefined() throw()
		: ExpressionException("constant already defined") { }
};


/** Exception class regarding functions. */
struct FunctionException : public ExpressionException {
protected:
	/**
	 * Constructs exception and sets error message.
	 * \param message error message.
	 */
	FunctionException(const std::string &message) throw()
		: ExpressionException(message) { }
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
