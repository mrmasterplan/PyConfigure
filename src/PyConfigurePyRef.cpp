#include "Python.h"

#include "../include/ConfigurePyDict.h"


namespace ConfigurePy
{
Ref::Ref() throw(): data(NULL) {}

Ref::Ref(PyObject* obj) throw():data(NULL)
{
    *this = obj;
}

Ref::~Ref() throw()
{
    Dec();
}

void Ref::Dec() throw()
{
    if(data != NULL) {
        Py_DECREF(data);
    }
    data = NULL;
}

void Ref::Inc() throw()
{
    if(data != NULL) {
        Py_INCREF(data);
    }
}


Ref& Ref::operator=(PyObject* obj) throw()
{
    Dec();

    data = obj;
    return *this;
}

Ref::operator PyObject*() const
{
    return data;
}

PyObject* Ref::Steal() throw()
{
    PyObject* tmp = data;
    data=NULL;
    return tmp;
}


}