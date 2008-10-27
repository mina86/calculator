/** \file
 * Function class virtual methods definitions.
 */
#include "function.hpp"
#include "expression.hpp"

namespace calc {


Function::~Function() { }

real Function::execute(Environment &env,
                       const std::vector<Expression*> &args) const {
	std::vector<Expression*>::const_iterator it(args.begin()), e(args.end());
	Arguments a(args.size());
	std::copy(Expression::executor_iterator(args.begin(), env),
	          Expression::executor_iterator(args.end(), env),
	          a.begin());
	return execute(env, a);
}


}
