#include "Python.h"
#include "PyConfigurePyRef.h"
// #include <iostream>

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
        Dec();
    }
    
    void PyRef::Dec() throw()
    {
        if(data != NULL){
            // std::cout<<"decrementing "<<data<<std::endl;
            
            Py_DECREF(data);
        }
        data = NULL;
    }

    void PyRef::Inc() throw()
    {
        if(data != NULL){
            // std::cout<<"decrementing "<<data<<std::endl;
            
            Py_INCREF(data);
        }
    }
    
    
    PyRef& PyRef::operator=(PyObject* obj) throw()
    {
        Dec();
        
        data = obj;
        // increment the reference count;
        return *this;
    }
    
    PyRef::operator PyObject*() const
    {
        return data;
    }
    
    PyObject* PyRef::NewRef() throw()
    {
        if( data!=NULL){
            Py_INCREF(data);
        }
        return data;
    }
    
    PyObject* PyRef::Steal() throw()
    {
        PyObject* tmp = data;
        data=NULL;
        return tmp;
    }
    
    
}