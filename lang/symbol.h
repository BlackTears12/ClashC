#ifndef SYMBOL_H
#define SYMBOL_H

#include <stddef.h>
#include <str.h>

typedef size_t symbol_ptr;

void init_symbol_table();
symbol_ptr register_symbol(str_view view);
str_view view_symbol(symbol_ptr sym);

#endif // SYMBOL_H
