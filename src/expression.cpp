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


real NumberExpression::execute(Environment &env) const {
	(void)env;
	return val;
}

real NegExpression::execute(Environment &env) const {
	return -exec<0>(env);
}

real StringExpression::execute(Environment &env) const {
	(void)env;
	std::cout << name;
	return 1.0;
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


real SetLocalExpression::execute(Environment &env) const {
	return env.local()[name] = exec<0>(env);
}

real SetGlobalExpression::execute(Environment &env) const {
	return env.global()[name] = exec<0>(env);
}

real SetConstExpression::execute(Environment &env) const {
	real val = exec<0>(env);
	if (!env.constants().insert(std::make_pair(name, val)).second) {
		throw ConstAlreadyDefined();
	}
	return val;
}



real AddExpression::execute(Environment &env) const {
	return exec<0>(env) + exec<1>(env);
}

real SubExpression::execute(Environment &env) const {
	return exec<0>(env) - exec<1>(env);
}

real MulExpression::execute(Environment &env) const {
	return exec<0>(env) * exec<1>(env);
}

real DivExpression::execute(Environment &env) const {
	return exec<0>(env) / exec<1>(env);
}

real ModExpression::execute(Environment &env) const {
	return m::fmod(exec<0>(env), exec<1>(env));
}

real PowExpression::execute(Environment &env) const {
	return m::pow(exec<0>(env), exec<1>(env));
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
	return is<0>(env);
}


bool EqualExpression::_boolean(Environment &env) const {
	return m::abs(exec<0>(env) - exec<1>(env)) <= precision;
}

bool GreaterExpression::_boolean(Environment &env) const {
	return exec<0>(env) > exec<1>(env) + precision;
}


bool LogicalOrExpression::_boolean(Environment &env) const {
	return is<0>(env) || is<1>(env);
}

bool LogicalAndExpression::_boolean(Environment &env) const {
	return is<0>(env) && is<1>(env);
}

bool LogicalXorExpression::_boolean(Environment &env) const {
	return is<0>(env) != is<1>(env);
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
	template<class T>
	struct SaveOldValue {
		/**
		 * Constructor.
		 * \param v reference to the variable.
		 */
		SaveOldValue(T &v) : value(v), old(v) { }

		/** Restores previous state of the variable. */
		~SaveOldValue() {
			value = old;
		}

		/**
		 * Assigns value to a variable.
		 * \param val the value.
		 */
		T &operator=(T val) {
			return value = val;
		}

	private:
		/** Reference to the variable. */
		T &value;
		/** Old value of the variable. */
		T old;
	};
}


real WhileExpression::execute(Environment &env) const {
	SaveOldValue<real> it  (env.iteration_value());
	SaveOldValue<real> last(env.last_value     ());

	try {
		for (real i = 0; it = i, is<0>(env); i += 1.0) {
			last = exec<1>(env);
		}

		return exec<2>(env);
	}
	catch (BreakException &e) {
		if (e.end()) {
			return e.getValue();
		} else {
			throw;
		}
	}
}

real TimesExpression::execute(Environment &env) const {
	SaveOldValue<real> it  (env.iteration_value());
	SaveOldValue<real> last(env.last_value     ());

	try {
		for (real n = exec<0>(env), i = 0; i < n; i += 1.0) {
			it = i;
			last = exec<1>(env);
		}

		return exec<2>(env);
	}
	catch (BreakException &e) {
		if (e.end()) {
			return e.getValue();
		} else {
			throw;
		}
	}
}

real IfExpression::execute(Environment &env) const {
	return is<0>(env) ? exec<1>(env) : exec<2>(env);
}


}
