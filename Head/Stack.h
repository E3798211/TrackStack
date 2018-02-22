#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <cstdio>
#include <iostream>

#include "../Log/Log.h"

// Data type in stack
typedef double data_t;

// Service constants
const int CANARY                = -12345;


class Stack {
private:
    /// First canary
    int         _first_canary   = CANARY;

// =================================================    SERVICE
    /// Log file
    FILE*       _log_file       = nullptr;

// =================================================    STACK PROPERTIES
    /// Current capacity
    unsigned    _capacity       = 0;

    /// Current amount of elements in the stack
    unsigned    _n_elements     = 0;

    /// Stack
    data_t*     _stack          = nullptr;

// =================================================    INNER FUNCTIONS
    // Dump (console)
    // Hash
    // PopCore()

    /// Last canary
    int         _last_canary    = CANARY;

public:
    /// Constructor
    Stack();

    //
    // int      Push
    // int      Pop
    // data_t   Pop
    //
};

#endif // STACK_H_INCLUDED
