#ifndef RUNTIME_VAL_H
#define RUNTIME_VAL_H

#include <stdbool.h>
#include <stdint.h>
#include <str.h>

enum runtime_result { RUNTIME_OK, RUNTIME_ERR };

typedef int32_t runtime_int;
typedef double runtime_float;
typedef bool runtime_bool;
typedef string_t runtime_str;
typedef enum runtime_result runtime_result;

typedef union runtime_val_data {
    runtime_int int_val;
    runtime_float float_val;
    runtime_bool bool_val;
    runtime_str str_val;
    runtime_result result;
} runtime_val_data;

typedef enum runtime_val_type {
    RUNTIME_INT,
    RUNTIME_FLOAT,
    RUNTIME_BOOL,
    RUNTIME_STR,
    RUNTIME_RESULT
} runtime_val_type;

typedef struct runtime_val
{
    runtime_val_type type;
    runtime_val_data value;
} runtime_val;

runtime_val runtime_val_int(int val);
runtime_val runtime_val_float(double val);
runtime_val runtime_val_bool(bool val);
runtime_val runtime_val_str(string_t val);
runtime_val runtime_val_result_ok();
runtime_val runtime_val_result_err();

runtime_val convert_runtime_val(runtime_val val, runtime_val_type t);

#endif // RUNTIME_VAL_H
