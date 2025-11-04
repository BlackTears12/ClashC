#include "proc.h"
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

static char** alloc_arg_buff(vect);

void launch_proc(char* prog)
{
    pid_t pid = fork();
    if (pid == -1) {
        //ERROR
    }
    if (pid == 0) {
        char* args[1] = {prog};
        execve(prog, args, NULL);
    } else {
        int status;
        wait(&status);
    }
}

void launch_proc_with_args(char* prog, vect_runtime_val* args) {}
