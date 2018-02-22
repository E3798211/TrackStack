#include "Log.h"

int InitLog(FILE* log_file)
{
    assert(log_file != nullptr);

    fprintf(log_file, "%s", INTRO);

    return SUCCESS;
}

unsigned Log(int message_type, FILE* log_file, const char* format, ...)
{
    assert(log_file != nullptr);
    assert(format   != nullptr);

    va_list  arguments_list;
    va_start(arguments_list, strlen(format));

    // "Opening" message in the file
    switch (message_type)
    {
        case FATAL_ERROR:
            fprintf(log_file, "%s", FATAL_ERROR_BEG);
        break;

        case ERROR:
            fprintf(log_file, "%s", ERROR_BEG);
        break;

        case WARNING:
            fprintf(log_file, "%s", WARNING_BEG);
        break;

        case INFO:
            fprintf(log_file, "%s", INFO_BEG);
        break;

        default:
            return 0;
    }

    // Placing message in the file
    unsigned i = 0;
    while(format[i] != '\0')
    {
        switch(format[i])
        {
            case 'u':
                fprintf(log_file, "%u ",  va_arg(arguments_list, unsigned));
            break;

            case 'i':
                fprintf(log_file, "%d ",  va_arg(arguments_list, int));
            break;

            case 'd':
                fprintf(log_file, "%lg ", va_arg(arguments_list, double));
            break;

            case 'c':
                fprintf(log_file, "%d ",  va_arg(arguments_list, char));
            break;

            case 's':
                fprintf(log_file, "%s ",  va_arg(arguments_list, char*));
            break;

            default:
            break;
        }
        i++;
    }

    // "Closing" message
    switch (message_type)
    {
        case FATAL_ERROR:
            fprintf(log_file, "%s", FATAL_ERROR_END);
        break;

        case ERROR:
            fprintf(log_file, "%s", ERROR_END);
        break;

        case WARNING:
            fprintf(log_file, "%s", WARNING_END);
        break;

        case INFO:
            fprintf(log_file, "%s", INFO_END);
        break;
    }

    return i;
}

