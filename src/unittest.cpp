#include <iostream>
#include "include/PyConfigure.h"

int main (int /*argc*/, char const * /*argv*/ [])
{
    std::cout<<"This is unittest."<<std::endl;
    PyConfigure::Dict dict;
    try{
        std::cout<<"working construct..."<<std::endl;
        dict=
            "a=5\n"
            "s='hello'\n";
        std::cout<<"... is working"<<std::endl;
    }catch(PyConfigure::Exception& e){
        std::cout<<"ERROR: "<<e<<std::endl;
        return 1;
    } 
 
    try{
        std::cout<<"broken construct..."<<std::endl;
        dict=
            "a=5\n"
            "s\n";
        std::cout<<"... is working"<<std::endl;
    }catch(PyConfigure::Exception e){
        std::cout<<"...breaks: "<<e<<std::endl;
    } 
    
 
    
    return 0;
}