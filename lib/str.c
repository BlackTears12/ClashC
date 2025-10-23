#include "str.h"
#include "string.h"

#include <stdio.h>

bool str_view_equals_str(str_view view, char *str)
{
    if (strlen(str) != view.len)
        return false;
    size_t idx = 0;
    while (idx < view.len && str[idx] == view.str[idx]) {
        ++idx;
    }
    return idx == view.len;
}

str_view view_str(char *str, size_t start, size_t end)
{
    str_view view;
    view.str = str + start;
    view.len = end - start;
    return view;
}

void print_view(str_view view)
{
    char buff[128];
    memcpy(buff, view.str, view.len);
    buff[view.len] = '\0';
    printf("%s\n", buff);
}

bool str_view_equals_view(str_view view, str_view other)
{
    if (view.len != other.len)
        return false;
    for (int i = 0; i < view.len; i++) {
        if (view.str[i] != other.str[i]) {
            return false;
        }
    }
    return true;
}
