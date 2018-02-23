

// This lib provides functions that help to create simple XML-logfiles.
// Version 1.3.1    |   big_changes.new_functions.bugs_fixed
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

const char                  INTRO[] =
"\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<?xml-stylesheet href=\"Styles.css\"?>\n\n\
<MAIN>\
";

const char                  OUTRO[] =
"</MAIN>";

const char        FATAL_ERROR_BEG[] = "<FATAL_ERROR>";
const char        FATAL_ERROR_END[] = "</FATAL_ERROR>\n";

const char              ERROR_BEG[] = "<ERROR>";
const char              ERROR_END[] = "</ERROR>\n";

const char            WARNING_BEG[] = "<WARNING>";
const char            WARNING_END[] = "</WARNING>\n";

const char               INFO_BEG[] = "<INFO>";
const char               INFO_END[] = "</INFO>\n";

enum MSG_TYPE
{
    FATAL_ERROR,
    ERROR,
    WARNING,
    INFO
};

// =================================================    OUTPUT FILE EXTENTIONS

const char                TXT_EXT[] = ".txt";
const char                XML_EXT[] = ".xml";

enum EXTENTION_TYPE
{
    TXT,
    XML
};

// =================================================    COLORS

const char                  BLUE[] = "\x1b[34m";
const char                   RED[] = "\x1b[91m";
const char                 GREEN[] = "\x1b[92m";
const char                YELLOW[] = "\x1b[93m";
const char                PURPLE[] = "\x1b[200m";
const char                  CYAN[] = "\x1b[96m";
const char               MAGENTA[] = "\x1b[95m";
const char               DEFAULT[] = "\x1b[0m ";

// =================================================    FUNCTIONS

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

/// Appends extention
/**
    Retuns updated base_name or nullptr in case of fault

    \param [in, out]    base_name       Main part of the name of the file
    \param [in]         extention       Extention to be added

    \warning base_name MUST have enough space after '\0'!
*/
char* AppendExtention(char* base_name, int extention);

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



// =================================================    MACRO

#define VAR( name ) #name

#endif // LOG_H_INCLUDED
