#include "common.h"

enum TokenType 
{
    ASSIGN, SYMBOL, EOF
};

struct Token
{
    enum TokenType type;
    Symbol symbol;
};