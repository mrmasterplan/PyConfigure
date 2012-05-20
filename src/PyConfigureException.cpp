#include <Python.h>
#include "../include/Debug.h"
#include "../include/PyConfigureException.h"
#include <string>

namespace PyConfigure {
    
    void Exception::ThrowIfRelevant(const char* msg) throw(Exception)
    {
        
        DBG;
        PyObject* err = PyErr_Occurred();
        if ( err ) {
            std::string message;
            if(msg) message = msg;
            
            PyObject *type=NULL, *value=NULL, *trc=NULL;
            PyErr_Fetch(&type,&value,&trc);
            
            #ifdef BUILDTESTS
            PyErr_Print();
            #endif
            
            if(!msg) message = PyBytes_AsString(value);
            
            PyErr_Restore(type,value,trc);
            
            throw Exception(message.c_str());
        }
        DBG;
    }
    
    Exception::Exception() throw()
    {
        DBG;
        // std::cout<<"My Text"<<std::endl;
    }
    
    Exception::Exception(const Exception& o) throw():
        msg(o.msg)
    {
        DBG;
    }
    
    
    Exception::~Exception() throw()
    {
        DBG;
    }
    
    Exception::Exception(const char * _msg) throw()
    {
        DBG;
        if(_msg!=0){
            // std::cout<<"message is "<<_msg<<std::endl;
            msg=_msg;
        }
        DBG;
    }
    
    Exception::operator const char*() throw()
    {
        DBG;
        return msg.c_str();
    }
    
}
