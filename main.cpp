#include <iostream>

#include "Src/Stack.hpp"

int main()
{
    Stack <double> a;
    a.Push(1.3);
    a.Push(1.3);
    a.Push(1.3);
    a.Push(1.3);
    a.Push(1.3);
    a.Push(1.3);

    double d = 0;
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
