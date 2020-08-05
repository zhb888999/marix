#include "matrix.h"
#include <stdio.h>

int main() {
    array *test2 = arange_int64(0, 16, 1);
    areshape(test2, acshape(2, 4, 4));
    aprint(test2);
    array *sli = aslice(test2, 0, 2, 0, 2);
    aprint(sli);
    //printf("%lu\n", aindex(sli, 2, 3));
    afree(test2);
}
