#include <Python.h>

#include "../include/ConfigurePyDict.h"

namespace ConfigurePy
{

void Exception::ThrowIfRelevant() throw(Exception)
{
    PyObject* err = PyErr_Occurred();
    if ( err ) {
        std::string message;
        std::string type_str;

        PyObject *type=NULL, *value=NULL, *trc=NULL;
        PyErr_Fetch(&type,&value,&trc);

        // PyErr_Print();

        if(type!=NULL) {
            Ref name = PyObject_GetAttrString(type,"__name__");
            Ref str = PyObject_Str(name);
            type_str = PyBytes_AsString(str);
        }
        if(value!=0){
            Ref str = PyObject_Str(value);
            message = PyBytes_AsString(str);
        }

        PyErr_Restore(type,value,trc);

        throw Exception(type_str,message);
    }
}

void Exception::Disown() throw()
{
    owns_state=0;
}

Exception::Exception(bool own) throw(): owns_state(own) {}

Exception::Exception(const Exception& o) throw():
    type(o.type),
    msg(o.msg),
    owns_state(o.owns_state)
{
    const_cast<Exception&>(o).Disown();
}


Exception::~Exception() throw()
{
    if(owns_state) {
        PyErr_Clear();
    }
}

Exception::Exception(std::string _type, std::string _msg, bool own) throw():
    type(_type),
    msg(_msg),
    owns_state(own)
{
    
}

const char* Exception::Message() const throw()
{
    return msg.c_str();
}

const char* Exception::Type() const throw()
{
    return type.c_str();
}


Exception::operator const char*() const throw()
{
    return (type+": "+msg).c_str();
}

}
