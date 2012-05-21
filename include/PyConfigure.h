#ifndef PYCONFIGURE_H_XRQ1SB5W
#define PYCONFIGURE_H_XRQ1SB5W

#include "ForwardPyObject.h"
#include "PyConfigurePyRef.h"
#include "PyConfigureResult.h"
#include "PyConfigureException.h"

namespace PyConfigure {

    class Dict{
    public:
        Dict() throw();
        Dict(PyObject*) throw();
        Dict(const Dict&) throw();
        ~Dict() throw();
    
        Dict& operator = (const Dict&) throw();
        Dict& operator = (PyObject*) throw(Exception);
        Dict& operator = (const char*) throw(Exception);
    
        Result operator[] (const char*) throw(Exception);

    private:
        void InitPy() throw();
        PyRef m_py_dict;
    };

}
#endif /* end of include guard: PYCONFIGURE_H_XRQ1SB5W */
