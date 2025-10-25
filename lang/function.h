#ifndef FUNCTION_H
#define FUNCTION_H

#include "ast.h"
#include "symbol.h"

VECT_GENERATE_STRUCT(symbol_ptr)

typedef struct function_node
{
    symbol_ptr id;
    vect_symbol_ptr* params;
    ast_st_block* body;
} function_node;

function_node* function_node_init(symbol_ptr id);
void function_node_destroy(function_node* func);
void func_add_param(function_node* func, symbol_ptr param);

void functions_init();

function_node* get_function(symbol_ptr id);
void register_function(function_node* node);

#endif
