#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <stdbool.h>
int fatal_error(char* msg);

int lexical_error(char* msg);

void log_msg(char* msg);

void clash_assert_fatal(bool b);

#define CLASH_ASSERT(b) clash_assert_fatal(b)

#endif // DIAGNOSTICS_H
