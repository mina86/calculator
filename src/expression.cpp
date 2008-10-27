/** \file
 * Expression method definitions.
 */

#include "config.hpp"

#include "expression.hpp"
#include "math.hpp"
#include "function.hpp"
#include "environment.hpp"


namespace calc {

bool Expression::boolean(Environment &env) const {
	/* The next line may produce "comparing floating point with == or
	   != is unsafe" warning; ignore it, we know that. */
	return execute(env) != 0.0;
}

BooleanExpression *Expression::booleanExpression() {
	return new ExpressionAsBoolean(this);
}

CommaExpression *Expression::commaExpression() {
	return new CommaExpression(this);
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
		throw NoSuchFunction(name);
		return 0;
	}

	if (!func->argumentsCountOK(args->size())) {
		throw InvalidNumberOfArguments(name);
		return 0;
	}

	return func->execute(env, args->expressions());
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
	return m::abs(expr1->execute(env) - expr2->execute(env)) <= precision;
}

bool GreaterExpression::_boolean(Environment &env) const {
	return expr1->execute(env) > expr2->execute(env) + precision;
}


bool LogicalOrExpression::_boolean(Environment &env) const {
	return expr1->boolean(env) || expr2->boolean(env);
}

bool LogicalAndExpression::_boolean(Environment &env) const {
	return expr1->boolean(env) && expr2->boolean(env);
}

bool LogicalXorExpression::_boolean(Environment &env) const {
	return expr1->boolean(env) != expr2->boolean(env);
}


CommaExpression::~CommaExpression() {
	Expressions::const_iterator it(vec.begin()), end(vec.end());
	for (; it != end; ++it) {
		delete *it;
	}
}

real CommaExpression::execute(Environment &env) const {
	real val = 0;
	Expressions::const_iterator it(vec.begin()), e(vec.end());
	for (; it != e; ++it) {
		val = (*it)->execute(env);
	}
	return val;
}

CommaExpression *CommaExpression::commaExpression() {
	return this;
}


namespace {
	/** Saves value of a variable and restores it when object is destroyed. */
	struct SaveOldValue {
		/**
		 * Constructor.
		 * \param m map object will operate on.
		 * \param n name of the value.
		 */
		SaveOldValue(Environment::Variables &m, const std::string n)
			: map(m), name(n) {
			Environment::Variables::iterator it = map.find(name);
			wasSet = it != map.end();
			if (wasSet) oldValue = it->second;
		}

		/** Restores previous state of the variable. */
		~SaveOldValue() {
			if (wasSet) {
				*this = oldValue;
			} else {
				map.erase(map.find(name));
			}
		}

		/**
		 * Assigns value to a variable.
		 * \param val the value.
		 */
		real &operator=(real val) {
			return map[name] = val;
		}

	private:
		/** The map to operate on. */
		Environment::Variables &map;
		/** Variable's name. */
		const std::string &name;
		/** Whether the variable was set. */
		bool wasSet;
		/** Old value of the variable. */
		real oldValue;
	};
}


WhileExpression::~WhileExpression() {
	delete cond;
}

real WhileExpression::execute(Environment &env) const {
	static const std::string it_name("it");
	static const std::string last_name("last");

	SaveOldValue it(env.constants(), it_name);
	SaveOldValue last(env.constants(), last_name);

	last = 0.0;
	try {
		for (real i = 0; it = i, cond->boolean(env); i += 1.0) {
			last = expr1->execute(env);
		}

		return expr2->execute(env);
	}
	catch (BreakException &e) {
		if (e.end()) {
			return e.getValue();
		} else {
			throw;
		}
	}
}

IfExpression::~IfExpression() {
	delete cond;
}

real IfExpression::execute(Environment &env) const {
	return cond->boolean(env) ? expr1->execute(env) : expr2->execute(env);
}


}
