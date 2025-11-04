#include "exec_engine.h"

int main()
{
    FILE* f = fopen("script.csh", "r");
    execute_script(f);
}
