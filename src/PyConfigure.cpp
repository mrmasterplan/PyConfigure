
#include "PyConfigure.h"
namespace PyConfigure {
    Dict::Dict() throw(){}
    Dict::Dict(const Dict&) throw(){}
    Dict::~Dict() throw(){}

    Dict& Dict::operator = (const Dict&) throw()
    {
        return *this;   
    }
    
    Dict& Dict::operator = (PyObject*) throw()
    {
        return *this;   
        
    }
    
    Dict& Dict::operator = (const char*) throw(Exception)
    {
        return *this;           
    }

    Result Dict::operator[] (const char*) throw(Exception)
    {
        return Result();
    }

}