/** \file
 * Enviroment declaration.
 * $Id: environment.hpp,v 1.2 2008/02/29 22:29:34 mina86 Exp $
 */
#ifndef H_ENVIRONMENT_HPP
#define H_ENVIRONMENT_HPP

#include "config.hpp"

#include <string>
#include <vector>
#include <map>
#if HAVE_TR1_UNORDERED_MAP
#  include <tr1/unordered_map>
#endif
#include <ostream>

#include "exceptions.hpp"
#include "position.hh"
#include "location.hh"

namespace calc {


/** Type used to pass arguments to calculator functions. */
typedef std::vector<real> FunctionArguments;
/** A pointer to calculator function. */
typedef real (*Function)(const FunctionArguments &arguments);


/**
 * Structure defines calculators environment that is variables,
 * constants and functions as well as the way errors and evaluated
 * instructions are printed.
 */
struct Environment {
#if HAVE_TR1_UNORDERED_MAP
	/** Type used to store constants. */
	typedef std::tr1::unordered_map<std::string, real> Constants;
	/** Type used to store functions. */
	typedef std::tr1::unordered_map<std::string, Function> Functions;
#else
	/** Type used to store constants. */
	typedef std::map<std::string, real> Constants;
	/** Type used to store functions. */
	typedef std::map<std::string, Function> Functions;
#endif
	/** Type used to store variables. */
	typedef std::map<std::string, real> Variables;


	/** An empty virtual destructor. */
	virtual ~Environment();

	/**
	 * Prints error message.
	 * \param pos position when error occured.
	 * \param msg error message
	 */
	virtual void error(const yy::position &pos, const std::string &msg);

	/**
	 * Prints result of executed instruction.
	 * \param value instruction's result.
	 */
	virtual void instruction(real value);


	/**
	 * Sets variable's value.
	 * \param name variable's name.
	 * \param value value to set.
	 * \return \a value.
	 */
	real set(const std::string &name, real value) {
		return variables_trans[name] = value;
	}

	/**
	 * Returns variable's value or zero if it does not exist.
	 * \param name variable's name.
	 */
	real get(const std::string &name) const {
		Variables::const_iterator it = variables_trans.find(name);
		return
			it == variables_trans.end() &&
			(it = variables.find(name)) == variables.end()
			? 0.0 : it->second;
	}

	/** Commits changed variables. */
	void commit() {
		Variables::const_iterator it = variables_trans.begin();
		Variables::const_iterator end = variables_trans.end();
		for (; it != end; ++it) {
			variables[it->first] = it->second;
		}
		variables_trans.clear();
	}

	/** Rejects changed variables. */
	void reject() {
		variables_trans.clear();
	}


	/**
	 * Returns constant's value or zero if it does not exist.
	 * \param name constant's name.
	 */
	real getConst(const std::string &name) const {
		Constants::const_iterator it = constants.find(name);
		return it == constants.end() ? 0.0 : it->second;
	}

	/**
	 * Executes function with given arguments.
	 * \param name function's name.
	 * \param arguments arguments passed to function.
	 * \return function's result.
	 * \throw NoSuchFunction if function does not exist.
	 * \throw FunctionException if function exist but there are other
	 *                          errors like wrong number of arguments.
	 */
	real run(const std::string &name,
	         const std::vector<real> &arguments) const {
		Functions::const_iterator it = functions.find(name);
		if (it == functions.end()) {
			throw NoSuchFunction();
		} else {
			return it->second(arguments);
		}
	}


	/** Stored variables. */
	Variables variables;
	/** Current transaction chagnes. */
	Variables variables_trans;
	/** Stored constants. */
	Constants constants;
	/** Pointers to functions. */
	Functions functions;
};

}

namespace std {

/**
 * Prints function arguments.
 * \param o output stream to print to.
 * \param a arguments to print.
 * \return \a o.
 */
inline std::ostream &operator<<(std::ostream &o,
                                const calc::FunctionArguments &a) {
	calc::FunctionArguments::const_iterator it = a.begin(), end = a.end();
	if (it == end) {
		return o << "()";
	}

	o << '(' << *it;
	while (++it != end) {
		o << ", " << *it;
	}
	return o << ')';
}

}

#endif
