#include "function.h"
#include "diagnostics.h"
#include "util.h"

VECT_GENERATE_TYPE(symbol_ptr)

function_node* function_node_init(symbol_ptr id)
{
    function_node* func = STRUCT_ALLOC(function_node);
    func->id = id;
    func->params = vect_init_symbol_ptr(DEFAULT_ARGUMENT_CAPACITY);
    func->body = ast_st_block_alloc();
    return func;
}

void function_node_destroy(function_node* func)
{
    vect_free(func->params);
    ast_st_block_destroy(func->body);
    free(func);
}

void func_add_param(function_node* func, symbol_ptr param) {}

typedef struct function_map_entry
{
    symbol_ptr id;
    function_node* func;
} function_map_entry;

#define INITIAL_FUNCTION_MAP_SIZE 32

typedef struct function_map
{
    function_map_entry* entries;
    size_t size;
    size_t max_size;
} function_map;

static function_map function_map_instance = {NULL, 0, 0};

void functions_init()
{
    function_map_instance.entries = malloc(INITIAL_FUNCTION_MAP_SIZE * sizeof(function_map_entry));
    function_map_instance.max_size = INITIAL_FUNCTION_MAP_SIZE;
};

function_node* get_function(symbol_ptr id)
{
    size_t i = 0;
    while (i < function_map_instance.size && function_map_instance.entries[i].id != id) {
        ++i;
    }
    if (i == function_map_instance.size)
        return NULL;
    return function_map_instance.entries[i].func;
}

void register_function(function_node* node)
{
    if (function_map_instance.size == function_map_instance.max_size) {
        function_map_instance.entries = realloc(function_map_instance.entries,
                                                function_map_instance.max_size * 2);
        function_map_instance.max_size *= 2;

        if (function_map_instance.entries == NULL) {
            fatal_error("cannot reallocate function map");
        }
    }
    function_map_entry* entry = &function_map_instance.entries[function_map_instance.size];
    entry->id = node->id;
    entry->func = node;
}
