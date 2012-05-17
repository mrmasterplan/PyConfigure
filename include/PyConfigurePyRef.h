#ifndef PYCONFIGUREPYREF_H_1AUDXXIC
#define PYCONFIGUREPYREF_H_1AUDXXIC

#include "ForwardPyObject.h"

namespace PyConfigure {
    class PyRef {
    public:
        PyRef() throw();
        PyRef(PyObject*) throw();
        ~PyRef() throw();
        
        PyRef& operator=(PyObject*) throw();
        
        operator PyObject*() const;
    private:
        PyObject* data;
    };
}

#endif /* end of include guard: PYCONFIGUREPYREF_H_1AUDXXIC */
