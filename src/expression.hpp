/** \file
 * Expression declarations.
 * $Id: expression.hpp,v 1.5 2008/04/21 08:35:26 mina86 Exp $
 */
#ifndef H_EXPRESSION_HPP
#define H_EXPRESSION_HPP

#include "config.hpp"

#include <string>
#include <vector>



namespace calc {

struct Environment;
struct BooleanExpression;


/** An abstract expression class. */
struct Expression {
	/**
	 * Evaluats expression in given environment.
	 * \param env environment to execute expression in.
	 * \return expression's result.
	 */
	virtual real execute(Environment &env) const = 0;

	/**
	 * Evaluats expression in given environment and interpretes its
	 * result as boolean value.
	 * \param env environment to execute expression in.
	 * \return expression's result interpreted as boolean value.
	 */
	virtual bool boolean(Environment &env) const;

	/** Returns BooleanExpression interpreting value of this Expression. */
	virtual BooleanExpression *booleanExpression();

	/** Virtual destructor. */
	virtual ~Expression();

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


/** A class representing a variable, global, local or constant. */
struct Variable {
	/** Variable's name. */
	std::string *name;
	/**
	 * Variable's scope.  '$' means global, '#' means constant and
	 * anything else means local.
	 */
	char scope;

	/** Converts object into an GetExpression. */
	inline operator Expression*() const;
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
struct NegExpression : public Expression {
	/**
	 * Constructor.
	 * \param e expression to negate.
	 */
	explicit NegExpression(Expression *e) : expr(e) { }
	/** Deletes expr. */
	~NegExpression();
	/**
	 * Returns negated value of expr.
	 * \param env environment to run expression in.
	 */
	virtual real execute(Environment &env) const;

private:
	/** Expression to negate. */
	Expression *expr;
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


/** Abstract class for expressions accessing variable's value. */
struct GetExpression : public NameExpression {
	/**
	 * A factory creating a GetExpression based on variable's scope.
	 * \param v variable to access
	 * \return GetExpression accessing given variable.
	 */
	static inline GetExpression *create(const Variable &v);

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


inline GetExpression *GetExpression::create(const Variable &var) {
	if (var.scope == '$') {
		return new GetGlobalExpression(*var.name);
	} else if (var.scope == '#') {
		return new GetConstExpression(*var.name);
	} else {
		return new GetLocalExpression(*var.name);
	}
}


inline Variable::operator Expression*() const {
	return GetExpression::create(*this);
}



/** Abstract class for expressions setting variable's value. */
struct SetExpression : public NameExpression {
	/**
	 * A factory creating a SetExpression based on variable's scope.
	 * \param var variable to access.
	 * \param e expression to set variable's value to value of.
	 * \return SetExpression setting given variable.
	 */
	static inline SetExpression *create(const Variable &var, Expression *e);

	/** Deletes expr. */
	~SetExpression();

protected:
	/** Expression to evaluate to set variable's value to. */
	Expression *expr;

	/**
	 * Constructor.
	 * \param n variable's name.
	 * \param e expression to set variables value to value of.
	 */
	SetExpression(const std::string &n, Expression *e)
		: NameExpression(n), expr(e) { }
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


inline SetExpression *SetExpression::create(const Variable &var,
                                            Expression *e) {
	if (var.scope == '$') {
		return new SetGlobalExpression(*var.name, e);
	} else if (var.scope == '#') {
		return new SetConstExpression(*var.name, e);
	} else {
		return new SetLocalExpression(*var.name, e);
	}
}



/** Base class for expressions taking at least two arguments. */
struct AtLeast2ArgExpression : public Expression {
	/** Deltes expressions. */
	~AtLeast2ArgExpression();

protected:
	/** First operand. */
	Expression *expr1;
	/** Second operand. */
	Expression *expr2;

	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	AtLeast2ArgExpression(Expression *e1, Expression *e2)
		: expr1(e1), expr2(e2) { }
};


/** An add expression. */
struct AddExpression : public AtLeast2ArgExpression {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	AddExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }

	/**
	 * Returns sum of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** A substraction expression. */
struct SubExpression : public AtLeast2ArgExpression {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	SubExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }

	/**
	 * Returns difference of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** A multipliaction expression. */
struct MulExpression : public AtLeast2ArgExpression {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	MulExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }

	/**
	 * Returns product of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** A division expression. */
struct DivExpression : public AtLeast2ArgExpression {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	DivExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }

	/**
	 * Returns quotient of two expressions values.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};

/** An exponentiation expression. */
struct PowExpression : public AtLeast2ArgExpression {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 */
	PowExpression(Expression *e1, Expression *e2)
		: AtLeast2ArgExpression(e1, e2) { }

	/**
	 * Returns value of one expression raised to the power of value of
	 * the second expression.
	 * \param env Environment to run expression in.
	 */
	virtual real execute(Environment &env) const;
};



/** A function call expression. */
struct FunctionExpression : public NameExpression {
	/** Vector of not yet evaluated function's arguments. */
	typedef std::vector<Expression*> Arguments;

	/**
	 * Constructor.
	 * \param n function's name.
	 * \param a function's call arguments.
	 */
	FunctionExpression(const std::string &n, Arguments *a)
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

	virtual BooleanExpression *booleanExpression();

protected:
	/**
	 * Evaluates a boolean expression in given environment.
	 * \param env environment to execute expression in.
	 * \return boolean expression's result.
	 */
	virtual bool _boolean(Environment &env) const = 0;

private:
	bool t;
};


struct ExpressionAsBoolean : public BooleanExpression {
	~ExpressionAsBoolean();

protected:
	virtual bool _boolean(Environment &env) const;

private:
	Expression *expr;

	explicit ExpressionAsBoolean(Expression *e) : expr(e) { }

	friend struct Expression;
};


/** Base class for boolean expressions taking at least two arguments. */
struct AtLeast2ArgBooleanExpression : public BooleanExpression {
	/** Deltes expressions. */
	~AtLeast2ArgBooleanExpression();

protected:
	/** First operand. */
	Expression *expr1;
	/** Second operand. */
	Expression *expr2;

	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 * \param _t if \c false result of expression will be negated
	 */
	AtLeast2ArgBooleanExpression(Expression *e1, Expression *e2,
	                             bool _t = true)
		: BooleanExpression(_t), expr1(e1), expr2(e2) { }
};


/**
 * Class representing equality comparison of two real numbers.  To get
 * a expression which represents situation when two numbers are not
 * equal give \c false as a 3rd constructor arguemnt.
 */
struct EqualExpression : public AtLeast2ArgBooleanExpression {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 * \param _t if \c false result of expression will be negated
	 */
	EqualExpression(Expression *e1, Expression *e2, bool _t = true)
		: AtLeast2ArgBooleanExpression(e1, e2, _t) { }

protected:
	virtual bool _boolean(Environment &env) const;
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
struct GreaterExpression : public AtLeast2ArgBooleanExpression {
	/**
	 * Constructor.
	 * \param e1 first operand.
	 * \param e2 second operand.
	 * \param _t if \c false result of expression will be negated
	 */
	GreaterExpression(Expression *e1, Expression *e2, bool _t = true)
		: AtLeast2ArgBooleanExpression(e1, e2, _t) { }

protected:
	virtual bool _boolean(Environment &env) const;
};

}

#endif
