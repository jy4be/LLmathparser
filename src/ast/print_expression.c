#include "ast/ast.h"
#include "computer/builtins.h"

#include <stdio.h>

char* expr_type_string(expr_type_t type);

/* Recursivly print an expression and call itself on
 * all child expressions. Indentation determines how many
 * spaces are before an expression.
 */
void print_expression(expression_t exp, size_t indent) {
    for(size_t i = 0; i < indent; i++)
        printf(" ");

    printf("{type: %s", expr_type_string(exp.type));
    if(exp.type == EXP_FUNC)
        printf(", func name: %s", exp.id_name);
    if(exp.type == EXP_NUM)
        printf(", value: %f", exp.value);
    if(exp.type == EXP_BIN_OP)
        printf(", operator: %c", OPERATOR_CHARS[exp.operator]);
    printf("}\n");

    if(exp.left)
        print_expression(*exp.left, indent+1);
    if(exp.right)
        print_expression(*exp.right, indent+1);
}

/* Stringified version of the expression type name */
char* expr_type_string(expr_type_t type) {
    switch (type) {
    case (EXP_BIN_OP):
        return "BIN_OP";
    case (EXP_BRACKET):
        return "BRACKET";
    case (EXP_FUNC):
        return "FUNC";
    case (EXP_VAR):
        return "VAR";
    case (EXP_NUM):
        return "NUM";
    case (EXP_EMPTY):
        return "EMPTY";
    }
    return "UNKNOWN";
}
