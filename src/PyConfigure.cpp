
#include <Python.h>
#include <iostream>
#include "../include/PyConfigure.h"
#include "../include/Debug.h"

namespace PyConfigure {
    
    Dict::Dict() throw():
        m_py_dict()
    {
        InitPy();
    }

    Dict::Dict(PyObject* o) throw():
        m_py_dict(o)
    {
        InitPy();
        m_py_dict.Inc();
    }

    Dict::Dict(const Dict& other) throw():
        m_py_dict(other.m_py_dict)
    {
        InitPy();
        m_py_dict.Inc();
    }
    void Dict::InitPy() throw()
    {
        if(not Py_IsInitialized()){
            std::cout<<"Initializing Python..."<<std::endl;
            Py_Initialize();
            
        }
    }
    
    
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
        // m_py_dict = Py_BuildValue("{}");
        m_py_dict = PyDict_New();
        Exception::ThrowIfRelevant();
        DBG;
        
        PyRef globals = PyDict_New();
        Exception::ThrowIfRelevant();
        DBG;
        PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
        Exception::ThrowIfRelevant();
        
        PyRef retstr = PyRun_StringFlags(code,Py_file_input,globals,m_py_dict,0);
        Exception::ThrowIfRelevant();
        DBG;
        
        return *this;           
    }

    Result Dict::operator[] (const char* key) throw(Exception)
    {
        PyRef obj = PyDict_GetItemString(m_py_dict, key);
        Exception::ThrowIfRelevant();
        return Result(obj.Steal());
    }

}