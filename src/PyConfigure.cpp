
#include <Python.h>
// #include <iostream>

#include "../include/ConfigurePyDict.h"

namespace ConfigurePy
{

Dict::Dict() throw():m_py_dict()
{
    InitPy();
}

Dict::Dict(PyObject* o) throw()
{
    *this = o;
}

Dict::Dict(const Dict& other) throw()
{
    *this = other;
}

void Dict::InitPy() throw()
{
    if(not Py_IsInitialized()) {
        Py_Initialize();
    }
}

Dict::~Dict() throw() {}

Dict& Dict::operator = (const Dict& other) throw()
{
    m_py_dict=other.m_py_dict;
    InitPy();
    m_py_dict.Inc();
    return *this;
}

Dict& Dict::operator = (PyObject* o) throw(Exception)
{
    m_py_dict = o;
    InitPy();
    m_py_dict.Inc();
    return *this;
}

Dict& Dict::operator = (const char* code) throw(Exception)
{
    m_py_dict = PyDict_New();
    Exception::ThrowIfRelevant();

    Ref globals = PyDict_New();
    Exception::ThrowIfRelevant();

    PyDict_SetItemString(globals, "__builtins__", PyEval_GetBuiltins());
    Exception::ThrowIfRelevant();

    Ref retstr = PyRun_StringFlags(code,Py_file_input,globals,m_py_dict,0);
    Exception::ThrowIfRelevant();

    return *this;
}

Result Dict::operator[] (const char* key) throw(Exception)
{
    Ref obj = PyDict_GetItemString(m_py_dict, key);
    Exception::ThrowIfRelevant();

    obj.Inc();
    return Result(obj.Steal());
}

}