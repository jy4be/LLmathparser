#ifndef AST_BUILTINS_H
#define AST_BUILTINS_H

static inline double bi_add(double a, double b)
    {return a + b;}
static inline double bi_sub(double a, double b)
    {return a - b;}
static inline double bi_mul(double a, double b)
    {return a * b;}
static inline double bi_div(double a, double b)
    {return a / b;}

double bi_pow(double base, double exp);


typedef double (*builtin_infix_funcs_t)(double, double);

static const builtin_infix_funcs_t BUILTINS[] = 
    {&bi_add, &bi_sub, &bi_mul, &bi_div};

static const char OPERATOR_CHARS[] = {'+', '-', '*', '/'};

#endif//AST_BUILTINS_H
