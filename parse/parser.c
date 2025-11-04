#include "parser.h"
#include "diagnostics.h"
#include "util.h"

static function_node* parse_fn_decl(parse_context* cxt);

static ast_statement parse_statement(parse_context* cxt);
static ast_statement parse_st_block(parse_context* cxt);
static ast_statement parse_assignment_or_fcall(parse_context* cxt, ast_variable* var);
static ast_statement parse_assignment(parse_context* cxt, ast_variable* lhs);

static ast_expression parse_expression(parse_context* cxt);
static ast_expression parse_literal(parse_context* cxt);
static ast_expression parse_variable(parse_context* cxt);
static ast_expression parse_enclosed_expression(parse_context* cxt);
static ast_expression parse_binary_op(parse_context* cxt, ast_expression lhs);
static ast_expression parse_variable_or_fcall(parse_context* cxt);

static ast_fcall* parse_fcall(parse_context* cxt, ast_variable* var);

static bool is_literal_token(token t);
static bool is_binary_op(token t);

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

void parse_context_consume_if(parse_context* cxt, token_type t)
{
    if (parse_context_peek_token(cxt).type == t) {
        parse_context_next_token(cxt);
    }
}

function_node* parse_file(FILE* file)
{
    parse_context cxt = {.file = file, .main_fn = NULL, .tokens = tokenize_file(file)};
    log_msg("Lexing finished");

    while (!token_queue_empty(cxt.tokens)) {
        if (parse_context_peek_token(&cxt).type == TOK_FN) {
            parse_fn_decl(&cxt);
        } else {
            syntax_error("Unexpected token", &cxt);
        }
    }

    log_msg("Parsing finished");
    return cxt.main_fn;
}

void syntax_error(char* msg, parse_context* cxt)
{
    log_msg("Syntax error");
    log_msg("Writing debug info\n");
    log_msg("Remaining tokens:");
    while (!token_queue_empty(cxt->tokens)) {
        print_token(dequeue_token(cxt->tokens));
    }
}

/* Local functions  */

static function_node* parse_fn_decl(parse_context* cxt)
{
    parse_context_assert_next_token(cxt, TOK_FN);
    symbol_ptr id = parse_context_assert_next_token(cxt, TOK_IDENTIFIER).symbol;

    /* parsing function signature */
    function_node* func = function_node_init(id);
    register_function(func);

    if (str_view_equals_cstr(view_symbol(func->id), "main")) {
        cxt->main_fn = func;
    }

    /* parsing params */
    parse_context_assert_next_token(cxt, TOK_L_BRACKET);
    token tok = parse_context_peek_token(cxt);
    while (tok.type != TOK_R_BRACKET) {
        token param = parse_context_assert_next_token(cxt, TOK_IDENTIFIER);
        func_add_param(func, param.symbol);

        parse_context_consume_if(cxt, TOK_COMMA);
        tok = parse_context_peek_token(cxt);
    }
    parse_context_next_token(cxt);

    /* parsing body */
    tok = parse_context_peek_token(cxt);
    switch (tok.type) {
    case TOK_LC_BRACKET:
        func->body = parse_st_block(cxt).value.block;
        break;
    case TOK_ARROW:
        break;
    default:
        syntax_error("Invalid function signature", cxt);
    }
    return func;
}

static ast_statement parse_statement(parse_context* cxt)
{
    token tok = parse_context_next_token(cxt);
    switch (tok.type) {
    case TOK_IDENTIFIER:
        return parse_assignment_or_fcall(cxt, ast_variable_alloc(tok.symbol));
    default:
        syntax_error("Invalid syntax", cxt);
        break;
    }
    exit(1);
}

static ast_statement parse_assignment_or_fcall(parse_context* cxt, ast_variable* var)
{
    if (parse_context_peek_token(cxt).type == TOK_L_BRACKET) {
        ast_statement fcall = {.type = AST_FCALL_ST, .value = parse_fcall(cxt, var)};
        return fcall;
    }
    if (parse_context_peek_token(cxt).type == TOK_EQUALS) {
        return parse_assignment(cxt, var);
    }
    syntax_error("Invalid syntax", cxt);
    exit(1);
}

static ast_fcall* parse_fcall(parse_context* cxt, ast_variable* var)
{
    ast_fcall* fcall = ast_fcall_alloc(var->id);
    ast_variable_destroy(var);
    parse_context_assert_next_token(cxt, TOK_L_BRACKET);
    token tok = parse_context_peek_token(cxt);
    while (tok.type != TOK_R_BRACKET) {
        ast_fcall_add_arg(fcall, parse_expression(cxt));
        parse_context_consume_if(cxt, TOK_COMMA);

        tok = parse_context_peek_token(cxt);
    }
    return fcall;
}

static ast_statement parse_assignment(parse_context* cxt, ast_variable* lhs)
{
    parse_context_assert_next_token(cxt, TOK_EQUALS);
    ast_expression expr = parse_expression(cxt);
    ast_statement assign = {.type = AST_ASSIGNMENT,
                            .value.assignment = ast_assignment_alloc(lhs, expr)};
    return assign;
}

ast_statement parse_st_block(parse_context* cxt)
{
    ast_statement block = {.type = AST_BLOCK, .value.block = ast_st_block_alloc()};
    parse_context_assert_next_token(cxt, TOK_LC_BRACKET);
    token tok = parse_context_peek_token(cxt);
    while (tok.type != TOK_RC_BRACKET) {
        add_st_to_block(block.value.block, parse_statement(cxt));
        tok = parse_context_peek_token(cxt);
    }
    parse_context_next_token(cxt);
    return block;
}

static ast_expression parse_expression(parse_context* cxt)
{
    token next_tok = parse_context_peek_token(cxt);
    ast_expression expr = {.type = AST_LITERAL};

    switch (next_tok.type) {
    case TOK_IDENTIFIER:
        expr = parse_variable_or_fcall(cxt);
        break;
    case TOK_L_BRACKET:
        expr = parse_enclosed_expression(cxt);
        break;
    default:
        if (is_literal_token(next_tok)) {
            expr = parse_literal(cxt);
        } else {
            syntax_error("Unrecognized expression", cxt);
        }
    }

    next_tok = parse_context_peek_token(cxt);
    if (is_binary_op(next_tok)) {
        return parse_binary_op(cxt, expr);
    }
    return expr;
}

static ast_expression parse_literal(parse_context* cxt)
{
    token tok = parse_context_next_token(cxt);
    ast_expression lit = {.type = AST_LITERAL,
                          .value.literal = ast_literal_alloc((ast_literal_type) tok.type,
                                                             tok.symbol)};
    return lit;
}

static ast_expression parse_variable(parse_context* cxt)
{
    ast_expression var = {.type = AST_VARIABLE,
                          .value.variable = ast_variable_alloc(parse_context_next_token(cxt)
                                                                   .symbol)};
    return var;
}

static ast_expression parse_enclosed_expression(parse_context* cxt)
{
    if (parse_context_peek_token(cxt).type == TOK_R_BRACKET) {
        syntax_error("empty parentheses", cxt);
    }
    ast_expression exp = parse_expression(cxt);
    parse_context_assert_next_token(cxt, TOK_R_BRACKET);
    ast_expression enclosed = {.type = AST_ENCLOSED,
                               .value.enclosed_expr = ast_enclosed_expr_alloc(exp)};

    return enclosed;
}

static ast_expression parse_binary_op(parse_context* cxt, ast_expression lhs)
{
    token bop_type = parse_context_next_token(cxt);
    ast_expression rhs = parse_expression(cxt);
    ast_expression bop = {.type = AST_BINARYOP,
                          .value.binary_op = ast_binary_op_alloc((ast_binary_op_type) bop_type.type,
                                                                 lhs,
                                                                 rhs)};
    return bop;
}

static ast_expression parse_variable_or_fcall(parse_context* cxt)
{
    ast_expression var = parse_variable(cxt);
    if (parse_context_peek_token(cxt).type == TOK_L_BRACKET) {
        ast_expression fcall = {.type = AST_FCALL, .value = parse_fcall(cxt, var.value.variable)};
        return fcall;
    }
    return var;
}

GENERATE_UTIL_FUNCTIONS(ast_literal_type)

static bool is_literal_token(token t)
{
    ast_literal_type allowed_tok_t[AST_LITERAL_TYPE_AMOUNT] = {LITERAL_TYPE_INT,
                                                               LITERAL_TYPE_FLOAT,
                                                               LITERAL_TYPE_BOOL,
                                                               LITERAL_TYPE_STR};
    return in_array_ast_literal_type((ast_literal_type) t.type,
                                     allowed_tok_t,
                                     AST_LITERAL_TYPE_AMOUNT);
}

GENERATE_UTIL_FUNCTIONS(ast_binary_op_type)

static bool is_binary_op(token t)
{
    ast_binary_op_type allowed_tok_t[AST_BINARY_OP_TYPE_AMOUNT] = {BOP_ADD,
                                                                   BOP_SUB,
                                                                   BOP_MULT,
                                                                   BOP_DIV};
    return in_array_ast_binary_op_type((ast_binary_op_type) t.type,
                                       allowed_tok_t,
                                       AST_BINARY_OP_TYPE_AMOUNT);
}
