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

template <typename data_T>
class Stack {
private:
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
    data_T*     _stack          = nullptr;

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
    int Push(data_T new_elem);

    /// Pop method
    /**
        Returns error code.

        \param [out]    container       Container for the popped element
    */
    int Pop(data_T* container);

    /// Prints as much info as possible
    int Dump(const char* call_func = __FUNCTION__);
};


#define DumpFunc()      Dump(__FUNCTION__)
#define EnterFunc()     Log(INFO, _log_file, "sss", ENTERED, __FUNCTION__, "()");
#define QuitFunc()      Log(INFO, _log_file, "sss", QUITED , __FUNCTION__, "()");

#define SimpleCheck()                                                           \
        do {                                                                    \
            CheckStack();                                                       \
            if(!_ready)                                                         \
            {                                                                   \
                Log(ERROR, _log_file, "sss", CANCELLED, __FUNCTION__, "()");    \
                Log(ERROR, _log_file, "ss",   REASON,    BROKEN);               \
                                                                                \
                EXT_LOGS DumpFunc();                                            \
                                                                                \
                return ERR_CODES::EBROKEN;                                      \
            }                                                                   \
        }while(0)                                                               \


#define EnterCheck(condition, error)                                            \
        do {                                                                    \
            SimpleCheck();                                                      \
            if((condition))                                                     \
            {                                                                   \
                Log(ERROR, _log_file, "sss", CANCELLED, __FUNCTION__, "()");    \
                Log(ERROR, _log_file, "ss" , REASON, error);                    \
                                                                                \
                EXT_LOGS DumpFunc();                                                \
                                                                                \
                return ERR_CODES::E##error;                                     \
            }                                                                   \
        }while(0)

// =============================================================    PRIVATE

template <typename data_T>
bool Stack<data_T>::CheckStack()
{
    EnterFunc();

    if(_deleted)                                _ready = false;
    if(_stack == nullptr)                       _ready = false;
    if(_stack[0]                != CANARY)      _ready = false;
    if(_stack[_capacity - 1]    != CANARY)      _ready = false;

    QuitFunc();
    return _ready;
}

template <typename data_T>
int Stack<data_T>::StackResize(size_t new_size)
{
    EnterFunc();

    // SAFE SimpleCheck();

    // EXT_LOGS DumpFunc();

    data_T* tmp = nullptr;
    try
    {
        tmp = new data_T [new_size];
    }
    catch(std::bad_alloc& ex)
    {
        // Log(ERROR, _log_file, "sss", CANCELLED, __FUNCTION__, "()");
        // Log(ERROR, _log_file, "ssu", REASON, ALLOC_FAIL, new_size * sizeof(data_T));

        // EXT_LOGS DumpFunc();

        QuitFunc();
        return ERR_CODES::EALLOC_FAIL;
    }

    unsigned min_length = (_capacity < new_size) ? _capacity : new_size;

    for(size_t i = 0; i < min_length; i++)
        tmp[i] = _stack[i];

    delete [] _stack;
    _stack = tmp;

    // _stack[0]               = CANARY;
    // _stack[new_size - 1]    = CANARY;

    _capacity = new_size;

    // Log(INFO, _log_file, "sss", EXECUTED, __FUNCTION__, "()");

    // EXT_LOGS DumpFunc();

    // SAFE SimpleCheck();

    QuitFunc();
    return ERR_CODES::ESUCCESS;
}

// =============================================================    PUBLIC

template <typename data_T>
Stack<data_T>::Stack():
    // _first_canary   (CANARY),
    _n_elements     (0),
    // _last_canary    (CANARY),
    _ready          (true)
{
    #ifdef _MULTIPLE_FILENAMES

        // Creating unique name for each object
        for(size_t i = 0; i < sizeof(int*) - 1; i++)
            _name[i] = 65 + (uintptr_t)this % (16 + i);
        _name[sizeof(int*) - 1] = '\0';

    #endif // _MULTIPLE_FILENAMES

    AppendExtention  (_name, XML);

    _log_file = fopen(_name, "w");
    if(_log_file == nullptr)
    {
        fprintf(stderr, "%s\tFailed to create logfile!\n%s", RED, DEFAULT);
        _ready = false;

        QuitFunc();
        return;
    }
    // InitLog  (_log_file);
    // Log(INFO, _log_file, "s", "Log file created");


    try
    {
        _stack = new data_T [2];
    }
    catch(std::bad_alloc& ex)
    {
        Log(FATAL_ERROR, _log_file, "su", ALLOC_FAIL, 2u * sizeof(int));
        _ready = false;

        QuitFunc();
        return;
    }

    _stack[0] = CANARY;
    _stack[1] = CANARY;

    _n_elements = 0;
    _capacity   = 2;

    // EXT_LOGS DumpFunc();
}

template <typename data_T>
Stack<data_T>::~Stack()
{
    if(!_deleted)
    {
        delete [] _stack;
        _n_elements     = DELETED;
        _capacity       = DELETED;
        // _first_canary   = DELETED;
        // _last_canary    = DELETED;

        _deleted        = true;

        // EXT_LOGS DumpFunc();

        // Log(INFO, _log_file, "sss", "Stack ", _name, "successfuly deleted");
        // FinishLog(_log_file);
        fclose   (_log_file);
    }
}

template <typename data_T>
int Stack<data_T>::Push(data_T new_elem)
{
    EnterFunc();

    // SAFE EnterCheck((_capacity > MAX_CAPACITY), OVERFLOWN);

    // EXT_LOGS DumpFunc();

    StackResize(_capacity + 1);
    _stack[++_n_elements] = new_elem;

    std::cout << "pushed " << new_elem << std::endl;

    // SAFE SimpleCheck();

    // EXT_LOGS DumpFunc();

    // Log(INFO, _log_file, "sss", EXECUTED, __FUNCTION__, "()");
    QuitFunc();
    return ESUCCESS;
}

template <typename data_T>
int Stack<data_T>::Pop(data_T* container)
{
    EnterFunc();
    // SAFE EnterCheck((_capacity <= MIN_CAPACITY), UNDERFLOWN);

    assert(container != nullptr);

    // EXT_LOGS DumpFunc();

    *container = _stack[_n_elements--];
    StackResize(_capacity - 1);

    std::cout << "poped  " << *container << std::endl;

    // EXT_LOGS DumpFunc();

    // SAFE SimpleCheck();

    // Log(INFO, _log_file, "sss", EXECUTED, __FUNCTION__, "()");
    QuitFunc();
    return ERR_CODES::ESUCCESS;
}

#define  DumpInt( var )  Log(DUMP, _log_file, "ssi", VAR(var), "=", (var));
#define DumpUint( var )  Log(DUMP, _log_file, "ssu", VAR(var), "=", (var));
#define DumpDble( var )  Log(DUMP, _log_file, "ssd", VAR(var), "=", (var));
#define  DumpStr( var )  Log(DUMP, _log_file, "sss", VAR(var), "=", (var));

/*
template <typename data_T>
int Stack<data_T>::Dump(const char* call_func)
{
    if(_log_file == nullptr)
    {
        fprintf(stderr, "%s\tLogfile closed. UPD me.%s\n", RED, DEFAULT);
        return ERR_CODES::EOPERATION_CANCELLED;
    }

    Log(DUMP, _log_file, "sss", "Dump from ", call_func, "(): ");

    /*
    if(_first_canary == CANARY)
    {
        DumpInt(_first_canary);
    }
    else
    {
        Log(ERROR, _log_file, "s", "First canary dead");
        return ERR_CODES::EBROKEN;
    }
    if( _last_canary == CANARY)
    {
        DumpInt( _last_canary);
    }
    else
    {
        Log(ERROR, _log_file, "s", "Second canary dead");
        return ERR_CODES::EBROKEN;
    }
    */
    /*
    DumpStr (_name);
    DumpUint(_capacity);
    DumpUint(_n_elements);

    if(_stack == nullptr)
    {
        Log(ERROR, _log_file, "s", "_stack is nullptr");
        return ERR_CODES::EBROKEN;
    }
    size_t i = 0;
    while(i < _capacity)
    {
        Log(DUMP, _log_file, "susd", "_stack[", i, "\t] = ", _stack[i]);
        i++;
    }

    return ERR_CODES::ESUCCESS;
}
*/
#endif // STACK_H_INCLUDED
