/** \file
 * Function class virtual methods definitions.
 * $Id: function.cpp,v 1.2 2008/06/05 20:37:04 mina86 Exp $
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
