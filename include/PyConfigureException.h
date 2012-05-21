#ifndef PYCONFIGUREEXCEPTION_H_3WAXS1Q1
#define PYCONFIGUREEXCEPTION_H_3WAXS1Q1

#include <exception>
#include <string>

namespace PyConfigure {    
    class Exception : public std::exception
    {
    public:
        static void ThrowIfRelevant(const char* message=0) throw(Exception);
        // static void Clear() throw();

        Exception(bool owner = 1) throw();
        Exception(const char * _msg,bool owner = 1) throw();
        Exception(const Exception& o) throw();
        virtual ~Exception() throw();
        operator const char*() throw();
        
        void Disown() throw();
        
    private:
        std::string msg;
        bool owns_state;
    };

}

#endif /* end of include guard: PYCONFIGUREEXCEPTION_H_3WAXS1Q1 */
