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
            
            if(!msg){
                // if(type!=NULL){
                //     message = PyBytes_AsString(type);
                //     message+=": ";
                // }
                message+= PyBytes_AsString(value);
            }
            
            PyErr_Restore(type,value,trc);
            
            throw Exception(message.c_str());
        }
        DBG;
    }
    
    // void Exception::Clear() throw()
    // {
    //     PyErr_Clear();
    // }
    
    void Exception::Disown() throw()
    {
        owns_state=0;
    }
    
    Exception::Exception(bool own) throw():
        owns_state(own)
    {
        DBG;
        // std::cout<<"My Text"<<std::endl;
    }
    
    Exception::Exception(const Exception& o) throw():
        msg(o.msg),
        owns_state(o.owns_state)
    {
        const_cast<Exception&>(o).owns_state = 0;
        DBG;
    }
    
    
    Exception::~Exception() throw()
    {
        if(owns_state){
            // std::cout<<"clearing exception down."<<std::endl;
            PyErr_Clear();
        }
        DBG;
    }
    
    Exception::Exception(const char * _msg, bool own) throw():
        msg(),
        owns_state(own)
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
