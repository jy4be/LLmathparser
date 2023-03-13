#ifndef AST_H_
#define AST_H_

#include "parser/parser.h"

typedef enum {
    EXP_ADD,
    EXP_SUB,
    EXP_MUL,
    EXP_DIV,
    EXP_VAR,
    EXP_FUNC,
    EXP_NUM,
    EXP_BRACKET,
    EXP_EMPTY,
} expr_type_t;

typedef struct Expression_S {
    expr_type_t type;
    union {
        struct Expression_S* left;
        struct Expression_S* expr;
    };
    struct Expression_S* right;
    union {
        char* id_name;
        double value;
    };
} expression_t;

typedef stack_t(expression_t) expression_stack_t;
typedef stack_t(expression_t*) expression_ptr_stack_t;
typedef stack_t(token_t)      token_stack_t;

expression_t* build_ast(
        pa_stack_t pa_stack,
        expression_stack_t* exp_stack);
expression_t* format_ast(
        expression_t* top_expression,
        expression_stack_t* exp_stack);
double evaluate_ast(expression_t* top,
        double var_value);
expression_t *reorder_ast(
        expression_t* top,
        expression_stack_t* exp_stack);
expression_t *ast_arithmetic_order(expression_t* top);

expression_t *optimize_ast(
        expression_t* top,
        expression_stack_t* clean_exp_stack);

void print_expression(expression_t exp, size_t indent);

#endif//AST_H_
