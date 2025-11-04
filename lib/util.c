#include "util.h"

int pow_of_ten(size_t pw)
{
    int out = 1;
    for (int i = 0; i < pw; i++) {
        out *= 10;
    }
    return out;
}

int char_to_int(char c)
{
    return c - '0';
}

int sign(int i)
{
    return (i >= 0) - (i < 0);
}
