#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <cstdio>
#include <iostream>
#include <climits>
#include "../Log/Log.h"

// =================================================    SAFENESS
// Comment next line in order to turn safeness off
#define __SAFE
#ifdef  __SAFE
    #define SAFE
#else
    #define SAFE if(0)
#endif // __SAFE

// Preventing multiple filenames
// #define _MULTIPLE_FILENAMES

// Extended logs
#define _EXT_LOGS
#ifdef _EXT_LOGS
    #define EXT_LOGS
#else
    #define EXT_LOGS if(0)
#endif // _EXT_LOGS

// Stack data type
typedef double data_t;

// Service constants
const int                CANARY = -12345;
const int               DELETED = 10110111;

const int               RESERVE = 10;
const int          MIN_CAPACITY = 2;
const int          MAX_CAPACITY = UINT_MAX - RESERVE;

const char            ENTERED[] = "Entered: ";
const char             QUITED[] = "Quited : ";
const char        UNEXPECTRED[] = "Unexpected error in ";
const char           EXECUTED[] = "Executed successfully: ";
const char             REASON[] = "Reason: ";
const char          CANCELLED[] = "Operation cancelled: ";
const char         ALLOC_FAIL[] = "Failed to allocate bytes: ";
const char          OVERFLOWN[] = "Stack overflown";
const char         UNDERFLOWN[] = "Stack underflown";
const char             BROKEN[] = "Stack broken";

class Stack {
private:
    /// First canary
    int         _first_canary   = CANARY;

// =================================================    SERVICE
    /// Log file
    FILE*       _log_file       = nullptr;

    /// Name of the object
    #ifdef _MULTIPLE_FILENAMES
        char        _name[sizeof(int*) + 5] = {};
    #else
        char        _name[sizeof(int*) + 5] = "name";
    #endif // _MULTIPLE_FILENAMES

    /// Stack status
    bool        _ready          = true;

    /// Stack is deleted?
    bool        _deleted        = false;

// =================================================    STACK PROPERTIES
    /// Current capacity
    size_t      _capacity       = 0;

    /// Current amount of elements in the stack
    size_t      _n_elements     = 0;

    /// Stack
    data_t*     _stack          = nullptr;

// =================================================    INNER FUNCTIONS

    /// Checks if stack is in correct state
    /**
        Returns true if stack is ok, false otherwise
    */
    bool CheckStack();

    /// Resizes Stack
    /**
        Returns error code.

        \param [in]     new_size        New size

        Just cuts or extends _stack.
    */
    int StackResize(size_t new_size);

    /// Last canary
    int         _last_canary    = CANARY;

public:
    /// Constructor
    Stack();

    /// Destructor
    ~Stack();

    /// Push method
    /**
        Returns error code.

        \param [in]     new_elem        Next elem in the stack
    */
    int Push(data_t new_elem);

    /// Pop method
    /**
        Returns error code.

        \param [out]    container       Container for the popped element
    */
    int Pop(data_t* container);

    /// Prints as much info as possible
    int Dump(const char* call_func = __FUNCTION__);
};

#endif // STACK_H_INCLUDED
