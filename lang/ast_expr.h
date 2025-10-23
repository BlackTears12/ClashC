#ifndef AST_EXPR_H
#define AST_EXPR_H

#include "str.h"
#include "symbol.h"
#include "vector.h"

typedef enum ast_expr_type {
    AST_FCALL = 0,
    AST_COMMAND = 1,
    AST_LITERAL,
    AST_VARIABLE,
    AST_BINARYOP,
    AST_LIST
} ast_expr_type;

typedef union ast_expr_data {
    struct ast_fcall *fcall;
    struct ast_command *command;
    struct ast_literal *literal;
    struct ast_variable *variable;
    struct ast_binary_op *binary_op;
} ast_expr_data;

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
    vect_ast_expression *args;
} ast_fcall;

ast_fcall *ast_fcall_alloc();
void ast_fcall_destroy(ast_fcall *fcall);

typedef struct ast_command
{
    vect_ast_expression args;
} ast_command;

ast_command *ast_command_alloc();
void ast_command_destroy(ast_command *cmd);

typedef struct ast_literal
{
    str_view value;
} ast_literal;

ast_literal *ast_literal_alloc(str_view val);
void ast_literal_destroy(ast_literal *lit);

typedef struct ast_variable
{
    symbol_ptr id;
} ast_variable;

ast_variable *ast_variable_alloc(symbol_ptr sym);
void ast_variable_destroy(ast_variable *var);

typedef struct ast_binary_op
{
    ast_expression lhs;
    ast_expression rhs;
} ast_binary_op;

ast_binary_op *ast_binary_op_alloc(ast_expression lhs, ast_expression rhs);
void ast_binary_op_destroy(ast_binary_op *lit);

#endif
