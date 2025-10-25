#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

#define STRUCT_ALLOC(strct) malloc(sizeof(strct))

#define IMPL_IN_ARRAY(TYPE) \
    bool in_array_##TYPE(TYPE val, TYPE* arr, size_t arr_len) \
    { \
        size_t i = 0; \
        while (i < arr_len && arr[i] != val) { \
            ++i; \
        } \
        return i < arr_len; \
    }

#define GENERATE_UTIL_FUNCTIONS(TYPE) IMPL_IN_ARRAY(TYPE)

#define FOR_EACH_LEN(idx, list, len) for (int idx = 0; idx < view.len; idx++)

#define FOR_EACH(idx, view) FOR_EACH_LEN(idx, view, len)

#endif // UTIL_H
