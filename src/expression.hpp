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
 * Expression declarations.
 */
#ifndef H_EXPRESSION_HPP
#define H_EXPRESSION_HPP

#include "config.hpp"

#include <assert.h>

#include <string>
#include <vector>



namespace calc {

struct Environment;
struct BooleanExpression;
struct CommaExpression;


/** An abstract expression class. */
struct Expression {
	/**
	 * Evaluats expression in given environment.
	 * \param env environment to execute expression in.
	 * \return expression's result.
	 * \throw ReturnException when 'return' pseudofunction was called.
	 * \throw BreakException  when 'break' pseudofunction was called.
	 */
	virtual real execute(Environment &env) const = 0;

	/**
	 * Evaluats expression in given environment and interpretes its
	 * result as boolean value.
	 * \param env environment to execute expression in.
	 * \return expression's result interpreted as boolean value.
	 * \throw ReturnException when 'return' pseudofunction was called.
	 * \throw BreakException  when 'break' pseudofunction was called.
	 */
	virtual bool boolean(Environment &env) const;


	/**
	 * If this is a CommaExpression returns it otherwise returns new
	 * CommaExpression with this expression as the only one.
	 */
	virtual CommaExpression *commaExpression();

	/** Returns BooleanExpression interpreting value of this Expression. */
	virtual BooleanExpression *booleanExpression();


	/** Virtual destructor. */
	virtual ~Expression() { }

protected:
	/** Empty default constructor (so it is available for derived
	 * classes). */
	Expression() { }

private:
	/**
	 * No copy constructor.
	 * \param expr object to copy.
	 */
	Expression(const Expression &expr) { (void)expr; }
};


/** An abstract \a n argument expression. */
template<unsigned n, class BaseExpression = Expression>
struct NArgExpression : public BaseExpression {
	/** Deletes all arguments. */
	~NArgExpression() {
		for (unsigned i = 0; i < n; ++i) {
			delete expressions[i];
		}
	}


protected:
	/**
	 * Constructor when \a n = 1.
	 * \param e1 first argument.
	 */
	explicit NArgExpression(Expression *e1) {
		typedef int static_assert[n == 1 ? 1 : -1];
		expressions[0] = e1;
	}

	/**
	 * Constructor when \a n = 1.
	 * \param e1 first argument.
	 * \param val additional argument for base constructor.
	 */
	template<class T>
	explicit NArgExpression(Expression *e1, T val) : BaseExpression(val) {
		typedef int static_assert[n == 1 ? 1 : -1];
		expressions[0] = e1;
	}

	/**
	 * Constructor when \a n = 2.
	 * \param e1 first argument.
	 * \param e2 second argument.
	 */
	NArgExpression(Expression *e1, Expression *e2) {
		typedef int static_assert[n == 2 ? 1 : -1];
		expressions[0] = e1, expressions[1] = e2;
	}

	/**
	 * Constructor when \a n = 2.
	 * \param e1 first argument.
	 * \param e2 second argument.
	 * \param val additional argument for base constructor.
	 */
	template<class T>
	NArgExpression(Expression *e1, Expression *e2, T val)
		: BaseExpression(val) {
		typedef int static_assert[n == 2 ? 1 : -1];
		expressions[0] = e1, expressions[1] = e2;
	}

	/**
	 * Constructor when \a n = 3.
	 * \param e1 first argument.
	 * \param e2 second argument.
	 * \param e3 third argument.
	 */
	NArgExpression(Expression *e1, Expression *e2, Expression *e3) {
		typedef int static_assert[n == 3 ? 1 : -1];
		expressions[0] = e1, expressions[1] = e2, expressions[2] = e3;
	}

	/**
	 * Constructor when \a n = 3.
	 * \param e1 first argument.
	 * \param e2 second argument.
	 * \param e3 third argument.
	 * \param val additional argument for base constructor.
	 */
	template<class T>
	NArgExpression(Expression *e1, Expression *e2, Expression *e3, T val)
		: BaseExpression(val) {
		typedef int static_assert[n == 3 ? 1 : -1];
		expressions[0] = e1, expressions[1] = e2, expressions[2] = e3;
	}


	/**
	 * Executes ith argument and returns result.
	 * \param env environment to execute expression in.
	 */
	template<unsigned i>
	real exec(Environment &env) const {
		return expressions[i]->execute(env);
	}

	/**
	 * Executes ith argument and returns boolean result.
	 * \param env environment to execute expression in.
	 */
	template<unsigned i>
	bool is(Environment &env) const {
		return expressions[i]->boolean(env);
	}


private:
	/** Just a helper. */
	typedef Expression *ExpressionPtr;

	/** Arguments. */
	ExpressionPtr expressions[n];
};




/** A literal number expression. */
struct NumberExpression : public Expression {
	/**
	 * Constructor.
	 * \param v literal number.
	 */
	explicit NumberExpression(real v) : val(v) { }

	/**
	 * Returns val.
	 * \param env ignored.
	 */
	virtual real execute(Environment &env) const;

private:
	/** Literal value. */
	real val;
};


/** A negation expression. */
struct NegExpression : public NArgExpression<1> {
	/**
	 * Constructor.
	 * \param e expression to negate.
	 */
	explicit NegExpression(Expression *e) : NArgExpression<1>(e) { }

	/**
	 * Returns negated value of expr.
	 * \param env environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};



/** Abstract class for expressions which have a string name argument. */
struct NameExpression : public Expression {
protected:
	/** Name argument. */
	std::string name;

	/**
	 * Constructor.
	 * \param n name argument.
	 */
	explicit NameExpression(const std::string &n) : name(n) { }
};

/** An expression which prints a string and returns one. */
struct StringExpression : public NameExpression {
	/**
	 * Constructor.
	 * \param str string to print.
	 */
	StringExpression(const std::string &str) : NameExpression(str) { }

	/**
	 * Prints string and returns one.
	 * \param env Environment to read variable's value from.
	 */
	virtual real execute(Environment &env) const;
};


/** Abstract class for expressions accessing variable's value. */
struct GetExpression : public NameExpression {
protected:
	/**
	 * Constructor.
	 * \param n variable's name.
	 */
	explicit GetExpression(const std::string &n) : NameExpression(n) { }
};


/** Class accessing local variable's value. */
struct GetLocalExpression : public GetExpression {
	/**
	 * Constructor.
	 * \param n variable's name.
	 */
	explicit GetLocalExpression(const std::string &n) : GetExpression(n) { }

	/**
	 * Return's variable's value in given environment.
	 * \param env Environment to read variable's value from.
	 */
	virtual real execute(Environment &env) const;
};

/** Class accessing global variable's value. */
struct GetGlobalExpression : public GetExpression {
	/**
	 * Constructor.
	 * \param n variable's name.
	 */
	explicit GetGlobalExpression(const std::string &n) : GetExpression(n) { }

	/**
	 * Return's variable's value in given environment.
	 * \param env Environment to read variable's value from.
	 */
	virtual real execute(Environment &env) const;
};

/** Class accessing constant's value. */
struct GetConstExpression : public GetExpression {
	/**
	 * Constructor.
	 * \param n constant's name.
	 */
	explicit GetConstExpression(const std::string &n) : GetExpression(n) { }

	/**
	 * Return's constant's value in given environment.
	 * \param env Environment to read constant's value from.
	 */
	virtual real execute(Environment &env) const;
};




/** Abstract class for expressions setting variable's value. */
struct SetExpression : public NArgExpression<1, NameExpression> {
protected:
	/**
	 * Constructor.
	 * \param n variable's name.
	 * \param e expression to set variables value to value of.
	 */
	SetExpression(const std::string &n, Expression *e)
		: NArgExpression<1, NameExpression>(e, n) { }
};


/** Class setting local's variable value. */
struct SetLocalExpression : public SetExpression {
	/**
	 * Constructor.
	 * \param n variable's name.
	 * \param e expression to set variables value to value of.
	 */
	SetLocalExpression(const std::string &n, Expression *e)
		: SetExpression(n, e) {}

	/**
	 * Sets variable's value in given environment.
	 * \param env Environment to alter variable's value in.
	 */
	virtual real execute(Environment &env) const;
};

/** Class setting global's variable value. */
struct SetGlobalExpression : public SetExpression {
	/**
	 * Constructor.
	 * \param n variable's name.
	 * \param e expression to set variables value to value of.
	 */
	SetGlobalExpression(const std::string &n, Expression *e)
		: SetExpression(n, e){}

	/**
	 * Sets variable's value in given environment.
	 * \param env Environment to alter variable's value in.
	 */
	virtual real execute(Environment &env) const;
};

/** Class setting constant's value. */
struct SetConstExpression : public SetExpression {
	/**
	 * Constructor.
	 * \param n constant's name.
	 * \param e expression to set constant's value to value of.
	 */
	SetConstExpression(const std::string &n, Expression *e)
		: SetExpression(n, e){}

	/**
	 * Sets constant's value in given environment.
	 * \param env Environment to alter variable's value in.
	 * \throw ConstAlreadyDefined if constant is already defined.
	 */
	virtual real execute(Environment &env) const;
};


/** A class representing a variable, global, local or constant. */
struct Variable {
	/** Variable's name. */
	std::string *name;
	/**
	 * Variable's scope.  '$' means global, '#' means constant and
	 * anything else means local.
	 */
	char scope;

	/** Creates a get expression. */
	GetExpression *getExpression() const {
		if (scope == '$') {
			return new GetGlobalExpression(*name);
		} else if (scope == '#') {
			return new GetConstExpression(*name);
		} else {
			return new GetLocalExpression(*name);
		}
	}

	/**
	 * Creates a set expression.
	 * \param expr right operand of assigment experssion.
	 */
	SetExpression *setExpression(Expression *expr) const {
		if (scope == '$') {
			return new SetGlobalExpression(*name, expr);
		} else if (scope == '#') {
			return new SetConstExpression(*name, expr);
		} else {
			return new SetLocalExpression(*name, expr);
		}
	}
};



/** An add expression. */
struct AddExpression : public NArgExpression<2> {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	AddExpression(Expression *e1, Expression *e2)
		: NArgExpression<2>(e1, e2) { }

	/**
	 * Returns sum of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** A substraction expression. */
struct SubExpression : public NArgExpression<2> {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	SubExpression(Expression *e1, Expression *e2)
		: NArgExpression<2>(e1, e2) { }

	/**
	 * Returns difference of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** A multipliaction expression. */
struct MulExpression : public NArgExpression<2> {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	MulExpression(Expression *e1, Expression *e2)
		: NArgExpression<2>(e1, e2) { }

	/**
	 * Returns product of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** A division expression. */
struct DivExpression : public NArgExpression<2> {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	DivExpression(Expression *e1, Expression *e2)
		: NArgExpression<2>(e1, e2) { }

	/**
	 * Returns quotient of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** A division modulo expression. */
struct ModExpression : public NArgExpression<2> {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	ModExpression(Expression *e1, Expression *e2)
		: NArgExpression<2>(e1, e2) { }

	/**
	 * Returns reminder of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** An exponentiation expression. */
struct PowExpression : public NArgExpression<2> {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	PowExpression(Expression *e1, Expression *e2)
		: NArgExpression<2>(e1, e2) { }

	/**
	 * Returns value of one expression raised to the power of value of
	 * the second expression.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};



/** A trinary @: epxression. */
struct WhileExpression : public NArgExpression<3> {
	/**
	 * Constructor.
	 * \param c condition expression
	 * \param e1 expression to evaluate while \a c evaluates \c true.
	 * \param e2 expression to evaluate when finally \a c evaluates
	 *           \c false.
	 */
	WhileExpression(Expression *c, Expression *e1, Expression *e2)
		: NArgExpression<3>(c, e1, e2) { }

	virtual real execute(Environment &env) const;
};


/** A trinary #: epxression. */
struct TimesExpression : public NArgExpression<3> {
	/**
	 * Constructor.
	 * \param t  expression saying how many times \a eq should be executed.
	 * \param e1 expression to evaluate \a e1 times.
	 * \param e2 expression to evaluate at the end.
	 */
	TimesExpression(Expression *t, Expression *e1, Expression *e2)
		: NArgExpression<3>(t, e1, e2) { }

	virtual real execute(Environment &env) const;
};


/** A trinary ?: epxression. */
struct IfExpression : public NArgExpression<3> {
	/**
	 * Constructor.
	 * \param c condition expression
	 * \param e1 expression to evaluate if \a c evaluates \c true.
	 * \param e2 expression to evaluate if \a c evaluates \c false.
	 */
	IfExpression(Expression *c, Expression *e1, Expression *e2)
		: NArgExpression<3>(c, e1, e2) { }

	virtual real execute(Environment &env) const;
};





/** An abstract class for boolean expressions. */
struct BooleanExpression : public Expression {
	/**
	 * Default constructor.
	 * \param _t expression's value that should be interpreted as
	 *           true; if this is set to \c false expression's result
	 *           will be negated; it can be altered with neg()
	 */
	explicit BooleanExpression(bool _t = true) : t(_t) { };

	/** Makes expression negate its result. */
	void neg() { t = !t; }

	virtual real execute(Environment &env) const;

	/**
	 * Evaluats a boolean expression in given environment.  It calls
	 * _boolean(() and compare's its result with \a t thus making it
	 * easy to negate expression's result by negating t.  Derived
	 * classes shall not overwrite this method and instead shall
	 * implement _boolean().
	 *
	 * \param env environment to execute expression in.
	 * \return boolean expression's result.
	 */
	virtual bool boolean(Environment &env) const;

	/** Returns itself. */
	virtual BooleanExpression *booleanExpression();

protected:
	/**
	 * Evaluates a boolean expression in given environment.
	 * \param env environment to execute expression in.
	 * \return boolean expression's result.
	 */
	virtual bool _boolean(Environment &env) const = 0;

private:
	/** A value of truth.  If it is \c false results are negated. */
	bool t;
};


/**
 * Interpretes expression's value as a boolean.  It is used to
 * make negations.
 */
struct ExpressionAsBoolean : public NArgExpression<1, BooleanExpression> {
protected:
	virtual bool _boolean(Environment &env) const;

private:
	/**
	 * Constructos object.
	 * \param e not a boolean expression.
	 */
	explicit ExpressionAsBoolean(Expression *e)
		: NArgExpression<1, BooleanExpression>(e) { }

	friend struct Expression;
};



/**
 * Class representing equality comparison of two real numbers.  To get
 * a expression which represents situation when two numbers are not
 * equal give \c false as a 3rd constructor arguemnt.
 */
struct EqualExpression : public NArgExpression<2, BooleanExpression> {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 * \param _t if \c false result of expression will be negated
	 * \param p comparison precision
	 */
	EqualExpression(Expression *e1, Expression *e2, bool _t = true,
	                real p = 0)
		: NArgExpression<2, BooleanExpression>(e1, e2, _t), precision(p) { }

	/** \copydoc EqualExpression(Expression*, Expression*, bool, real) */
	EqualExpression(Expression *e1, Expression *e2, real p, bool _t = true)
		: NArgExpression<2, BooleanExpression>(e1, e2, _t), precision(p) { }

protected:
	virtual bool _boolean(Environment &env) const;

private:
	/** Comparison precision. */
	const real precision;
};


/**
 * Class representing comparison of two real numbers.  As name sugests
 * it checks if first operand is greater then the second, however this
 * class is enough to represent all four possible relations (greater,
 * lower, lower equal and greater equal).  Lower is simply greater
 * with operands switched.  Lower equal is negation of greater and to
 * get negation pass \c false as 3rd argument to constructor.  Greater
 * equal is negation of lower thus it's enough to switch arguemnts and
 * give \c false as 3rd argument.
 */
struct GreaterExpression : public NArgExpression<2, BooleanExpression> {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 * \param _t if \c false result of expression will be negated
	 * \param p comparison precision
	 */
	GreaterExpression(Expression *e1, Expression *e2, bool _t = true,
	                  real p = 0)
		: NArgExpression<2, BooleanExpression>(e1, e2, _t), precision(p) { }

	/** \copydoc GreaterExpression(Expression*, Expression*, bool, real) */
	GreaterExpression(Expression *e1, Expression *e2, real p,
	                  bool _t = true)
		: NArgExpression<2, BooleanExpression>(e1, e2, _t), precision(p) { }

	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 * \param sw whether to switch first and second operand.
	 * \param _t if \c false result of expression will be negated
	 * \param p comparison precision
	 */
	GreaterExpression(Expression *e1, Expression *e2, bool sw, bool _t,
	                  real p = 0)
		: NArgExpression<2, BooleanExpression>(sw ? e2 : e1, sw ? e1 : e2,_t),
		  precision(p) { }

protected:
	virtual bool _boolean(Environment &env) const;

private:
	/** Comparison precision. */
	const real precision;
};


/** A logical OR expression. */
struct LogicalOrExpression : public NArgExpression<2, BooleanExpression> {
	/**
	 * Constructos a logical expression.
	 * \param e1 first sub-expression.
	 * \param e2 second sub-expression.
	 */
	LogicalOrExpression(Expression *e1, Expression *e2)
		: NArgExpression<2, BooleanExpression>(e1, e2) { }

protected:
	virtual bool _boolean(Environment &env) const;
};


/** A logical AND expression. */
struct LogicalAndExpression : public NArgExpression<2, BooleanExpression> {
	/**
	 * Constructos a logical expression.
	 * \param e1 first sub-expression.
	 * \param e2 second sub-expression.
	 */
	LogicalAndExpression(Expression *e1, Expression *e2)
		: NArgExpression<2, BooleanExpression>(e1, e2) { }

protected:
	virtual bool _boolean(Environment &env) const;
};


/** A logical XOR expression. */
struct LogicalXorExpression : public NArgExpression<2, BooleanExpression> {
	/**
	 * Constructos a logical expression.
	 * \param e1 first sub-expression.
	 * \param e2 second sub-expression.
	 */
	LogicalXorExpression(Expression *e1, Expression *e2)
		: NArgExpression<2, BooleanExpression>(e1, e2) { }

protected:
	virtual bool _boolean(Environment &env) const;
};



/** Expression representing comma operator. */
struct CommaExpression : public Expression {
	/** A vector of expressions. */
	typedef std::vector<Expression *> Expressions;


	/** Constructs empty sequence of expressions. */
	CommaExpression() { }

	/**
	 * Constructs sequence consisting of single expression.
	 * \param e expression to add to sequence.
	 */

	explicit CommaExpression(Expression *e) { push(e); }
	/**
	 * Copies sequence of expressions.
	 * \param exprs sequence of expressions.
	 */
	explicit CommaExpression(const Expressions &exprs) : vec(exprs) { }

	/** Deletes sequence of expressions and all expressions in it. */
	~CommaExpression();

	virtual real execute(Environment &env) const;
	/** Returns itself. */
	virtual CommaExpression *commaExpression();


	/** Returns number of expressions in sequence. */
	Expressions::size_type size() const { return vec.size(); }

	/** Returns underlying vector. */
	const Expressions &expressions() const { return vec; }

	/** Adds expression to sequence. */
	void push(Expression *e) {
		assert(e);
		vec.push_back(e);
	}

private:
	/** A vector of expressions. */
	Expressions vec;
};



/** A function call expression. */
struct FunctionExpression : public NameExpression {
	/** Function arguments. */
	typedef CommaExpression Arguments;

	/**
	 * Constructor.
	 * \param n function's name.
	 * \param a function's call arguments.
	 */
	explicit FunctionExpression(const std::string &n,
	                            Arguments *a = new Arguments())
		: NameExpression(n), args(a) { }

	/** Deletes arguments. */
	~FunctionExpression();

	/**
	 * Calls function and return's it return value.
	 * \param env Environment to run expression in.
	 * \throw InvalidNumberOfArguments if wrong number of arguments
	 *                                 was given.
	 * \throw NoSuchFunction if non-existing function was called.
	 */
	virtual real execute(Environment &env) const;

private:
	/** Vector of not yet evaluated function's arguments. */
	Arguments *args;
};







/**
 * Exception thrown when breaking out of the loop or returning from
 * a function.
 */
struct EscapeException {
	/** Returns whether exception's path has ended here. */
	bool end() { return (levels -= 1.0) <= 0.25; }

	/** Returns value used as a return value. */
	real getValue() const { return retValue; }

protected:
	/**
	 * Constructor
	 * \param val value used as return value from.
	 * \param lvl number of loops/functions to escape through.
	 */
	EscapeException(real val = 0, real lvl = 1)
		: retValue(val), levels(lvl) { }

	/**
	 * Copy constructor.
	 * \param e object to copy.
	 */
	EscapeException(const EscapeException &e)
		: retValue(e.retValue), levels(e.levels) { }

private:
	/** Value used as return value. */
	const real retValue;
	/** Number of loops/functions to escape through. */
	real levels;
};


/** Exception thrown when breaking out of the loop. */
struct BreakException : public EscapeException {
	BreakException(real val = 0, real lvl = 1) : EscapeException(val, lvl) { }
};

/** Exception thrown when returning from a function. */
struct ReturnException : public EscapeException {
	ReturnException(real val = 0, real lvl = 1) : EscapeException(val, lvl) {}
};

}

#endif
