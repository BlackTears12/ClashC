#include "parser.h"
#include "diagnostics.h"

token parse_context_next_token(parse_context* cxt)
{
    token t = parse_context_peek_token(cxt);
    dequeue_token(cxt->tokens);
    return t;
}

token parse_context_peek_token(parse_context* cxt)
{
    return peek_token(cxt->tokens);
}

token parse_context_assert_next_token(parse_context* cxt, token_type t)
{
    token tok = parse_context_next_token(cxt);
    if (tok.type != t) {
        lexical_error("Unexpected token");
    }
    return tok;
}

static function_node* parse_fn_decl(parse_context* cxt);

static ast_statement parse_statement(parse_context* cxt);
static ast_statement parse_assignment_or_fcall(parse_context* cxt);
static ast_statement parse_fcall(parse_context* cxt);
static ast_statement parse_assignment(parse_context* cxt);
static ast_statement parse_st_block(parse_context* cxt);

static ast_expression parse_expression(parse_context* cxt);
static ast_expression parse_literal(parse_context* cxt);
static ast_expression parse_variable(parse_context* cxt);

static ast_statement parse_statement(parse_context* cxt)
{
    token tok = parse_context_next_token(cxt);
    switch (tok.type) {
    case TOK_IDENTIFIER:
        return parse_assignment_or_fcall(cxt);
    default:
        syntax_error("Invalid syntax");
        break;
    }
    exit(1);
}

static ast_statement parse_assignment_or_fcall(parse_context* cxt)
{
    if (parse_context_peek_token(cxt).type == TOK_L_BRACKET) {
        return parse_fcall(cxt);
    }
    if (parse_context_peek_token(cxt).type == TOK_EQUALS) {
        return parse_assignment(cxt);
    }
    syntax_error("Invalid syntax");
    exit(1);
}

static ast_statement parse_fcall(parse_context* cxt) {}

static ast_statement parse_assignment(parse_context* cxt)
{
    ast_variable* var = ast_variable_alloc(parse_context_next_token(cxt).symbol);
    parse_context_assert_next_token(cxt, TOK_EQUALS);
    ast_expression expr = parse_expression(cxt);
    ast_statement assign = {.type = AST_ASSIGNMENT,
                            .value.assignment = ast_assignment_alloc(var, expr)};
    return assign;
}

static ast_statement parse_st_block(parse_context* cxt) {}

static ast_expression parse_expression(parse_context* cxt) {}

static ast_expression parse_literal(parse_context* cxt) {}

static ast_expression parse_variable(parse_context* cxt) {}
