#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <cstdio>
#include <iostream>
#include "../Log/Log.h"

// =================================================    SAFENESS
// Comment next line in order to turn safeness off
#define __SAFE
#ifdef  __SAFE
    #define SAFE
#else
    #define SAFE if(0)
#endif // __SAFE

// Preventing multiple filenames during developing
#define __DEVELOP_IS_IN_ACTION
#ifdef  __DEVELOP_IS_IN_ACTION
    #define TMP_OFF( something )
    #define TMP_ON( something ) something
#else
    #define TMP_OFF( something ) something
    #define TMP_ON( something )
#endif // __DEVELOP_IS_IN_ACTION


// Data type in stack
typedef double data_t;

// Service constants
const int CANARY                = -12345;
const int DELETED               = 10110111;


class Stack {
private:
    /// First canary
    int         _first_canary   = CANARY;

// =================================================    SERVICE
    /// Log file
    FILE*       _log_file       = nullptr;

    /// Name of the object
    TMP_OFF (   char        _name[sizeof(int*) + 5] = {};       )
    TMP_ON  (   char        _name[sizeof(int*) + 5] = "name";   )

    /// Stack status
    bool        _ready          = true;

// =================================================    STACK PROPERTIES
    /// Current capacity
    unsigned    _capacity       = 0;

    /// Current amount of elements in the stack
    unsigned    _n_elements     = 0;

    /// Stack
    data_t*     _stack          = nullptr;

// =================================================    INNER FUNCTIONS

    /// Last canary
    int         _last_canary    = CANARY;

public:
    /// Constructor
    Stack();

    /// Destructor
    ~Stack();

    //
    // int      Dump
    // int      Push
    // int      Pop
    //
};

#endif // STACK_H_INCLUDED
