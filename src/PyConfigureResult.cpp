
#include <Python.h>
#include "PyConfigure.h"
#include "PyConfigureResult.h"
#include "PyConfigureException.h"

namespace PyConfigure {
    using namespace std;
    
    Result::~Result(){}
    
    Result::Result(PyObject* obj)
    {
        m_obj = obj;
    }
    
    Result::operator long() const  throw(Exception)
    {
        long a = PyLong_AsLong(m_obj);
        Exception::ThrowIfRelevant();
        return a;
    }

    Result::operator std::string() const  throw(Exception)
    {
        std::string s = PyBytes_AsString(m_obj);
        Exception::ThrowIfRelevant();
        return s;
    }
    
    Result::operator double() const throw(Exception)
    {
        double a = PyFloat_AsDouble(m_obj);
        Exception::ThrowIfRelevant();
        return a;
    }

    Result::operator Dict() const  throw(Exception)
    {
        return Dict(m_obj);
    }
    
    Result Result::operator[] (const char* key) throw(Exception)
    {
        return ((Dict)(*this))[key];
    }
    
}
