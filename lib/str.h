#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct str_view
{
    char *str;
    size_t len;
} str_view;

str_view view_str(char *str, size_t start, size_t end);
void print_view(str_view view);

bool str_view_equals_cstr(str_view view, char *str);
bool str_view_equals_view(str_view view, str_view other);

int str_view_to_int(str_view v);
double str_view_to_float(str_view v);
bool str_view_to_bool(str_view v);

typedef str_view string_t;
string_t str_new(char *str);
void str_delete(string_t str);

/* Concats @pre to @post without freeing them*/
string_t str_concat(string_t pre, string_t post);

/* Concats @pre to @post and deallocates them after*/
string_t str_merge(string_t pre, string_t post);

#endif
