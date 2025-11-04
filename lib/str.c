#include "str.h"
#include "diagnostics.h"
#include "string.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

bool str_view_equals_cstr(str_view view, char *str)
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

int str_view_to_int(str_view v)
{
    int out = 0;
    int beg = v.str[0] == '-';
    for (int i = v.len - 1; i >= beg; i--) {
        out += pow_of_ten(v.len - i - 1) * char_to_int(v.str[i]);
    }
    if (v.str[0] == '-')
        return out * -1;
    return out;
}

double str_view_to_float(str_view v)
{
    int dot_i = 0;
    while (dot_i < v.len && v.str[dot_i] != '.') {
        ++dot_i;
    }
    str_view temp_str;
    temp_str.str = v.str;
    temp_str.len = dot_i;
    int int_comp = str_view_to_int(temp_str);
    temp_str.str += dot_i + 1;
    temp_str.len = v.len - dot_i - 1;
    int sign = v.str[0] == '-' ? -1 : 1;
    int fraq_comp = str_view_to_int(temp_str) * sign;
    double out = int_comp + (double) fraq_comp / pow_of_ten(temp_str.len);
    return out;
}

bool str_view_to_bool(str_view v)
{
    if (str_view_equals_cstr(v, "true"))
        return true;
    if (str_view_equals_cstr(v, "false"))
        return false;
    return fatal_error("Cannot convert to bool");
}

string_t str_new(char *str)
{
    size_t len = strlen(str);
    string_t s = {.str = (char *) malloc(len + 1), .len = len};
    memcpy(s.str, str, len);
    s.str[len] = '\0';
    return s;
}

void str_delete(string_t str)
{
    free(str.str);
}

string_t str_concat(string_t pre, string_t post) {}
