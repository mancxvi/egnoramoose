#include <stdio.h>
#include "egnoramoose.h"

int main(int argc, char *argv[])
{
    Eg *eg = eg_make(5, 3, 2);
    eg_print(eg);
    eg_jump(eg, 1, 0, L_RIGHT);
    eg_print(eg);
    eg_destroy(eg);
    return 0;
}
