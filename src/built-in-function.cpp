#include "built-in-function.hpp"


namespace calc {

/************************************************************************/
/* Class: BuiltInFunction                                               */
/************************************************************************/
BuiltInFunction::BuiltInFunction(const unsigned &nargs) : minArgs(nargs), maxArgs(nargs)
{
}

BuiltInFunction::BuiltInFunction( const unsigned &min, const unsigned &max )
         : minArgs(min), maxArgs(max)
{
}

BuiltInFunction::~BuiltInFunction(void)
{
}

bool BuiltInFunction::argumentsCountOK( unsigned count ) const
{
    return minArgs <= count && count <= maxArgs;
}

}