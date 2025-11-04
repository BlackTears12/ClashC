#include "diagnostics.h"

#include <stdio.h>
#include <stdlib.h>

int lexical_error(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

int fatal_error(char *msg)
{
    printf("FATAL %s\n", msg);
    exit(1);
}

void log_msg(char *msg)
{
    printf("%s\n", msg);
    fflush(stdout);
}

void clash_assert_fatal(bool b)
{
    if (!b) {
        fatal_error("");
    }
}
