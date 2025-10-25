#include "ast_stmt.h"
#include "util.h"

VECT_GENERATE_TYPE(ast_statement)

ast_st_block *ast_st_block_alloc()
{
    ast_st_block *bl = STRUCT_ALLOC(ast_st_block);
    bl->content = vect_init_ast_statement(5);
    return bl;
}

void ast_st_block_destroy(ast_st_block *block)
{
    vect_free(block->content);
    free(block);
}

void add_st_to_block(ast_st_block *block, ast_statement st)
{
    vect_push_ast_statement(block->content, st);
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
