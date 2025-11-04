#ifndef RUNTIME_STORAGE_H
#define RUNTIME_STORAGE_H

#include "runtime_val.h"
#include "symbol.h"

void runtime_storage_init();

runtime_val get_runtime_value(symbol_ptr s);
void set_runtime_value(symbol_ptr s, runtime_val v);
void push_runtime_value(symbol_ptr s, runtime_val v);

void push_runtime_scope();
void pop_runtime_scope();

#endif // RUNTIME_STORAGE_H
