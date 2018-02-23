

// This lib provides functions that help to create simple XML-logfiles.
// Version 1.1.1    |   big_changes.new_functions.bugs_fixed
//
// Current version needs file "Styles.css" placed in the same directory with log file.
// Please do not forget about it.



#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <assert.h>
#include <cstdio>
#include <iostream>
#include <stdarg.h>
#include <cstring>

#include "Errors.h"

// =================================================    SERVICE

const char INTRO[]              =
"\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<?xml-stylesheet href=\"Styles.css\"?>\n\n\
<MAIN>\
";

const char OUTRO[]              =
"</MAIN>";

const char FATAL_ERROR_BEG[]    = "<FATAL_ERROR>";
const char FATAL_ERROR_END[]    = "</FATAL_ERROR>\n";

const char ERROR_BEG[]          = "<ERROR>";
const char ERROR_END[]          = "</ERROR>\n";

const char WARNING_BEG[]        = "<WARNING>";
const char WARNING_END[]        = "</WARNING>\n";

const char INFO_BEG[]           = "<INFO>";
const char INFO_END[]           = "</INFO>\n";

// =================================================    FUNCTIONS

enum MSG_TYPE
{
    FATAL_ERROR,
    ERROR,
    WARNING,
    INFO
};

/// Initializes log file
/**
    Returns SUCCESS in case of success, error code otherwise.

    \param [in]     log_file        Log file
*/
int InitLog(FILE* log_file);

/// Finishes log file
/**
    Returns SUCCESS in case of success, error code otherwise.

    \param [in]     log_file        Log file
*/
int FinishLog(FILE* log_file);

/// Prints message to the log file
/**
    Returns amount of arguments printed.

    \param [in]     message_type    One of the types: FATAL_ERROR, ERROR, WARNING, INFO
    \param [in]     log_file        Log file
    \param [in]     format          Format of arguments to be put in log file

    Parameter "format" takes next values according to the arguments:
            u       for     unsigned integer
            i       for     integer
            d       for     double
            s       for     string
*/
unsigned Log(int message_type, FILE* log_file, const char* format, ...);

#endif // LOG_H_INCLUDED
