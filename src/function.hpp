/** \file
 * Function class declaration.
 * $Id: function.hpp,v 1.2 2008/04/12 12:58:01 mina86 Exp $
 */
#ifndef H_FUNCTION_HPP
#define H_FUNCTION_HPP

#include "config.hpp"

#include <string>
#include <vector>


namespace calc {


struct Environment;


struct Function {
	virtual ~Function() { };

	virtual bool argumentsCountOK(unsigned count) const = 0;
	virtual real execute(Environment &env, const real *args, unsigned count)
		const = 0;
	virtual void free() = 0;

	Function() { }

private:
	Function(const Function &func) { (void)func; }
};


}

#endif
