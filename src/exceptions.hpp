/** \file
 * Exception definitions.
 * $Id: exceptions.hpp,v 1.1 2008/02/08 21:47:32 mina86 Exp $
 */
#ifndef H_EXCEPTIONS_HPP
#define H_EXCEPTIONS_HPP


#include <string>


namespace calc {


/** A generic, abstract exception class. */
struct Exception {
	/** Returns error message. */
	const std::string &getMessage() const { return message; }

protected:
	/**
	 * Constructs exception and sets error message.
	 * \param message_ error message.
	 */
	Exception(const std::string &message_) : message(message_) { }

private:
	/** Default constructor not allowed. */
	Exception() { }

	/** Stores error message. */
	const std::string message;
};


/** An I/O exception class. */
struct IOException : public Exception {
	/**
	 * Constructs exception and sets error message.
	 * \param message_ error message.
	 */
	IOException(const std::string &message_) : Exception(message_) { }
};


/** Exception class regarding functions. */
struct FunctionException : public Exception {
	/**
	 * Constructs exception and sets error message.
	 * \param message_ error message.
	 */
	FunctionException(const std::string &message_) : Exception(message_) { }
};


/**
 * Exception thrown when an invalid number of arguments was passed to
 * function.
 */
struct InvalidNumberOfArguments : public FunctionException {
	/** Constructos exception. */
	InvalidNumberOfArguments() : FunctionException(error_msg) { }

private:
	/** Exception error message. */
	static const std::string error_msg;
};


/**
 * Exception thrown when function that does not exist was called.
 */
struct NoSuchFunction : public FunctionException {
	/** Constructos exception. */
	NoSuchFunction() : FunctionException(error_msg) { }

private:
	/** Exception error message. */
	static const std::string error_msg;
};


}

#endif
