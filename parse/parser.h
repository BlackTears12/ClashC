#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "function.h"
#include "lexer.h"

typedef struct parse_context
{
    FILE* file;
    token_queue* tokens;
    function_node* main_fn;
} parse_context;

token parse_context_next_token(parse_context* cxt);
token parse_context_peek_token(parse_context* cxt);
token parse_context_assert_next_token(parse_context* cxt, token_type t);
void parse_context_consume_if(parse_context* cxt, token_type t);

function_node* parse_file(FILE* file);

void syntax_error(char* msg, parse_context* cxt);

#endif // PARSER_H
