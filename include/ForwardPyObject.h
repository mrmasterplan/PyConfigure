#ifndef FORWARDPYOBJECT_H_CW5XG0IG
#define FORWARDPYOBJECT_H_CW5XG0IG

// This is how to avoid including Python.h in the header.
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif


#endif /* end of include guard: FORWARDPYOBJECT_H_CW5XG0IG */
