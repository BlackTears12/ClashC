#include "diagnostics.h"

#include <stdio.h>
#include <stdlib.h>

void lexical_error(char *msg)
{
    printf("%s", msg);
    exit(1);
}

void fatal_error(char *msg) {}

void syntax_error(char *msg)
{
    lexical_error(msg);
}
