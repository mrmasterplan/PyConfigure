
#include "Python.h"
#include "../include/Wrapper.h"
#include "../include/PyConfigureException.h"
#include "../include/PyConfigurePyRef.h"
#include "Debug.h"

namespace PyConfigure {

    size_t Wrapper::MySequence_Size(PyObject* o)
    {
        DBG;
        size_t i = PySequence_Size(o);
        DBG;
        Exception::ThrowIfRelevant();
        DBG;
        return i;
    }
    
    PyObject* Wrapper::MySequence_GetItem(PyObject* o,size_t i)
    {
        PyRef item = PySequence_GetItem(o,i);
        Exception::ThrowIfRelevant();
        
        return item.Steal();
    }
    
}
