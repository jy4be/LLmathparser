#include <stdio.h>
#include <string.h>

#include "nlib/nstack.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ast/ast.h"

#define INPUT_MAX_LENGTH 256
#define MAX_TOKENS 256
#define VAR_VALUE 1.0

void readline(char *buf, size_t max_Length);


int main(int argc, char **argv) {
    char fn[INPUT_MAX_LENGTH];
    token_t token_List[MAX_TOKENS];
    pa_stack_t parser_actions;
    size_t token_count;
    expression_stack_t exp_data_stack;
    expression_stack_t clean_exp_data_stack;
    expression_t* top_exp;
    double result;

    //currently, pow is the only function, and no mechanism for ohter functions is in place
    char *funcs[] = {"pow"};


    //read an input string from the console
    readline(fn, INPUT_MAX_LENGTH);
    
    //Lex input string
    token_count = lex_string(fn, 'x', funcs, 1, token_List);
    print_tokens(token_List, token_count);

    //Parse tokens
    parser_actions = parse_tokens(token_List, token_count);

    //Construct AST from production rules
    top_exp = build_ast(parser_actions, &exp_data_stack);
    print_expression(*top_exp, 0);
    printf("\n");

    //Compress AST and put it in arithmetic order
    top_exp = format_ast(top_exp, &exp_data_stack);
    top_exp = reorder_ast(top_exp, &exp_data_stack);
    top_exp = ast_arithmetic_order(top_exp);
    print_expression(*top_exp, 0);
    printf("\n");

    //Optimize AST
    top_exp = optimize_ast(top_exp, &clean_exp_data_stack);
    nstk_destroy(exp_data_stack);

    print_expression(*top_exp, 0);

    //Evaluate AST
    result = evaluate_ast(top_exp, VAR_VALUE);
    printf("\nFinal result: f(%f) = %f\n", VAR_VALUE, result);

    nstk_destroy(clean_exp_data_stack);
    nstk_destroy(parser_actions);
    return 0;
}

/* Function uses fgetc to read stdin until linebreak occurs*/
void readline(char *buf, size_t max_Length) {
    for(size_t i = 0; i < max_Length-1;i++) {
        buf[i] = fgetc(stdin);
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
        buf[max_Length - 1] = '\0';
    }
}
