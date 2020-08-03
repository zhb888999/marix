#include "matrix.h"

int main() {
    array *test1 = aones(acshape(3, 11, 11, 9), int32);
	ashape *shape = test1->shape;
    aprint(test1);
    array *test2 = arange(0, 100000000, 1, int32);
    areshape(test2, acshape(3, 100, 100, -1));
    aprint(test2);
    afree(test1);
    afree(test2);
}
