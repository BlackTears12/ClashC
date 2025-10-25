#include "diagnostics.h"

#include <stdio.h>
#include <stdlib.h>

void lexical_error(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

void fatal_error(char *msg)
{
    printf("FATAL %s\n", msg);
    exit(1);
}

void log_msg(char *msg)
{
    printf("%s\n", msg);
    fflush(stdout);
}
