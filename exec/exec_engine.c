#include "exec_engine.h"
#include "diagnostics.h"
#include "parser.h"
#include "runtime_storage.h"

VECT_GENERATE_STRUCT(runtime_val)
VECT_GENERATE_TYPE(runtime_val)

VECT_GENERATE_FN_DECL(symbol_ptr)
VECT_GENERATE_FN_DECL(ast_expression)

#define RETURN_VISIT_OK return (ast_visit_result) runtime_val_result_ok()

static void init_modules();
static runtime_val exec_fn(function_node* fn);
static runtime_val exec_fn_with_args(function_node* fn,
                                     vect_ast_expression* args,
                                     ast_visit_context* cxt);
static string_t runtime_str_from_parse_str_view(str_view v);

ast_visit_result eval_ast_literal(ast_literal* lit, ast_visit_context* cxt)
{
    str_view v = view_symbol(lit->value);
    switch (lit->type) {
    case LITERAL_TYPE_INT:
        return (ast_visit_result) runtime_val_int(str_view_to_int(v));
    case LITERAL_TYPE_FLOAT:
        return (ast_visit_result) runtime_val_float(str_view_to_float(v));
    case LITERAL_TYPE_BOOL:
        return (ast_visit_result) runtime_val_bool(str_view_to_bool(v));
    case LITERAL_TYPE_STR:
        return (ast_visit_result) runtime_val_str(runtime_str_from_parse_str_view(v));
    }
}

ast_visit_result eval_ast_variable(ast_variable* var, ast_visit_context* cxt)
{
    //TODO ENV VARIABLES
    return (ast_visit_result) get_runtime_value(var->id);
}

ast_visit_result eval_ast_binary_op(ast_binary_op* binary_op, ast_visit_context* cxt) {}
ast_visit_result eval_ast_command(ast_command* cmd, ast_visit_context* cxt) {}

ast_visit_result eval_ast_fcall(ast_fcall* fcall, ast_visit_context* cxt)
{
    return (ast_visit_result) exec_fn_with_args(get_function(fcall->id), fcall->args, cxt);
}

ast_visit_result eval_ast_assignment(ast_assignment* assign, ast_visit_context* cxt)
{
    //TODO ENV VARIABLES
    set_runtime_value(assign->var->id, cxt->visit_expr(assign->expr, cxt).rt_val);
    RETURN_VISIT_OK;
}

ast_visit_result eval_ast_st_block(ast_st_block* block, ast_visit_context* cxt)
{
    push_runtime_scope();
    VECT_FOR_EACH(block->content, i)
    {
        runtime_val val = cxt->visit_stmt(vect_at_ast_statement(block->content, i), cxt).rt_val;
        if (cxt->visit_ended) {
            return (ast_visit_result) val;
        }
    }
    pop_runtime_scope();
    RETURN_VISIT_OK;
}

void execute_script(FILE* f)
{
    init_modules();
    function_node* main = parse_file(f);
    exec_fn(main);
}

/* Static function definitions */

static void init_modules()
{
    functions_init();
    runtime_storage_init();
}

static runtime_val exec_fn(function_node* fn)
{
    ast_visitor_fns visitors = {.literal = eval_ast_literal,
                                .variable = eval_ast_variable,
                                .assignment = eval_ast_assignment,
                                .binary_op = eval_ast_binary_op,
                                .block = eval_ast_st_block,
                                .command = eval_ast_command,
                                .fcall = eval_ast_fcall};

    ast_visit_context cxt = new_visit_context(&visitors);
    ast_visit_result result = eval_ast_st_block(fn->body, &cxt);
    return result.rt_val;
}

static runtime_val exec_fn_with_args(function_node* fn,
                                     vect_ast_expression* args,
                                     ast_visit_context* cxt)
{
    CLASH_ASSERT(fn->params->size == args->size);

    push_runtime_scope();
    VECT_FOR_EACH(args, i)
    {
        symbol_ptr sym = vect_at_symbol_ptr(fn->params, i);
        ast_expression expr = vect_at_ast_expression(args, i);
        push_runtime_value(sym, cxt->visit_expr(expr, cxt).rt_val);
    }
    runtime_val ret = exec_fn(fn);
    pop_runtime_scope();
    return ret;
}

static string_t runtime_str_from_parse_str_view(str_view v) {}
