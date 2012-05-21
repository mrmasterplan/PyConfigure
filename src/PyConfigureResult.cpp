
#include <Python.h>
#include "../include/ConfigurePyDict.h"

namespace ConfigurePy
{
using namespace std;

Result::~Result() {}

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
    Ref str = PyObject_Str(m_obj);    
    Exception::ThrowIfRelevant();

    std::string s = PyBytes_AsString(str);
    Exception::ThrowIfRelevant();
    return s;
}

Result::operator double() const throw(Exception)
{
    double a = PyFloat_AsDouble(m_obj);
    Exception::ThrowIfRelevant();
    return a;
}

Result::operator bool() const throw(Exception)
{
    int a = PyObject_IsTrue(m_obj);
    Exception::ThrowIfRelevant();
    return a;
}

Result::operator Dict() const throw(Exception)
{
    return Dict(m_obj);
}

Result Result::operator[] (const char* key) throw(Exception)
{
    return ((Dict)(*this))[key];
}

size_t Result::Sequence_Size(PyObject* o)
{
    size_t i = PySequence_Size(o);
    Exception::ThrowIfRelevant();
    return i;
}

PyObject* Result::Sequence_GetItem(PyObject* o,size_t i)
{
    Ref item = PySequence_GetItem(o,i);
    Exception::ThrowIfRelevant();
    return item.Steal();
}

}
