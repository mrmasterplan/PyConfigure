// call_function.c - A sample of calling 
// python functions from C code
// 
// compile with
// $ clang++ -I /Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/ -lpython2.7 get_stuff.cpp -o get_stuff


#include <Python.h>
#include "iostream"
#include <exception>

// TPython already does almost all that I want to do :(
// The rest is not worth the hassle.
// 
/*
My thoughts:
  - make a class that hold configuration data.
  - one can pass a string with python code which is then parsed into an internal dictionary.
  - a python dictionary can be passed directly if it is available either from python or from
    another C api program. The dictionary replaced the internal one.
  - The calib object has move semantics like python objects. It is only needed to read from.
    Deep copying is not possible.
  - The object can be queried with a get(string) function. The result object has cast operators
    to a number of standard calibration type objects like:
        - ints
        - double
        - bools
        - strings
        - vector<int>
        - vector<double>
        - vector<bool>
        - vector<string>
        - another calib dict object
  - The last kind would be the result of the key being found to be a dict.
  - The result object would not be possible to be copied, stored, or assigned. This way one is
    forced to cast it immediately.
  - in all the class would be well suited to configure code that may be called both from C++ code
    or from a python api, without having to pass down a lot of individual config options.
/Simon
    
*/

class PyException : public std::exception
{
public:
  PyException() throw(){}
  PyException(const PyException&) throw(){}
  ~PyException() throw(){}  
};

class PythonParser;

int ThrowIfPyExcept(){
    if ( PyErr_Occurred() ) {
        // PyErr_Print();
        PyErr_Clear();
        throw PyException();
    }
    return 0;    
}

class PyObjectOwner; // smart PyObject pointer that decrements the ref count on deletion

int main(int argc, char *argv[])
{
    // PyObject *py_a, *py_s, *string_result, *globals, *locals;

    std::cout<<"initializing..."<<std::endl;
    // Initialize the Python Interpreter
    Py_Initialize();
    
    std::cout<<"build globals"<<std::endl;
    PyObject *globals = Py_BuildValue("{}");
    ThrowIfPyExcept();
    
    // std::cout<<"build locals"<<std::endl;
    // PyObject *locals = Py_BuildValue("{}");
    // ThrowIfPyExcept();
    

    std::cout<<"run..."<<std::endl;
    PyObject *string_result = PyRun_StringFlags(""
        "a=5\n"
        "s='hello'\n"
        // "p\n"
        // "print s\n"
        ,
        Py_file_input, globals, globals, NULL);
    // Py_file_input, globals, locals, NULL);
    ThrowIfPyExcept();

    PyObject *py_a = PyDict_GetItemString(globals, "a");
    ThrowIfPyExcept();
    
    long a = PyLong_AsLong( py_a );
    ThrowIfPyExcept();

    std::cout<<"a is "<<a<<std::endl;

    PyObject *py_s = PyDict_GetItemString(globals, "s");
    ThrowIfPyExcept();

    const char* s = PyBytes_AsString( py_s );
    ThrowIfPyExcept();

    std::cout<<"s is "<<s<<std::endl;
    
    // Clean up
    Py_DECREF(globals);
    // Py_DECREF(locals);
    Py_DECREF(string_result);

    // Finish the Python Interpreter
    Py_Finalize();

    return 0;
}