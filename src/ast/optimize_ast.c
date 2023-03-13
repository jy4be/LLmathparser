#include "ast/ast.h"
#include "nlib/stdalloc.h"
#include <stdio.h>
#include <stdlib.h>

expression_t *sub_optimize(expression_t *node,
        expression_stack_t *exp_stack);


/* Optimize the AST:
 * At the moment, it just calculates the result of expressions
 * which don't contain the variable; There could be done a lot
 * more.
 *
 * Also sets up a new, clean stack.
 */
expression_t *optimize_ast(
        expression_t* top,
        expression_stack_t* clean_exp_stack) 
{
    nstk_setup((*clean_exp_stack), 1024, stdalloc);

    return sub_optimize(top, clean_exp_stack);
}

/* The actual optimization function called on the expressions 
 *
 * First recursively calls itself on all child expressions.
 * If, after that, all child expressions are numeric expressions,
 * calculate the result and return it, otherwise, do nothing*/
expression_t *sub_optimize(
        expression_t *node,
        expression_stack_t *exp_stack)
{
    expression_t *result, *left, *right;
    expression_t new_exp;

    switch(node->type) {
    case EXP_NUM:
        new_exp = (expression_t) {
            .type = EXP_NUM,
            .value = node->value};
        nstk_push((*exp_stack), new_exp); 
        result = &nstk_top((*exp_stack));
        break;
    case EXP_VAR:
        new_exp = (expression_t) {
            .type = EXP_VAR};
        nstk_push((*exp_stack), new_exp); 
        result = &nstk_top((*exp_stack));
        break;
    case EXP_BRACKET:
        left = sub_optimize(
                node->expr,
                exp_stack);
        if (left->type == EXP_NUM) {
            result = left;
        }
        else {
            new_exp = (expression_t) {
                .type = EXP_BRACKET,
                .expr = left};
            nstk_push((*exp_stack), new_exp); 
            result = &nstk_top((*exp_stack));

        }
        break;
    case EXP_FUNC:
        //currently, pow is the only function
        //if there were more inbuilt functions, they'd have to be
        //differentiated here
        left = sub_optimize(
                node->expr,
                exp_stack);
        if (left->type == EXP_NUM) {
            new_exp = (expression_t) {
                .type = EXP_NUM,
                .value = left->value * left->value};
            nstk_push((*exp_stack), new_exp); 
            result = &nstk_top((*exp_stack));
        }
        else {
            new_exp = (expression_t) {
                .type = EXP_FUNC,
                .expr = left,
                .id_name = node->id_name};
            nstk_push((*exp_stack), new_exp); 
            result = &nstk_top((*exp_stack));

        }
        break;
    case EXP_ADD:
        left = sub_optimize(node->left, exp_stack);
        right = sub_optimize(node->right, exp_stack);

        if (left->type == EXP_NUM && right->type == EXP_NUM){
            new_exp = (expression_t) {
                        .type = EXP_NUM,
                        .value = left->value + right->value};
            nstk_push((*exp_stack), new_exp); 
        }
        else {
            new_exp = (expression_t) {
                .type = EXP_ADD,
                .left = left,
                .right = right};
            nstk_push((*exp_stack), new_exp); 
        }
        result = &nstk_top((*exp_stack));
        break;
    case EXP_SUB:
        left = sub_optimize(node->left, exp_stack);
        right = sub_optimize(node->right, exp_stack);

        if (left->type == EXP_NUM && right->type == EXP_NUM){
            new_exp = (expression_t) {
                        .type = EXP_NUM,
                        .value = left->value - right->value};
            nstk_push((*exp_stack), new_exp); 
        }
        else {
            new_exp = (expression_t) {
                .type = EXP_SUB,
                .left = left,
                .right = right};
            nstk_push((*exp_stack), new_exp); 
        }
        result = &nstk_top((*exp_stack));
        break;
    case EXP_MUL:
        left = sub_optimize(node->left, exp_stack);
        right = sub_optimize(node->right, exp_stack);

        if (left->type == EXP_NUM && right->type == EXP_NUM){
            new_exp = (expression_t) {
                        .type = EXP_NUM,
                        .value = left->value * right->value};
            nstk_push((*exp_stack), new_exp); 
        }
        else {
            new_exp = (expression_t) {
                .type = EXP_MUL,
                .left = left,
                .right = right};
            nstk_push((*exp_stack), new_exp); 
        }
        result = &nstk_top((*exp_stack));
        break;
    case EXP_DIV:
        left = sub_optimize(node->left, exp_stack);
        right = sub_optimize(node->right, exp_stack);

        if (left->type == EXP_NUM && right->type == EXP_NUM){
            new_exp = (expression_t) {
                        .type = EXP_NUM,
                        .value = left->value / right->value};
            nstk_push((*exp_stack), new_exp); 
        }
        else {
            new_exp = (expression_t) {
                .type = EXP_DIV,
                .left = left,
                .right = right};
            nstk_push((*exp_stack), new_exp); 
        }
        result = &nstk_top((*exp_stack));
        break;
    case EXP_EMPTY:
        printf("should not optimize empty expression!\n");
        exit(-1);
    }
        
    return result;
}

