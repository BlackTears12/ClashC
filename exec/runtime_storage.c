#include "runtime_storage.h"
#include "diagnostics.h"
#include "runtime_val.h"
#include "symbol.h"
#include <stdlib.h>


typedef struct runtime_val_storage_entry
{
    symbol_ptr id;
    runtime_val val;
} runtime_val_storage_entry;

#define MAX_SCOPE_SIZE 32
#define INITIAL_RUNTIME_STORAGE_SIZE 64

typedef struct runtime_val_storage
{
    runtime_val_storage_entry* entries;
    size_t scope_delims[MAX_SCOPE_SIZE];
    size_t scope_size;
    size_t entry_size;
    size_t entry_max_size;
} runtime_val_storage;

static void symbol_not_defined_error(symbol_ptr sym);
static runtime_val_storage_entry* search_symbol_value(symbol_ptr s);

static runtime_val_storage runtime_val_storage_instace
    = {.entries = NULL,
       .scope_size = 0,
       .entry_size = 0,
       .entry_max_size = INITIAL_RUNTIME_STORAGE_SIZE};

void runtime_storage_init()
{
    runtime_val_storage_instace.entries = malloc(INITIAL_RUNTIME_STORAGE_SIZE
                                                 * sizeof(runtime_val_storage_entry));
    runtime_val_storage_instace.entry_max_size = INITIAL_RUNTIME_STORAGE_SIZE;
};

runtime_val get_runtime_value(symbol_ptr s)
{
    runtime_val_storage_entry* val = search_symbol_value(s);
    if (!val) {
        symbol_not_defined_error(s);
    }
    return val->val;
}

void set_runtime_value(symbol_ptr s, runtime_val v)
{
    runtime_val_storage_entry* entry = search_symbol_value(s);
    if (entry) {
        entry->val = v;
    } else {
        push_runtime_value(s, v);
    }
}

void push_runtime_value(symbol_ptr s, runtime_val v)
{
    if (runtime_val_storage_instace.entry_size == runtime_val_storage_instace.entry_max_size) {
        runtime_val_storage_instace.entries = realloc(runtime_val_storage_instace.entries,
                                                      runtime_val_storage_instace.entry_max_size
                                                          * 2);
        runtime_val_storage_instace.entry_max_size *= 2;

        if (runtime_val_storage_instace.entries == NULL) {
            fatal_error("cannot reallocate runtime value storage");
        }
    }
    runtime_val_storage_entry* entry
        = &runtime_val_storage_instace.entries[runtime_val_storage_instace.entry_size];
    entry->id = s;
    entry->val = v;
}

void push_runtime_scope() {}
void pop_runtime_scope() {}

/* Static function definitions */

static void symbol_not_defined_error(symbol_ptr sym)
{
    exit(1);
}

static runtime_val_storage_entry* search_symbol_value(symbol_ptr s)
{
    size_t i = 0;
    while (i < runtime_val_storage_instace.entry_size
           && runtime_val_storage_instace.entries[i].id != s) {
        ++i;
    }
    if (i == runtime_val_storage_instace.entry_size) {
        return NULL;
    }
    return &runtime_val_storage_instace.entries[i];
}
