#ifndef PYCONFIGUREEXCEPTION_H_3WAXS1Q1
#define PYCONFIGUREEXCEPTION_H_3WAXS1Q1

#include <exception>

namespace PyConfigure {

    class Exception : public std::exception
    {
    public:
      Exception() throw(){}
      Exception(const Exception&) throw(){}
      virtual ~Exception() throw();
    };

}

#endif /* end of include guard: PYCONFIGUREEXCEPTION_H_3WAXS1Q1 */
