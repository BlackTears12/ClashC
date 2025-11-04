#include "symbol.h"
#include "diagnostics.h"
#include <malloc.h>
#include <str.h>
#include <string.h>

#define MAX_SYMBOL_LEN 64
#define DEFAULT_SYMBOL_TABLE_SIZE 64

typedef struct symbol
{
    char str[MAX_SYMBOL_LEN];
    size_t len;
} symbol;

static void symbol_from_str_view(symbol *sym, str_view view)
{
    memcpy(sym->str, view.str, view.len);
    sym->len = view.len;
    sym->str[sym->len] = '\0';
}

typedef struct symbol_table
{
    symbol *data;
    size_t len;
    size_t max_len;
} symbol_table;

static symbol_table symbol_table_instance = {NULL, 0, 0};

void symbol_table_init()
{
    symbol_table_instance.len = 0;
    symbol_table_instance.max_len = DEFAULT_SYMBOL_TABLE_SIZE;
    symbol_table_instance.data = malloc(sizeof(symbol) * DEFAULT_SYMBOL_TABLE_SIZE);
    if (!symbol_table_instance.data)
        fatal_error("cannot allocate symbol table");
}

symbol_ptr register_symbol(str_view view)
{
    for (symbol_ptr i = 0; i < symbol_table_instance.len; i++) {
        if (str_view_equals_cstr(view, symbol_table_instance.data[i].str)) {
            return i;
        }
    }

    if (symbol_table_instance.len == symbol_table_instance.max_len) {
        symbol_table_instance.max_len *= 2;
        symbol_table_instance.data = realloc(symbol_table_instance.data,
                                             symbol_table_instance.max_len);
        if (!symbol_table_instance.data)
            fatal_error("cannot allocate symbol table");
    }
    symbol_from_str_view(&symbol_table_instance.data[symbol_table_instance.len++], view);
    return (symbol_ptr) symbol_table_instance.len - 1;
}

str_view view_symbol(symbol_ptr sym)
{
    symbol *symbol = &symbol_table_instance.data[sym];
    return view_str(symbol->str, 0, symbol->len);
}

char *str_symbol(symbol_ptr sym)
{
    return symbol_table_instance.data[sym].str;
}
