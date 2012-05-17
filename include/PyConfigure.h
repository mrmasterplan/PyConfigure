#ifndef PYCONFIGURE_H_XRQ1SB5W
#define PYCONFIGURE_H_XRQ1SB5W

#include <Python.h>
#include "PyConfigureResult.h"
#include "PyConfigureException.h"

namespace PyConfigure {

    class Dict{
    public:
        Dict() throw();
        Dict(const Dict&) throw();
        ~Dict() throw();
    
        Dict& operator = (const Dict&) throw();
        Dict& operator = (PyObject*) throw();
        Dict& operator = (const char*) throw(Exception);
    
        Result operator[] (const char*) throw(Exception);
    };

}
#endif /* end of include guard: PYCONFIGURE_H_XRQ1SB5W */
