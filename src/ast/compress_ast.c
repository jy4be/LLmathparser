#include "ast/ast.h"
#include "ast/ast_builtins.h"
#include "nlib/stdalloc.h"
#include <stdio.h>


//Remove empty expressions
expression_t* format_ast(
        expression_t* top_expression,
        expression_stack_t* exp_stack)
{
    if(top_expression->left != NULL)
        top_expression->left = 
            format_ast(top_expression->left, exp_stack);

    if(top_expression->right != NULL)
        top_expression->right = 
            format_ast(top_expression->right, exp_stack);


    if(top_expression->type == EXP_EMPTY) {
        if(!top_expression->right && top_expression->left) {
            return top_expression->left;
        }
        if(top_expression->right && top_expression->left) {
            top_expression->type = top_expression->right->type;
            top_expression->operator = top_expression->right->operator;
            top_expression->right = top_expression->right->left;
        }
        if(!top_expression->right && !top_expression->left) {
            return NULL;
        }
    }

    return top_expression;
}

/* AST is build from back to front, meaning right to left,
 * but it needs to be in left to right order, so the tree needs
 * to be inverted*/
expression_t *reorder_ast(
        expression_t* top,
        expression_stack_t* exp_stack)
{
    stack_t(expression_t*) to_traverse;
    nstk_setup(to_traverse, 1024, stdalloc);

    stack_t(infix_op_type_t) operator_stack;
    nstk_setup(operator_stack, 1024, stdalloc);

    stack_t(expression_t*) values;
    nstk_setup(values, 1024, stdalloc);

    nstk_push(to_traverse, top);

    /* Push all operators on an operator-stack and all values on a
     * value stack, so they can be assembeld in reverse order */
    while(nstk_size(to_traverse)) {
        expression_t* node = nstk_top(to_traverse);
        nstk_pop(to_traverse);

        if(!node)
            continue;

        //Whe an expression with higher priority is found, reorder it first
        if(node->type == EXP_BRACKET || node->type == EXP_FUNC) {
            node->expr = reorder_ast(node->expr, exp_stack);
            nstk_push(values, node);
            continue;
        }

        if(node->type == EXP_BIN_OP) {
            nstk_push(operator_stack, node->operator);
        }
        else
            nstk_push(values, node);

        nstk_push(to_traverse, node->right);
        nstk_push(to_traverse, node->left);

    }

    /* Rebuild the AST in reverse order, so it is left to right */
    expression_t new_top_parent = {0};
    expression_t *to_fill = &new_top_parent;
    while(nstk_size(operator_stack)) {
        expression_t reordered_node = {
            .type = EXP_BIN_OP,
            .operator = nstk_top(operator_stack),
            .right = nstk_top(values)}; 
        nstk_pop(operator_stack);
        nstk_pop(values);

        nstk_push((*exp_stack), reordered_node);
        to_fill->left = &nstk_top((*exp_stack));
        to_fill = &nstk_top((*exp_stack));
    }

    to_fill->left = nstk_top(values);
    nstk_pop(values);

    nstk_destroy(values);
    nstk_destroy(operator_stack);
    nstk_destroy(to_traverse);


    return new_top_parent.left;
}

/* Multiplication and division have a higher arithmetic priority then addition
 * and subtraction, so they need to be ordered in a way where they are calculated first
 *
 * Instead of having the usual cascading slope, multiplication and division are
 * moved in a pyramid shape when a MUL or DIV expression has an ADD or SUB child expression,
 * they extract the right number, form a new expression with this number, and take the place
 * of the right expression.
 *
 * This is done repeatedly until all Expressions are in place.
 *
 *       MUL                     ADD
 *      /  \                    /   \
 *   NUM1  ADD         ->     MUL   EXP...
 *         /  \               /  \
 *     NUM2    EXP...      NUM1  NUM2
 *
 * */
expression_t *ast_arithmetic_order(expression_t* top){
    //Keep track of changes in AST-order, when no changes happened
    //AST is ordered correctly
    bool has_changed = false;
    stack_t(expression_t*) to_traverse;

    nstk_setup(to_traverse, 1024, stdalloc);
    nstk_push(to_traverse, top);

    //cascadingly traverse all nodes
    while(nstk_size(to_traverse)) {
        expression_t *node = nstk_top(to_traverse);
        nstk_pop(to_traverse);

        if(!node)
            continue;

        //check to see if a higher order expression has a 
        //lower order node as child
        if(node->type == EXP_BIN_OP && (node->operator == INF_OP_MUL || node->operator == INF_OP_DIV)) {
            if(node->left->type == EXP_BIN_OP && 
                    (node->left->operator == INF_OP_ADD || node->left->operator == INF_OP_SUB)) {
                expression_t* lesser = node->left;

                node->left = lesser->left;
                lesser->left = node->right;
                node->right = lesser;

                infix_op_type_t tmp = node->operator;
                node->operator = lesser->operator;
                lesser->operator = tmp;

                expression_t *tmp_exp = lesser->right;
                lesser->right = lesser->left;
                lesser->left = tmp_exp;

                has_changed = true;
            }

        }

        nstk_push(to_traverse, node->left);
        nstk_push(to_traverse, node->right);
    }
    nstk_destroy(to_traverse);

    if(has_changed)
        top = ast_arithmetic_order(top);
    return top;
}
