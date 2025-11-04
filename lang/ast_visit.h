#ifndef AST_VISIT_H
#define AST_VISIT_H

#include "ast_expr.h"
#include "ast_stmt.h"
#include "function.h"
#include "runtime_val.h"

#define TYPEDEF_VISITOR_FN(ast_node) \
    typedef ast_visit_result (*ast_node##_visitor)(ast_node *, struct ast_visit_context *);

typedef union ast_visit_result {
    runtime_val rt_val;
} ast_visit_result;

typedef struct ast_visit_context
{
    struct ast_visitor_fns *visitors;
    ast_visit_result (*visit_expr)(ast_expression, struct ast_visit_context *);
    ast_visit_result (*visit_stmt)(ast_statement, struct ast_visit_context *);
    bool visit_ended;
} ast_visit_context;

void end_ast_visit(ast_visit_context *cxt);

TYPEDEF_VISITOR_FN(ast_literal)
TYPEDEF_VISITOR_FN(ast_variable)
TYPEDEF_VISITOR_FN(ast_binary_op)
TYPEDEF_VISITOR_FN(ast_command)
TYPEDEF_VISITOR_FN(ast_fcall)
TYPEDEF_VISITOR_FN(ast_assignment);
TYPEDEF_VISITOR_FN(ast_st_block);

typedef struct ast_visitor_fns
{
    ast_literal_visitor literal;
    ast_variable_visitor variable;
    ast_binary_op_visitor binary_op;
    ast_command_visitor command;
    ast_fcall_visitor fcall;
    ast_assignment_visitor assignment;
    ast_st_block_visitor block;
} ast_visitor_fns;

ast_visit_context new_visit_context(ast_visitor_fns *visitors);
ast_visit_result dispatch_expr_visitor(ast_expression expr, ast_visit_context *cxt);
ast_visit_result dispatch_stmt_visitor(ast_statement stmt, ast_visit_context *cxt);

#endif // AST_VISIT_H
