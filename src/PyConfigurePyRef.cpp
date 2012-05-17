
#include "PyConfigurePyRef.h"

#include "Python.h"

namespace PyConfigure {
    PyRef::PyRef() throw():
        data(NULL)
    {
        // no code
    }
    
    PyRef::PyRef(PyObject* obj) throw():
        data(NULL)
    {
        *this = obj;
    }
    
    PyRef::~PyRef() throw()
    {
        
    }
    
    PyRef& PyRef::operator=(PyObject* obj) throw()
    {
        data = obj;
        // increment the reference count;
        return *this;
    }
    
    PyRef::operator PyObject*() const
    {
        return data;
    }
    
}