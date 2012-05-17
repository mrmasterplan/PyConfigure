
#include "PyConfigure.h"
#include "PyConfigureResult.h"

namespace PyConfigure {
    Result::~Result(){}
    Result::Result(){}
    Result::Result(const Result&){}

    Result::operator Dict() const
    {
        return Dict();
    }
}
