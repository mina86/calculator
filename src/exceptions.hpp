/** \file
 * Exception definitions.
 * $Id: exceptions.hpp,v 1.9 2008/06/05 20:36:27 mina86 Exp $
 */
#ifndef H_EXCEPTIONS_HPP
#define H_EXCEPTIONS_HPP


#include <stdexcept>
#include <string>

namespace calc {



/** An I/O exception class. */
struct IOException : public std::runtime_error {
	/**
	 * Constructs exception and sets error message.
	 * \param message error message.
	 */
	explicit IOException(const std::string &message) throw()
		: std::runtime_error(message) { }
};


/** Base Exception thrown by Expression classes. */
struct ExpressionException : public std::runtime_error {
protected:
	/**
	 * Constructs exception and sets error message.
	 * \param message error message.
	 */
	explicit ExpressionException(const std::string &message) throw()
		: std::runtime_error(message) { }
};

/**
 * Thrown by SetConstExpression when trying to set already defined
 * constant's value.
 */
struct ConstAlreadyDefined : public ExpressionException {
	/** Constructors exception. */
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
	explicit FunctionException(const std::string &message) throw()
		: ExpressionException(message) { }
};


/**
 * Exception thrown when an invalid number of arguments was passed to
 * function.
 */
struct InvalidNumberOfArguments : public FunctionException {
	/** Constructors exception. */
    InvalidNumberOfArguments() throw()
        : FunctionException("invalid number of arguments") { }
	InvalidNumberOfArguments(const std::string &msg) throw()
        : FunctionException("invalid number of arguments for function: " + msg) { }
};


/**
 * Exception thrown when function that does not exist was called.
 */
struct NoSuchFunction : public FunctionException {
	/** Constructors exception. */
    NoSuchFunction(const std::string &msg) throw()
        : FunctionException("no such function: " + msg) {}
};


}

#endif
