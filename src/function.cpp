/** \file
 * Function class virtual methods definitions.
 */
#include "function.hpp"
#include "expression.hpp"

namespace calc {


Function::~Function() { }

real Function::execute(Environment &env,
                       const std::vector<Expression*> &args) const {
	std::vector<Expression*>::const_iterator it(args.begin()),end(args.end());
	Arguments a(args.size());
	Arguments::iterator out = a.begin();
	for (; it != end; ++it, ++out) {
		*out = (*it)->execute(env);
	}
	return execute(env, a);
}


}
