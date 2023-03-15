#ifndef AST_BUILTINS_H
#define AST_BUILTINS_H

#include <math.h>

#define INBUILT_FUNCTION_OFFSET sizeof(OPERATOR_CHARS) / sizeof(char)
#define INBUILT_FUNCS_AMOUNT sizeof(INBUILT_FUNCS) / sizeof(char*)

typedef double (*builtin_funcs_t)(double, double);

static inline double bi_add(double a, double b)
    {return a + b;}
static inline double bi_sub(double a, double b)
    {return a - b;}
static inline double bi_mul(double a, double b)
    {return a * b;}
static inline double bi_div(double a, double b)
    {return a / b;}

builtin_funcs_t builtin_from_name(char* name);

static const builtin_funcs_t BUILTINS[] = 
    {&bi_add, &bi_sub, &bi_mul, &bi_div, &pow};

static const char OPERATOR_CHARS[] = {'+', '-', '*', '/'};
static const char* INBUILT_FUNCS[] = {"pow"};

#endif//AST_BUILTINS_H
