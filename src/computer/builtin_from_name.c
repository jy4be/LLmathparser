#include "computer/builtins.h"
#include <string.h>

builtin_funcs_t builtin_from_name(char* name) {
    for(size_t i = 0; i < INBUILT_FUNCS_AMOUNT; i++){
        if (!strcmp(INBUILT_FUNCS[i], name))
            return BUILTINS[i + INBUILT_FUNCTION_OFFSET];
    }
    return NULL;


}
