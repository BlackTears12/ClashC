#include "ast_visit.h"

ast_visit_context new_visit_context(ast_visitor_fns *visitors)
{
    ast_visit_context cxt = {.visitors = visitors,
                             .visit_expr = dispatch_expr_visitor,
                             .visit_stmt = dispatch_stmt_visitor,
                             .visit_ended = false};
    return cxt;
}

ast_visit_result dispatch_expr_visitor(ast_expression expr, ast_visit_context *cxt)
{
    ast_visitor_fns *visitors = cxt->visitors;
    switch (expr.type) {
    case AST_LITERAL:
        return visitors->literal(expr.value.literal, cxt);
    case AST_VARIABLE:
        return visitors->variable(expr.value.variable, cxt);
    case AST_BINARYOP:
        return visitors->binary_op(expr.value.binary_op, cxt);
    case AST_COMMAND:
        return visitors->command(expr.value.command, cxt);
    case AST_PIPE:
        return visitors->pipe(expr.value.pipe, cxt);
    case AST_FCALL:
        return visitors->fcall(expr.value.fcall, cxt);
    case AST_LIST:
    case AST_ENCLOSED:
    default:
        break;
    }
}

ast_visit_result dispatch_stmt_visitor(ast_statement stmt, ast_visit_context *cxt)
{
    ast_visitor_fns *visitors = cxt->visitors;
    switch (stmt.type) {
    case AST_ASSIGNMENT:
        return visitors->assignment(stmt.value.assignment, cxt);
    case AST_COMMAND_ST:
        return visitors->command(stmt.value.command, cxt);
    case AST_PIPE_ST:
        return visitors->pipe(stmt.value.pipe, cxt);
    case AST_FCALL_ST:
        return visitors->fcall(stmt.value.fcall, cxt);
    case AST_BLOCK:
        return visitors->block(stmt.value.block, cxt);
    default:
        break;
    }
}

void end_ast_visit(ast_visit_context *cxt)
{
    cxt->visit_ended = true;
}
