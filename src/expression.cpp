/** \file
 * Expression method definitions.
 * $Id: expression.cpp,v 1.2 2008/04/12 12:58:01 mina86 Exp $
 */

#include "config.hpp"

#include <memory>

#include "expression.hpp"
#include "math.hpp"
#include "function.hpp"


namespace calc {

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

NameExpression::~NameExpression() {
	delete name;
}

real GetLocalExpression::execute(Environment &env) const {
	return Environment::get(env.local(), *name);
}

real GetGlobalExpression::execute(Environment &env) const {
	return Environment::get(env.global(), *name);
}

real GetConstExpression::execute(Environment &env) const {
	return Environment::get(env.constants(), *name);
}


SetExpression::~SetExpression() {
	delete expr;
}

real SetLocalExpression::execute(Environment &env) const {
	real val = expr->execute(env);
	return env.local()[*name] = val;
}

real SetGlobalExpression::execute(Environment &env) const {
	real val = expr->execute(env);
	return env.global()[*name] = val;
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
	const Function *func = env.getFunction(*name);
	if (!func) {
		env.error("no such function: " + *name);
		return 0;
	}

	if (func->argumentsCountOK(args->size())) {
		env.error("invalid number of arguments for function: " + *name);
		return 0;
	}

	std::auto_ptr<real> values(new real[args->size()]);
	real *v = values.get();
	Arguments::const_iterator it = args->begin(), end = args->end();
	while (it != end) {
		*v = (*it)->execute(env);
		++it; ++v;
	}

	return func->execute(env, values.get(), args->size());
}


}
