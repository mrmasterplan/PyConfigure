#ifndef PYCONFIGURERESULT_H_SYA6P5HL
#define PYCONFIGURERESULT_H_SYA6P5HL

#include <vector>
#include <string>
#include "PyConfigurePyRef.h"
#include "ForwardPyObject.h"
#include "PyConfigureException.h"
#include "PyConfigurePyRef.h"
#include "Debug.h"
#include "Wrapper.h"

namespace PyConfigure {
    class Dict;

    class Result {
        friend class Dict;
    public:
        ~Result();
        
        operator Dict() const throw(Exception);
        
        // fundamental
        operator double() const throw(Exception);
        operator long() const throw(Exception);
        operator std::string() const throw(Exception);

        // derived
        operator bool() const throw(Exception){return (long)(*this);}
        operator float() const throw(Exception){return (double)(*this);}
        operator int() const throw(Exception){return (long)(*this);}
        operator unsigned int() const throw(Exception){return (long)(*this);}
        
        Result operator[] (const char* key) throw(Exception);
        
        // operator std::vector<int>() const;
        template<typename T>
        operator std::vector<T>() const throw(Exception)
        {
            size_t length =  Wrapper::MySequence_Size(m_obj);
            DBG;
            std::vector<T> vec(length);
            DBG;
            for ( size_t i = 0; i < length; ++i ) {
                DBG;
                PyRef item = Wrapper::MySequence_GetItem(m_obj,i);
                DBG;
                vec[i]=(T)Result(item);
                DBG;
            }
            return vec;
        }

    private:
        // Result();
        Result(PyObject*);
        
        PyRef m_obj;
    };

}

#endif /* end of include guard: PYCONFIGURERESULT_H_SYA6P5HL */
