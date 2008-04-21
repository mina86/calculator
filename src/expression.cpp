/** \file
 * Expression method definitions.
 * $Id: expression.cpp,v 1.4 2008/04/21 08:26:41 mina86 Exp $
 */

#include "config.hpp"

#include "expression.hpp"
#include "math.hpp"
#include "function.hpp"
#include "environment.hpp"


namespace calc {

bool Expression::boolean(Environment &env) const {
	return execute(env) != 0.0;
}

/** Returns BooleanExpression interpreting value of this Expression. */
BooleanExpression *Expression::booleanExpression() {
	return new ExpressionAsBoolean(this);
}

Expression::~Expression() { }


real NumberExpression::execute(Environment &env) const {
	(void)env;
	return val;
}

NegExpression::~NegExpression() {
	delete expr;
}

real NegExpression::execute(Environment &env) const {
	return -expr->execute(env);
}

real GetLocalExpression::execute(Environment &env) const {
	return Environment::get(env.local(), name);
}

real GetGlobalExpression::execute(Environment &env) const {
	return Environment::get(env.global(), name);
}

real GetConstExpression::execute(Environment &env) const {
	return Environment::get(env.constants(), name);
}


SetExpression::~SetExpression() {
	delete expr;
}

real SetLocalExpression::execute(Environment &env) const {
	real val = expr->execute(env);
	return env.local()[name] = val;
}

real SetGlobalExpression::execute(Environment &env) const {
	real val = expr->execute(env);
	return env.global()[name] = val;
}

real SetConstExpression::execute(Environment &env) const {
	real val = expr->execute(env);
	std::pair<Environment::Variables::iterator, bool> ret =
		env.constants().insert(std::make_pair(name, val));
	if (!ret.second) {
		throw ConstAlreadyDefined();
	}
	return val;
}



AtLeast2ArgExpression::~AtLeast2ArgExpression() {
	delete expr1;
	delete expr2;
}

real AddExpression::execute(Environment &env) const {
	return expr1->execute(env) + expr2->execute(env);
}

real SubExpression::execute(Environment &env) const {
	return expr1->execute(env) - expr2->execute(env);
}

real MulExpression::execute(Environment &env) const {
	return expr1->execute(env) * expr2->execute(env);
}

real DivExpression::execute(Environment &env) const {
	return expr1->execute(env) / expr2->execute(env);
}

real PowExpression::execute(Environment &env) const {
	return m::pow(expr1->execute(env), expr2->execute(env));
}


FunctionExpression::~FunctionExpression() {
	delete args;
}

real FunctionExpression::execute(Environment &env) const {
	const Function *func = env.getFunction(name);
	if (!func) {
		env.error("no such function: " + name);
		return 0;
	}

	if (func->argumentsCountOK(args->size())) {
		env.error("invalid number of arguments for function: " + name);
		return 0;
	}

	Function::Arguments values(args->size());
	real *v = &values[0];
	Arguments::const_iterator it = args->begin(), end = args->end();
	while (it != end) {
		*v = (*it)->execute(env);
		++it; ++v;
	}

	return func->execute(env, values);
}



real BooleanExpression::execute(Environment &env) const {
	return _boolean(env) == t ? 1.0 : 0.0;
}

bool BooleanExpression::boolean(Environment &env) const {
	return _boolean(env) == t;
}

BooleanExpression *BooleanExpression::booleanExpression() {
	return this;
}


bool ExpressionAsBoolean::_boolean(Environment &env) const {
	return expr->boolean(env);
}

ExpressionAsBoolean::~ExpressionAsBoolean() {
	delete expr;
}


AtLeast2ArgBooleanExpression::~AtLeast2ArgBooleanExpression() {
	delete expr1;
	delete expr2;
}


bool EqualExpression::_boolean(Environment &env) const {
	return expr1->execute(env) == expr2->execute(env);
}

bool GreaterExpression::_boolean(Environment &env) const {
	return expr1->execute(env) > expr2->execute(env);
}



}
