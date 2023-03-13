#ifndef _H_NMACRO
#define _H_NMACRO

#define macro_concat(a, b) a##b
#define macro_var(name) macro_concat(name, __LINE__)

#define scope(start, end) for ( \
        int macro_var(_i_) = (start, 0); \
        !macro_var(_i_); \
        (macro_var(_i_) += 1), end)

#define defer(deferred_statement) for ( \
        int macro_var(_i_) = 0; \
        !macro_var(_i_); \
        (macro_var(_i_) += 1), deferred_statement)

#endif //_H_NMACRO
