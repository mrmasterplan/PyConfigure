
#include <Python.h>
#include <iostream>
#include "../include/PyConfigure.h"
#include "../include/Debug.h"

namespace PyConfigure {
    
    Dict::Dict() throw()
    {
        if(not Py_IsInitialized())
            Py_Initialize();
        /*no code*/
    }

    Dict::Dict(const Dict&) throw(){}
    
    Dict::~Dict() throw()
    {
    }

    Dict& Dict::operator = (const Dict&) throw()
    {
        return *this;   
    }
    
    Dict& Dict::operator = (PyObject*) throw(Exception)
    {
        return *this;   
    }
    
    Dict& Dict::operator = (const char* code) throw(Exception)
    {
        DBG;
        m_py_dict = Py_BuildValue("{}");
        Exception::ThrowIfRelevant();
        DBG;
        
        PyRef globals = Py_BuildValue("{}");
        Exception::ThrowIfRelevant();
        DBG;
        
        PyRef retstr = PyRun_StringFlags(code,Py_file_input,globals,m_py_dict,0);
        Exception::ThrowIfRelevant();
        DBG;
        
        return *this;           
    }

    Result Dict::operator[] (const char*) throw(Exception)
    {
        return Result();
    }

}