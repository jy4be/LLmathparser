#include "ast/ast.h"

#include <stdio.h>
#include <stdlib.h>

#include "nlib/stdalloc.h"


/* Based on the rule aand together with the list of tokens and expression, 
 * transform the data into an expression according to the rule */
expression_t assemble_expression(
        rule_t* rule,
        expression_ptr_stack_t* exp_stack,
        token_stack_t* token_stack,
        expression_stack_t* exp_data_stack);

/* Build Abstract Syntax Tree recursively 
 * based on the rules which the parser produced */
expression_t* build_ast(
        pa_stack_t pa_stack,
        expression_stack_t* exp_data_stack)
{
    stack_t(token_t) token_stack;
    stack_t(expression_t*) exp_stack;

    nstk_setup((*exp_data_stack), 1024, stdalloc);
    nstk_setup(token_stack, 1024, stdalloc);
    nstk_setup(exp_stack, 1024, stdalloc);

    /* For each parser action either:
     *  I.)  Push a token to the token-stack and advance
     *  II.) Assemble an expression from a rule, the tokens 
     *       and the already assembled expressions, and push it to the stack */
    while (nstk_size(pa_stack) > 0) {
        if (nstk_top(pa_stack).type == PA_MATCH) {
            nstk_push(token_stack, nstk_top(pa_stack).token);
        }
        else {
            rule_t* rule = nstk_top(pa_stack).rule;
            expression_t exp = assemble_expression(rule, &exp_stack, &token_stack, exp_data_stack);

            nstk_push((*exp_data_stack), exp);
            nstk_push(
                    exp_stack, 
                    &nstk_top((*exp_data_stack)));

        }
        nstk_pop(pa_stack);
    }

    //Last assembled expression is the top of AST
    expression_t* top_expression = nstk_top(exp_stack);

    nstk_destroy(token_stack);
    nstk_destroy(exp_stack);
    return top_expression;
}

expression_t assemble_expression(
        rule_t* rule,
        expression_ptr_stack_t* exp_stack,
        token_stack_t* token_stack,
        expression_stack_t* exp_data_stack)
{
    expression_t source_exp = {
        .type = EXP_EMPTY,
        .left = NULL,
        .right = NULL};

    //Build expression from rules
    
    if(rule->type == RULE_TYPE_E1) {
        expression_t sub_exp;
        sub_exp.type = EXP_BRACKET;
        sub_exp.left = nstk_top((*exp_stack));
        sub_exp.right= NULL;
        nstk_pop((*exp_stack));
        nstk_push((*exp_data_stack), sub_exp);
        nstk_push(
                (*exp_stack), 
                &nstk_top((*exp_data_stack)));


        source_exp.left = nstk_top((*exp_stack));
        nstk_pop((*exp_stack));
        source_exp.right = nstk_top((*exp_stack));
        nstk_pop((*exp_stack));

        nstk_pop((*token_stack));
        nstk_pop((*token_stack));
    }
    if(rule->type == RULE_TYPE_E2) {
        source_exp.left = nstk_top((*exp_stack));
        nstk_pop((*exp_stack));
        source_exp.right = nstk_top((*exp_stack));
        nstk_pop((*exp_stack));
    }
    if(rule->type == RULE_TYPE_D1) {
        token_t token = nstk_top((*token_stack));
        nstk_pop((*token_stack));

        if (token.operator == '+') {
            source_exp.type = EXP_ADD;
        }
        if (token.operator == '-') {
            source_exp.type = EXP_SUB;
        }
        if (token.operator == '*') {
            source_exp.type = EXP_MUL;
        }
        if (token.operator == '/') {
            source_exp.type = EXP_DIV;
        }
        source_exp.left = nstk_top((*exp_stack));
        nstk_pop((*exp_stack));
    }
    if(rule->type == RULE_TYPE_D2) {
    }
    if(rule->type == RULE_TYPE_T1) {
        source_exp.type = EXP_FUNC;
        token_t token = nstk_top((*token_stack));
        nstk_pop((*token_stack));
        source_exp.id_name = token.func;

        source_exp.left = nstk_top((*exp_stack));
        nstk_pop((*exp_stack));

        nstk_pop((*token_stack));
        nstk_pop((*token_stack));
    }
    if(rule->type == RULE_TYPE_T2) {
        source_exp.type = EXP_VAR;
        nstk_pop((*token_stack));
    }
    if(rule->type == RULE_TYPE_T3) {
        source_exp.type = EXP_NUM;
        token_t token = nstk_top((*token_stack));
        nstk_pop((*token_stack));
        source_exp.value = token.number;
    }

    return source_exp;
}
