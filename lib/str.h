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

bool str_view_equals_str(str_view view, char *str);
bool str_view_equals_view(str_view view, str_view other);

#endif
