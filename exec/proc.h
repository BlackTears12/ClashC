#ifndef PROC_H
#define PROC_H

#include "ast_expr.h"
#include "runtime_val.h"
#include <unistd.h>

typedef struct pipe_redirect_fd
{
    int stdin;
    int stdout;
} pipe_redirect_fd;

static pipe_redirect_fd PIPE_FD_NO_REDIRECT = {STDIN_FILENO, STDOUT_FILENO};

VECT_GENERATE_STRUCT(runtime_val);

typedef struct process_descr
{
    char* program;
    bool background;
    vect_runtime_val* args;
    pipe_redirect_fd redirect_fd;
} process_descr;

void launch_proc(process_descr proc);

#endif // PROC_H
