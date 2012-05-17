#ifndef PYCONFIGURERESULT_H_SYA6P5HL
#define PYCONFIGURERESULT_H_SYA6P5HL

#include <vector>
#include <string>

namespace PyConfigure {
    class Dict;

    class Result {
        friend class Dict;
    public:
        ~Result();
        
        operator Dict() const;
        
        operator double() const;
        operator float() const;
        operator int() const;
        operator unsigned int() const;
        operator std::string() const;
        
        operator std::vector<double>() const;
        operator std::vector<float>() const;
        operator std::vector<int>() const;
        operator std::vector<unsigned int>() const;
        operator std::vector<std::string>() const;
        
    private:
        Result();
        Result(const Result&);
    };

}

#endif /* end of include guard: PYCONFIGURERESULT_H_SYA6P5HL */
