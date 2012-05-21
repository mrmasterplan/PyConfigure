#ifndef WRAPPER_H_1HY2Z3IC
#define WRAPPER_H_1HY2Z3IC

#include "ForwardPyObject.h"

namespace PyConfigure {
    class Wrapper{
    private:
        friend class Result;
        
        static size_t MySequence_Size(PyObject*);
        static PyObject* MySequence_GetItem(PyObject*,size_t i);
        
        
        Wrapper();
        Wrapper(const Wrapper&);
        ~Wrapper();
    };
}


#endif /* end of include guard: WRAPPER_H_1HY2Z3IC */
