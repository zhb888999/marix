#include "matrix.h"
#include <stdio.h>

int main() {
    array *test1 = arange_uint8(0, 10, 1);
    array *test2 = arange_int64(0, 10, 1);
	array *test3 = arange_float64(0, 1, 0.1);
    aprint(test1);
    aprint(test2);
    aprint(test3);
    afree(test1);
    afree(test2);
    afree(test3);
	ashape *shape = acshape(5, 2, 3, 4, 5, 6);
	for(int i=0; i < 5; i++)
		printf("%lu ", *(shape->step+i));
}
