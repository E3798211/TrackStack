#include <iostream>

#include "Head/Stack.h"

int main()
{

    /*
    FILE* a = fopen("a.xml", "w");
    InitLog(a);
    Log(FATAL_ERROR, a, "is", 5,    "hey");
    Log(ERROR,       a, "ds", 5.6,  "String");
    Log(INFO,        a, "s", "Long string, very long string");
    Log(INFO,        a, "s", "Long string, very long string");

    Log(WARNING,     a, "is", 5, "SSSS");

    FinishLog(a);
    */


    Stack a;
    a.Push(1.3);
    a.Push(1.3);
    a.Push(1.3);
    a.Push(1.3);
    a.Push(1.3);
    a.Push(1.3);

    data_t d;
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
    a.Pop(&d);
}
