/** \file
 * Function class virtual methods definitions.
 * $Id: function.cpp,v 1.1 2008/04/21 10:14:54 mina86 Exp $
 */
#include "function.hpp"
#include "expression.hpp"

namespace calc {


Function::~Function() { }

real Function::execute(Environment &env,
                       const std::vector<Expression*> &args) const {
	std::vector<Expression*>::const_iterator it(args.begin()), e(args.end());
	Arguments a(args.size());
	Arguments::iterator i(a.begin());
	for (; it != e; ++it, ++i) {
		*i = (*it)->execute(env);
	}
	return execute(env, a);
}


}
