#include "proc.h"
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

static string_t get_cmd_binary();

void launch_proc(ast_command* cmd)
{
    pid_t pid = fork();
    if (pid == -1) {
        //ERROR
    }
    if (pid == 0) {
        execve(cmd.str, );
    } else {
        int status;
        wait(&status);
    }
}
