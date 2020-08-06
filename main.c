#include "matrix.h"
#include <stdio.h>

int main() {
    array *test2 = arange_int64(0, 1000, 1);
    areshape(test2, acshape(3, 10, 10, -1));
    aprint(test2);
    array *sli = aslice(test2, 2, 5, 3, 6, 4, 7);
    aprint(sli);
    printf("%d %d\n", *sli->slice->start, *sli->slice->end);
    printf("%d %d\n", *(sli->slice->start + 1), *(sli->slice->end + 1));
    printf("%d %d\n", *(sli->slice->start + 2), *(sli->slice->end + 2));
    afree(test2);
    //ashape *shape = acshape(3, 10, 10, -1);
    //printf("%d\n", *shape->step);
}
