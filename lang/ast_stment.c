#include "ast_stment.h"
#include "alloc.h"

VECT_GENERATE_TYPE(ast_statement)

ast_statement_block *ast_statement_block_alloc()
{
    ast_statement_block *bl = STRUCT_ALLOC(ast_statement_block);
    bl->block = vect_init_ast_statement(5);
    return bl;
}

void ast_statement_block_destroy(ast_statement_block *block)
{
    vect_free(block->block);
    free(block);
}

ast_assignment *ast_assignment_alloc(ast_variable *lhs, ast_expression rhs)
{
    ast_assignment *assign = STRUCT_ALLOC(ast_assignment);
    assign->var = lhs;
    assign->expr = rhs;
    return assign;
}

void ast_assignment_destroy(ast_assignment *assign)
{
    ast_variable_destroy(assign->var);
    ast_expression_destroy(assign->expr);
    free(assign);
}
