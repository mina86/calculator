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
 * Exception definitions.
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
