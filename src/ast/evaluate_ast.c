#include "ast/ast.h"
#include "computer/builtins.h"
#include "nlib/stdalloc.h"
#include <stdio.h>
#include <stdlib.h>


//Recursively calls itself on all child nodes of 'top' expression to calculate result
double evaluate_ast(
        expression_t* top,
        double var_value)
{
    double result = 0;
    
    switch(top->type) {
    case EXP_NUM:
        result = top->value;
        break;
    case EXP_BRACKET:
        result = evaluate_ast(
                top->expr,
                var_value);
        break;
    case EXP_BIN_OP:
        result = BUILTINS[top->operator](
                evaluate_ast(top->left, var_value),
                evaluate_ast(top->right, var_value));
        break;
    case EXP_VAR:
        result = var_value;
        break;
    case EXP_FUNC:
        //currently, pow is the only function
        //if there were more inbuilt functions, they'd have to be
        //differentiated here
        result = evaluate_ast(top->expr, var_value);
        result *= result;
        break;
    case EXP_EMPTY:
        printf("shouldn't evaluate empty expression!\n");
        exit(-1);
    }

    return result;
}
