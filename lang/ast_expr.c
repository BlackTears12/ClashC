#include "ast_expr.h"
#include "util.h"

VECT_GENERATE_TYPE(ast_expression)

void ast_expression_destroy(ast_expression expr) {}

ast_fcall *ast_fcall_alloc(symbol_ptr id)
{
    ast_fcall *fcall = STRUCT_ALLOC(ast_fcall);
    fcall->id = id;
    fcall->args = vect_init_ast_expression(DEFAULT_ARGUMENT_CAPACITY);
    return fcall;
}

void ast_fcall_destroy(ast_fcall *fcall)
{
    vect_free(fcall->args);
    free(fcall);
}

void ast_fcall_add_arg(ast_fcall *fcall, ast_expression arg)
{
    vect_push_ast_expression(fcall->args, arg);
}

ast_command *ast_command_alloc(symbol_ptr cmd)
{
    ast_command *ast_cmd = STRUCT_ALLOC(ast_command);
    ast_cmd->cmd = cmd;
    ast_cmd->args = vect_init_ast_expression(DEFAULT_ARGUMENT_CAPACITY);
    return ast_cmd;
}

void ast_command_destroy(ast_command *cmd)
{
    vect_free(cmd->args);
    free(cmd);
}

void ast_command_add_arg(ast_command *cmd, ast_expression arg)
{
    vect_push_ast_expression(cmd->args, arg);
}

ast_literal *ast_literal_alloc(ast_literal_type type, symbol_ptr val)
{
    ast_literal *lit = STRUCT_ALLOC(ast_literal);
    lit->type = type;
    lit->value = val;
    return lit;
}

void ast_literal_destroy(ast_literal *lit)
{
    free(lit);
}

ast_variable *ast_variable_alloc(symbol_ptr sym)
{
    ast_variable *var = STRUCT_ALLOC(ast_variable);
    var->id = sym;
    var->env = view_symbol(sym).str[0] == '$';
    return var;
}

void ast_variable_destroy(ast_variable *var)
{
    free(var);
}

ast_binary_op *ast_binary_op_alloc(ast_binary_op_type type, ast_expression lhs, ast_expression rhs)
{
    ast_binary_op *bop = STRUCT_ALLOC(ast_binary_op);
    bop->type = type;
    bop->lhs = lhs;
    bop->rhs = rhs;
    return bop;
}

void ast_binary_op_destroy(ast_binary_op *op)
{
    ast_expression_destroy(op->lhs);
    ast_expression_destroy(op->rhs);
    free(op);
}

ast_enclosed_expr *ast_enclosed_expr_alloc(ast_expression expr)
{
    ast_enclosed_expr *enclosed = STRUCT_ALLOC(ast_enclosed_expr);
    enclosed->inner = expr;
    return enclosed;
}

void ast_enclosed_expr_destroy(ast_enclosed_expr *expr)
{
    free(expr);
}
