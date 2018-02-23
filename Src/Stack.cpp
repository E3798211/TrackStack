#include "../Head/Stack.h"

Stack::Stack():
    _first_canary   (CANARY),
    _n_elements     (0),
    _last_canary    (CANARY),
    _ready          (true)
{
    TMP_OFF
    (
        // Creating unique name :)
        for(int i = 0; i < sizeof(int*) - 1; i++)
            _name[i] = 65 + (uintptr_t)this % (16 + i);
        _name[sizeof(int*) - 1] = '\0';
    )

    AppendExtention  (_name, XML);

    _log_file = fopen(_name, "w");
    if(_log_file == nullptr)
    {
        fprintf(stderr, "%s\tFailed to create logfile!\n%s", RED, DEFAULT);
        _ready = false;
        return;
    }
    InitLog  (_log_file);
    Log(INFO, _log_file, "s", "Log file created");


    try
    {
        _stack = new data_t [3];
    }
    catch(std::bad_alloc& ex)
    {
        fprintf(stderr, "%s\tFailed to allocate 3 bytes!\n%s", RED, DEFAULT);
        Log(FATAL_ERROR, _log_file, "s", "Failed to allocate 3 bytes!");
        _ready = false;
    }

    _stack[0] = CANARY;
    _stack[1] = 0;
    _stack[2] = CANARY;

    _n_elements = 0;
    _capacity   = 3;

    // Dump

}

Stack::~Stack()
{
    if(_ready)
    {
        delete [] _stack;
        _n_elements     = DELETED;
        _capacity       = DELETED;
        _first_canary   = DELETED;
        _last_canary    = DELETED;

        _ready          = false;


        Log(INFO, _log_file, "sss", "Stack ", _name, "successfuly deleted");
        FinishLog(_log_file);
        fclose   (_log_file);
    }
}


