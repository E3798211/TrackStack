#include "../Head/Stack.h"

Stack::Stack():
    _first_canary   (CANARY),
    _capacity       (0),
    _n_elements     (0),
    _last_canary    (CANARY)
{
    // fopen("abx", "a");
    // Create logfile, init it. Name - pointer
    // Allocate memory
    // Count hash (should be places in SAFE zone)
}
