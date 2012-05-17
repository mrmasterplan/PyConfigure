PyConfigure
===========

C++ class that uses a python dictionary to hold an arbitrary amount of configuration data.

TPython already does almost all that I want to do :(  
The rest is not worth the hassle.

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

Usage will be through a single PyConfigure.h.
Then:

    PyConfigure::Dict mydict;
    mydict =    "#Python yay"
                "a=5\n"
                "s='hello'\n"
                "v=[1,2,3]\n"
                "delegated=dict("
                    "a=1,"
                    "b='meh'"
                    ")\n";
    int a = mydict["a"];
    string s = mydict["s"];
    vector<int> = mydict["v"];
    PyConfigure::Dict otherdict = mydict["delegated"];
    
all python exceptions become C++ exceptions.

Copyright Simon Heisterkamp 2012
