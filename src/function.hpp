/** \file
 * Function class declaration.
 * $Id: function.hpp,v 1.1 2008/04/12 02:15:52 mina86 Exp $
 */
#ifndef H_FUNCTION_HPP
#define H_FUNCTION_HPP

#include "config.hpp"

#include <string>
#include <vector>


namespace calc {


struct Environment;


struct Function {
	typedef std::vector<real> Arguments;

	virtual ~Function() { };

	virtual bool argumentsCountOK(unsigned count) const = 0;
	virtual real execute(Environment &env, const Arguments &args) const = 0;
	virtual void free() = 0;

	Function() { }

private:
	Function(const Function &func) { (void)func; }
};


}

#endif
