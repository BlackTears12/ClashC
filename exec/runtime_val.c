#include "runtime_val.h"

static runtime_val runtime_val_from(runtime_val_type t, runtime_val_data d);

runtime_val runtime_val_int(int val)
{
    return runtime_val_from(RUNTIME_INT, (runtime_val_data) val);
}

runtime_val runtime_val_float(double val)
{
    return runtime_val_from(RUNTIME_FLOAT, (runtime_val_data) val);
}

runtime_val runtime_val_bool(bool val)
{
    return runtime_val_from(RUNTIME_BOOL, (runtime_val_data) val);
}

runtime_val runtime_val_str(string_t val)
{
    return runtime_val_from(RUNTIME_STR, (runtime_val_data) val);
}

runtime_val runtime_val_result_ok()
{
    return runtime_val_from(RUNTIME_RESULT, (runtime_val_data) RUNTIME_OK);
}

runtime_val runtime_val_result_err()
{
    return runtime_val_from(RUNTIME_RESULT, (runtime_val_data) RUNTIME_ERR);
}

static runtime_val runtime_val_from(runtime_val_type t, runtime_val_data d)
{
    runtime_val v = {.type = t, .value = d};
    return v;
}

runtime_val convert_runtime_val(runtime_val val, runtime_val_type t) {}
