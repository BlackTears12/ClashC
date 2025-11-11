#include "proc.h"
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

VECT_GENERATE_FN_DECL(runtime_val)

static int exec_program(char* prog, vect_runtime_val* args);

static int exec_program(char* prog, vect_runtime_val* args)
{
    if (args != NULL && args->size > 0) {
        char** argv = malloc(sizeof(char*) * args->size + 1);
        for (int i = 0; i < args->size; i++) {
            argv[i] = rt_val_to_str(vect_at_runtime_val(args, i)).str;
        }
        argv[args->size] = NULL;
        int result = execve(prog, argv, NULL);
        free(argv);
        return result;
    } else {
        char* argv[2] = {prog, NULL};
        return execve(prog, argv, NULL);
    }
}

void launch_proc(process_descr proc)
{
    pid_t pid = fork();
    if (pid == -1) {
        //ERROR
    }
    if (pid == 0) {
        //TODO error checking
        dup2(STDIN_FILENO, proc.redirect_fd.stdin);
        dup2(STDOUT_FILENO, proc.redirect_fd.stdout);
        exec_program(proc.program, proc.args);
    } else if (!proc.background) {
        int status;
        wait(&status);
    }
}
