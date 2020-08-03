#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>

void ftoa(double num, char *buf)
{
    union u_num{
        double num;
        struct {
            uint64_t mantissa:52;
            unsigned exp: 11;
            unsigned symbol: 1;
        } bits;
    };
    char stack[100];
    union u_num *unum = (union u_num *)&num;
    printf("%lf:%d %d %lu\n", num, unum->bits.symbol, unum->bits.exp, unum->bits.mantissa);
    printf("exp:%f", pow(2, unum->bits.exp - 1023));
    printf("mantissa:%f", pow(2, -unum->bits.mantissa));
}
int main()
{
    char buf[100];
    ftoa(0.2, buf);

    printf("|%f\n", 23.234234/10);
}
