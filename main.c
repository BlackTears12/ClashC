#include "lexer.h"
#include "parser.h"

int main()
{
    FILE* f = fopen("script.csh", "r");
    parse_file(f);
}
