#ifndef PYCONFIGUREEXCEPTION_H_3WAXS1Q1
#define PYCONFIGUREEXCEPTION_H_3WAXS1Q1

#include <exception>
#include <string>

namespace PyConfigure {    
    class Exception : public std::exception
    {
    public:
        static void ThrowIfRelevant(const char* message=0) throw(Exception);

        Exception() throw();
        Exception(const char * _msg) throw();
        Exception(const Exception& o) throw();
        virtual ~Exception() throw();
        operator const char*() throw();
        
    private:
        std::string msg;
    };

}

#endif /* end of include guard: PYCONFIGUREEXCEPTION_H_3WAXS1Q1 */
