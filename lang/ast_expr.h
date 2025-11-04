#ifndef AST_EXPR_H
#define AST_EXPR_H

#include "str.h"
#include "symbol.h"
#include "token.h"
#include "vector.h"

#define DEFAULT_ARGUMENT_CAPACITY 5

typedef enum ast_expr_type {
    AST_FCALL = 0,
    AST_COMMAND = 1,
    AST_LITERAL,
    AST_VARIABLE,
    AST_BINARYOP,
    AST_LIST,
    AST_ENCLOSED,
} ast_expr_type;

typedef union ast_expr_data {
    struct ast_fcall *fcall;
    struct ast_command *command;
    struct ast_literal *literal;
    struct ast_variable *variable;
    struct ast_binary_op *binary_op;
    struct ast_enclosed_expr *enclosed_expr;
} ast_expr_data;

/* Generic expression */
typedef struct ast_expression
{
    ast_expr_type type;
    ast_expr_data value;
} ast_expression;

void ast_expression_destroy(ast_expression expr);

VECT_GENERATE_STRUCT(ast_expression)

/* AST Expression Nodes */

typedef struct ast_fcall
{
    symbol_ptr id;
    vect_ast_expression *args;
} ast_fcall;

ast_fcall *ast_fcall_alloc(symbol_ptr id);
void ast_fcall_destroy(ast_fcall *fcall);
void ast_fcall_add_arg(ast_fcall *fcall, ast_expression arg);

typedef struct ast_command
{
    symbol_ptr cmd;
    vect_ast_expression *args;
} ast_command;

ast_command *ast_command_alloc(symbol_ptr cmd);
void ast_command_destroy(ast_command *cmd);
void ast_command_add_arg(ast_command *cmd, ast_expression arg);

#define AST_LITERAL_TYPE_AMOUNT 4

typedef enum ast_literal_type {
    LITERAL_TYPE_INT = TOK_INTEGER,
    LITERAL_TYPE_STR = TOK_STR_LITERAL,
    LITERAL_TYPE_FLOAT = TOK_FLOATING,
    LITERAL_TYPE_BOOL = TOK_BOOL
} ast_literal_type;

typedef struct ast_literal
{
    ast_literal_type type;
    symbol_ptr value;
} ast_literal;

ast_literal *ast_literal_alloc(ast_literal_type type, symbol_ptr val);
void ast_literal_destroy(ast_literal *lit);

typedef struct ast_variable
{
    bool env;
    symbol_ptr id;
} ast_variable;

ast_variable *ast_variable_alloc(symbol_ptr sym);
void ast_variable_destroy(ast_variable *var);

#define AST_BINARY_OP_TYPE_AMOUNT 4

typedef enum ast_binary_op_type {
    BOP_ADD = TOK_PLUS,
    BOP_SUB = TOK_MINUS,
    BOP_MULT = TOK_MULTIPLY,
    BOP_DIV = TOK_DIVIDE

} ast_binary_op_type;

typedef struct ast_binary_op
{
    ast_binary_op_type type;
    ast_expression lhs;
    ast_expression rhs;
} ast_binary_op;

ast_binary_op *ast_binary_op_alloc(ast_binary_op_type type, ast_expression lhs, ast_expression rhs);
void ast_binary_op_destroy(ast_binary_op *op);

/* Represents an expression enclosed in a bracket
 * by design the parser should not output this ast node
 * its only for convenience
 */
typedef struct ast_enclosed_expr
{
    ast_expression inner;
} ast_enclosed_expr;

ast_enclosed_expr *ast_enclosed_expr_alloc(ast_expression expr);
void ast_enclosed_expr_destroy(ast_enclosed_expr *expr);

#endif
