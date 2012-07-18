#include <iostream>
#include <string>
#include "../include/ConfigurePyDict.h"

int main (int /*argc*/, char const * /*argv*/ [])
{
    std::cout<<"This is unittest."<<std::endl;
    ConfigurePy::Dict dict;

    try {
        std::cout<<"broken construct..."<<std::endl;
        dict=
            "a=5\n"
            "s\n";
        std::cout<<"... is working"<<std::endl;
    } catch(ConfigurePy::Exception& e) {
        std::cout<<"...breaks: "<<e<<std::endl;
        // e.Disown();
        // ConfigurePy::Exception::Clear();
    }

    try {
        std::cout<<"working construct..."<<std::endl;
        dict="a=5\n"
             "s='hello'\n"
             "v=[1,2,3]\n"
             "vs=['hello','world']\n"
             "f=3.1415\n"
             "d=dict(\n"
             "a=3\n"
             ")\n";
        int i = dict["a"];
        std::cout<<"i is "<<i<<std::endl;
        
        std::cout<<"d is "<<(std::string)dict["d"]<<std::endl;

        std::string s = dict["s"];
        std::cout<<"s is "<<s<<std::endl;

        std::vector<int> v = dict["v"];
        std::cout<<"v has size "<<v.size()<<std::endl;
        std::cout<<"and elements: ";
        for ( size_t i = 0; i < v.size(); ++i ) {
            std::cout<<v[i]<<", ";
        }
        std::cout<<std::endl;


        std::vector<std::string> vs = dict["vs"];
        std::cout<<"vs has size "<<vs.size()<<std::endl;
        std::cout<<"and elements: ";
        for ( size_t i = 0; i < vs.size(); ++i ) {
            std::cout<<vs[i]<<", ";
        }
        std::cout<<std::endl;

        double f = dict["f"];
        std::cout<<"f is "<<f<<std::endl;

        ConfigurePy::Dict second = dict["d"];

        int a = second["a"];
        std::cout<<"second.a = "<<a<<std::endl;
        std::cout<<"second.a = "<<(int)dict["d"]["a"]<<std::endl;

        std::cout<<"...works"<<std::endl;
    } catch(ConfigurePy::Exception& e) {
        std::cout<<"ERROR: "<<e<<std::endl;
        return 1;
    }


    return 0;
}