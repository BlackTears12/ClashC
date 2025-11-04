#ifndef PROC_H
#define PROC_H

#include "runtime_val.h"
#include <ast_expr.h>

VECT_GENERATE_STRUCT(runtime_val);

void launch_proc_with_args(char* prog);
void launch_proc_with_args(char* prog, vect_runtime_val* args);

#endif // PROC_H
