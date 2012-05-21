#ifndef CONFIGUREPYDICT_H_HD30VJXO
#define CONFIGUREPYDICT_H_HD30VJXO

#include <exception>
#include <string>
#include <vector>

#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif


namespace ConfigurePy
{
// The Dict is the type that is directly used by the user.
class Dict;
// The base class for any python exception that can occur
class Exception;
// The result class is the object returned by the dictionary access functions.
// it can be cast to a number of c++ types.
class Result;

// Ref holds a reference to a PyObject and handles the reference count automatically.
class Ref
{
public:
    Ref() throw();
    Ref(PyObject*) throw();
    ~Ref() throw();
    Ref& operator=(PyObject*) throw();
    operator PyObject*() const;
    operator bool() const {
        return data;
    };
    void Inc() throw();
    void Dec() throw();
    // PyObject* NewRef() throw();
    PyObject* Steal() throw();
private:
    PyObject* data;
};

class Exception : public std::exception
{
public:
    static void ThrowIfRelevant() throw(Exception);
    Exception(bool owner = 1) throw();
    Exception(std::string type, std::string msg, bool owner = 1) throw();
    Exception(const Exception& o) throw();
    virtual ~Exception() throw();
    operator const char*() const throw();
    const char* Message() const throw();
    const char* Type() const throw();
    void Disown() throw();
private:
    std::string type;
    std::string msg;
    bool owns_state;
};


class Result
{
    friend class Dict;
public:
    ~Result();

    operator Dict() const throw(Exception);

    // fundamental
    operator double() const throw(Exception);
    operator long() const throw(Exception);
    operator std::string() const throw(Exception);
    operator bool() const throw(Exception);

    // derived
    operator float() const throw(Exception) {
        return (double)(*this);
    }
    operator int() const throw(Exception) {
        return (long)(*this);
    }
    operator unsigned int() const throw(Exception) {
        return (long)(*this);
    }

    Result operator[] (const char* key) throw(Exception);

    // operator std::vector<int>() const;
    template<typename T>
    operator std::vector<T>() const throw(Exception) {
        std::vector<T> vec(Sequence_Size(m_obj));
        for ( size_t i = 0; i < vec.size(); ++i ) {
            vec[i]=(T)Result(Sequence_GetItem(m_obj,i));
        }
        return vec;
    }

private:
    Result();
    Result(PyObject*);
    Result(const Result&);
    static PyObject* Sequence_GetItem(PyObject*,size_t i);
    static size_t Sequence_Size(PyObject*);

    Ref m_obj;
};


class Dict
{
public:
    Dict() throw();
    Dict(PyObject*) throw();
    Dict(const Dict&) throw();
    ~Dict() throw();

    Dict& operator = (const Dict&) throw();
    Dict& operator = (PyObject*) throw(Exception);
    Dict& operator = (const char*) throw(Exception);

    Result operator[] (const char*) throw(Exception);

private:
    void InitPy() throw();
    Ref m_py_dict;
};
}


#endif /* end of include guard: CONFIGUREPYDICT_H_HD30VJXO */
