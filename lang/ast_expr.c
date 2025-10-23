#include "ast_expr.h"
#include "alloc.h"

VECT_GENERATE_TYPE(ast_expression)

ast_fcall *ast_fcall_alloc()
{
    ast_fcall *fcall = STRUCT_ALLOC(ast_fcall);
    fcall->args = vect_init_ast_expression(5);
    return fcall;
}

void ast_fcall_destroy(ast_fcall *fcall) {}

ast_command *ast_command_alloc() {}

void ast_command_destroy(ast_command *cmd) {}

ast_literal *ast_literal_alloc(str_view val) {}

void ast_literal_destroy(ast_literal *lit) {}

ast_variable *ast_variable_alloc(symbol_ptr sym) {}

void ast_variable_destroy(ast_variable *var) {}

ast_binary_op *ast_binary_op_alloc(ast_expression lhs, ast_expression rhs) {}

void ast_binary_op_destroy(ast_binary_op *lit) {}

void ast_expression_destroy(ast_expression expr) {}
