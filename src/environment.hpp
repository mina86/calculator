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
 * Enviroment declaration.
 */
#ifndef H_ENVIRONMENT_HPP
#define H_ENVIRONMENT_HPP

#include "config.hpp"

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "expression.hpp"
#include "function.hpp"
#include "position.hh"
#include "location.hh"

namespace calc {


struct Lexer;



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


	/**
	 * Constructor.
	 * \param p precision for comparison operators.
	 * \param fp precision for fuzzy comparison operators.
	 */
	explicit Environment(real p = 0, real fp = 1.0e-9)
		: _precision(p), _fuzzy_precision(fp), global_scope(_stack),
		  _iteration(_constants["#"]), _last(_constants["!"]) {
		_iteration = _last = 0;
	}


	/** An empty virtual destructor. */
	virtual ~Environment();

	/**
	 * Executes expression on given expression.
	 * \param expr expression to evaluate.
	 * \param verbose if set true, calls instruction().
	 * \return expression's result.
	 */
	void execute(const Expression *expr, bool verbose);

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

	/** Returns reference to ## constant's value. */
	real &iteration_value() { return _iteration; }

	/** Returns reference to ## constant's value. */
	const real &iteration_value() const { return _iteration; }

	/** Returns reference to #! constant's value. */
	real &last_value() { return _last; }

	/** Returns reference to #! constant's value. */
	const real &last_value() const { return _last; }



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
	 * \param scope initial variables in scope; this object will be
	 *              deleted after function returns or throws exception.
	 */
	real executeInNewScope(Expression *expr, std::auto_ptr<Variables> scope) {
		NewScope local_scope(_stack, scope);
		return expr->execute(*this);
	}


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

	/** Method adds new user function definition. If function is defined,
	 *  it is replaced by new definition.
	 *  \param name function's name.
	 *  \param func new function object.
	 */
	void addUserFunction(const std::string &name, Function *func) {
		Function* &f = functions()[name];
		if (f) {
			f->free();
		}
		f = func;
	}


	/**
	 * Returns precision for (fuzzy) comparison operators.
	 * \param fuzzy whether to return precision for fuzzy comparison.
	 */
	real precision(bool fuzzy = false) const {
		return fuzzy ? _fuzzy_precision : _precision;
	}



	/** Returns lexer used by read calculator function. */
	Lexer *getReadLexer() const {
		return readLexer;
	}

	/**
	 * Sets lexer used by read calculator function.
	 * \param lexer new lexer;
	 */
	void setReadLexer(Lexer *lexer) {
		readLexer = lexer;
	}


private:
	/** Execution stack. */
	Stack _stack;
	/** Stored constants. */
	Variables _constants;
	/** Pointers to functions. */
	Functions _functions;
	/** Precision for comparison oeprators. */
	real _precision;
	/** Precision for fuzzy comparison oeprators. */
	real _fuzzy_precision;
	/** Lexer used by read calculator function. */
	Lexer *readLexer;

	/**
	 * A private class for running expressions in their own scope.
	 * It's constructor creates new scope and destructor removes it.
	 */
	struct NewScope {
		/**
		 * Constructor using given scope as a new local scope on stack.
		 * \param s stack to create new scope on.
		 */
		explicit NewScope(Stack &s) : stack(s) {
			std::auto_ptr<Variables> vars(new Variables());
			stack.push_back(vars.get());
			vars.release();
		}

		/**
		 * Constructor using given scope as a new local scope on stack.
		 * \param s stack to create new scope on.
		 * \param vars object to use as a new local scope; it will be
		 *             deleted when object is destroyed or constructor
		 *             throws exception.
		 */
		NewScope(Stack &s, std::auto_ptr<Variables> vars) : stack(s) {
			stack.push_back(vars.get());
			vars.release();
		}

		/** Discards top-level scope from the stack. */
		~NewScope() {
			delete stack.back();
			stack.pop_back();
		}

	private:
		/** Stack class operats on. */
		Stack &stack;
	};

	/**
	 * Since Environment class has instance of NewScope class when
	 * Environment is created a new local (which is global at the same
	 * time) scope is created and it is later discarded when
	 * Environment object is destroyed.
	 */
	NewScope global_scope;


	/** Reference to ## constant's value. */
	real &_iteration;
	/** Reference to #! constant's value. */
	real &_last;


	/**
	 * Copying not allowed (yet).
	 * \param e object to copy.
	 */
	Environment(const Environment &e)
		: global_scope(_stack), _iteration(e._iteration), _last(e._last) {}
};

}

#endif
