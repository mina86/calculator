#include "built-in-function.hpp"

namespace calc {


bool BuiltInFunction::argumentsCountOK(unsigned count) const {
    return minArgs <= count && count <= maxArgs;
}

void BuiltInFunction::free() { }


}
