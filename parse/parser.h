#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "function.h"
#include "lexer.h"

typedef struct parse_context
{
    function_node* func;
    FILE* file;
    token_queue* tokens;
} parse_context;

token parse_context_next_token(parse_context* cxt);
token parse_context_peek_token(parse_context* cxt);
token parse_context_assert_next_token(parse_context* cxt, token_type t);

void parse_file(FILE* file);

#endif // PARSER_H
