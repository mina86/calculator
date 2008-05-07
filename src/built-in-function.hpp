#pragma once

#include "function.hpp"

namespace calc {

/**
 * A Built-in Functions base class
 */
struct BuiltInFunction : public Function {
	virtual bool argumentsCountOK(unsigned count) const;
	virtual void free();

protected:
	/** Constructor available only for child classes */
	BuiltInFunction(const unsigned &nargs)
		: minArgs(nargs), maxArgs(nargs) { }
	BuiltInFunction(const unsigned &min, const unsigned &max)
		: minArgs(min), maxArgs(max) { }

private:
	/** Minimal number of arguments passed to function */
	const unsigned minArgs;

	/** Maximal number of arguments passed to function */
	const unsigned maxArgs;
};

}
