#ifndef AST_STMENT_H
#define AST_STMENT_H

#include "ast_expr.h"
#include "symbol.h"

typedef enum ast_statement_type {
    AST_FCALL_ST = AST_FCALL,
    AST_COMMAND_ST = AST_COMMAND,
    AST_ASSIGNMENT,
    AST_BLOCK
} ast_statement_type;

typedef union ast_statement_data {
    struct ast_fcall *fcall;
    struct ast_command *command;
    struct ast_assignment *assignment;
    struct ast_st_block *ast_statement_block;
} ast_statement_data;

typedef struct ast_statement
{
    ast_statement_type type;
    ast_statement_data value;
} ast_statement;

VECT_GENERATE_STRUCT(ast_statement)

typedef struct ast_statement_block
{
    vect_ast_statement *block;
} ast_statement_block;

ast_statement_block *ast_statement_block_alloc();
void ast_statement_block_destroy(ast_statement_block *block);

typedef struct ast_assignment
{
    ast_variable *var;
    ast_expression expr;
} ast_assignment;

ast_assignment *ast_assignment_alloc(ast_variable *lhs, ast_expression rhs);
void ast_assignment_destroy(ast_assignment *assign);

#endif // AST_STMENT_H
