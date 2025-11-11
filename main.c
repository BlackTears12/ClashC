#include "exec_engine.h"
#include "proc.h"

int main()
{
    process_descr proc = {.program = "/bin/ls",
                          .background = false,
                          .redirect_fd = PIPE_FD_NO_REDIRECT,
                          .args = NULL};
    launch_proc(proc);
    //FILE* f = fopen("script.csh", "r");
    //execute_script(f);
}
