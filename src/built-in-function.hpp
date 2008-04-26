#pragma once

#include "function.hpp"

namespace calc {

/**
 * A Built-in Functions base class
 */
struct BuiltInFunction : public Function
{
    /** Virtual, empty destructor. */
    virtual ~BuiltInFunction(void);

    /**
     * Returns whether number of arguments is OK.
     * \param count number of arguements.
     */
    virtual bool argumentsCountOK(unsigned count) const;

    virtual void free() {};

protected:
    /** Constructor available only for child classes */
    BuiltInFunction(const unsigned &nargs);
    BuiltInFunction(const unsigned &min, const unsigned &max);

private:

    /** Minimal number of arguments passed to function */
    const unsigned minArgs;

    /** Maximal number of arguments passed to function */
    const unsigned maxArgs;
};

}
