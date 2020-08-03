#include "matrix.h"
#include <stdio.h>

int main() {
    //array *test1 = aones(acshape(2, 10, 10), int64);
	//ashape *shape = test1->shape;
    //aprint(test1);
    array *test2 = arange(0, 100000000, 1, int64);
    //array *test2 = arange(0, 100, 1, int64);
    //areshape(test2, acshape(2, 10, 10));
    //areshape(test2, acshape(3, 100, 100, -1));
    aprint(test2);
    //afree(test1);
    afree(test2);
}
