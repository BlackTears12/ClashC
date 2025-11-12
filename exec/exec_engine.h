#ifndef EXEC_ENGINE_H
#define EXEC_ENGINE_H

#include "ast_visit.h"

ast_visit_result eval_ast_literal(ast_literal* lit, ast_visit_context* cxt);
ast_visit_result eval_ast_variable(ast_variable* var, ast_visit_context* cxt);
ast_visit_result eval_ast_binary_op(ast_binary_op* binary_op, ast_visit_context* cxt);
ast_visit_result eval_ast_command(ast_command* cmd, ast_visit_context* cxt);
ast_visit_result eval_ast_pipe(ast_pipe* pipe, ast_visit_context* cxt);
ast_visit_result eval_ast_fcall(ast_fcall* fcall, ast_visit_context* cxt);
ast_visit_result eval_ast_assignment(ast_assignment* assign, ast_visit_context* cxt);
ast_visit_result eval_ast_st_block(ast_st_block* block, ast_visit_context* cxt);

void execute_script(FILE* f);
void exec_statement(ast_statement st);

#endif // EXEC_ENGINE_H
