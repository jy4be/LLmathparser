#include "parser/parser.h"
#include "nlib/stdalloc.h"

#include "parser/parser_rules.h"

#include <stdio.h>
#include <stdlib.h>

/* Derive a set of production rules from the tokens,
 * according to rules defined in 'parser_rules.h',
 * Using an LL(1)-parser.
 *
 * A stack of parser actions is returned, containing
 * the exact order of witch symbols were matched and
 * which production rules were used.
 */
pa_stack_t parse_tokens(
        token_t* tokens, 
        size_t token_count)
{
    stack_t(symbol_t) symbol_stack;
    pa_stack_t parser_actions;
    size_t token_index = 0;

    nstk_setup(parser_actions, 512, stdalloc);

    nstk_setup(symbol_stack, 512, stdalloc);
    nstk_push(symbol_stack, T_EOS);
    nstk_push(symbol_stack, NT_E);

    while (nstk_top(symbol_stack) != T_EOS) {
        symbol_t current_symbol = nstk_top(symbol_stack);
        nstk_pop(symbol_stack);

        if(token_count-1 < token_index) {
            printf("END OF FILE REACHED, BUT NOT END OF EXPANSION\n");
            exit(-1);
        }

        if(current_symbol == tokens[token_index].type) {
            printf("Discarded: %s\n", symbol_string(current_symbol));

            parser_action_t pa =  {
                    .type = PA_MATCH,
                    .token = tokens[token_index]};
            nstk_push(parser_actions, pa);
            token_index++;
            continue;
        }
        if(current_symbol < 100){
            printf("ILLEGAL GRAMMAR\n");
            exit(-1);
        }
        rule_t* prod_rule = PARSING_TABLE[current_symbol - 100][tokens[token_index].type];


        if(!prod_rule) {
            printf("ILLEGAL GRAMMAR\n");
            exit(-1);
        }
        else {
            printf("Rule: ");
            print_rule(prod_rule);
            printf("\n");
            parser_action_t pa =  {
                    .type = PA_PRODUCE,
                    .rule = prod_rule};
            nstk_push(parser_actions, pa);
            for(size_t i = 0; i < prod_rule->length ; i++){
                nstk_push(
                        symbol_stack, 
                        prod_rule->production[prod_rule->length-1-i]);
            }
        }
    }
    nstk_destroy(symbol_stack);

    if(token_index != token_count -1) {
        printf("TOKENCOUNT NOT ALIGNED WITH RULE EXPANSION\n");
        printf("%ld of %ld parsed",
                token_index, token_count-1);
        exit(-1);
    }
    printf("Parsing succesfull\n");

    return parser_actions;
}
