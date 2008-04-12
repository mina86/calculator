/** \file
 * Enviroment declaration.
 * $Id: environment.hpp,v 1.4 2008/04/12 12:57:11 mina86 Exp $
 */
#ifndef H_ENVIRONMENT_HPP
#define H_ENVIRONMENT_HPP

#include "config.hpp"

#include <string>
#include <vector>
#include <map>

#include "exceptions.hpp"
#include "user-function.hpp"
#include "position.hh"
#include "location.hh"

namespace calc {




/**
 * Structure defines calculators environment that is variables,
 * constants and functions as well as the way errors and evaluated
 * instructions are printed.
 */
struct Environment {
	/** Type used to store functions. */
	typedef std::map<std::string, Function*> Functions;
	/** Type used to store variables. */
	typedef std::map<std::string, real> Variables;
	/** Type used to store execution stack. */
	typedef std::vector<Variables*> Stack;


	/** Default constructor. */
	Environment() : global_scope(_stack) { }


	/** An empty virtual destructor. */
	virtual ~Environment();

	/**
	 * Prints error message.
	 * \param pos position when error occured.
	 * \param msg error message
	 */
	virtual void error(const yy::position &pos, const std::string &msg);

	/**
	 * Prints error message.
	 * \param msg error message
	 */
	virtual void error(const std::string &msg);

	/**
	 * Prints result of executed instruction.
	 * \param value instruction's result.
	 */
	virtual void instruction(real value);


	/** Returns execution stack. */
	const Stack &stack() { return _stack; }

	/** Returns local (the most nested) stack frame. */
	Variables &local() { return *_stack.back(); }

	/** Returns local (the most nested) stack frame. */
	const Variables &local() const { return *_stack.back(); }

	/** Returns global (outer) stack frame. */
	Variables &global() { return *_stack.front(); }

	/** Returns global (outer) stack frame. */
	const Variables &global() const { return *_stack.front(); }

	/** Returns constants. */
	Variables &constants() { return _constants; }

	/** Returns constants. */
	const Variables &constants() const { return _constants; }


	/**
	 * Returns value from given map or zero if it does not exist.
	 * \param map  map to search in.
	 * \param name variable's name.
	 */
	static real get(const Variables &map, const std::string &name) {
		Variables::const_iterator it = map.find(name);
		return it == map.end() ? 0 : it->second;
	}



	/**
	 * Executes expression in new context.  Creates new stack frame,
	 * assigns local variables and executes expression.
	 *
	 * \param expr expression to execute
	 * \param names list of local variables names
	 * \param values list of local variables values
	 * \return value returned by expression.
	 */
	real ExecuteInNewScope(Expression *expr, const UserFunction::Names &names,
	                       const real *values);


	/** Returns functions map. */
	Functions &functions() { return _functions; }

	/** Returns functions map. */
	const Functions &functions() const { return _functions; }

	/**
	 * Returns function with given name or 0 if it does not exist.
	 * \param name function's name.
	 */
	const Function *getFunction(const std::string &name) const {
		Functions::const_iterator it = functions().find(name);
		return it == functions().end() ? 0 : it->second;
	}


private:
	/** Execution stack. */
	Stack _stack;
	/** Stored constants. */
	Variables _constants;
	/** Pointers to functions. */
	Functions _functions;


	struct NewScope {
		NewScope(Stack &s) : stack(s) {
			stack.push_back(new Variables());
		}

		~NewScope() {
			delete stack.back();
			stack.pop_back();
		}

	private:
		Stack &stack;
	} global_scope;


	/**
	 * Copying not allowed (yet).
	 * \param env object to copy.
	 */
	Environment(const Environment &env) : global_scope(_stack) {
		(void)env;
	}
};

}

#endif
