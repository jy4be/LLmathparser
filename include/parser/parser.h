#ifndef PARSER_H_
#define PARSER_H_
#include "lexer/lexer.h"
#include "nlib/nstack.h"


typedef enum {
    T_BIN_OP = 0,
    T_BRACKET_OPEN = 1,
    T_BRACKET_CLOSE = 2,
    T_FUNC = 3,
    T_VAR = 4,
    T_NUM = 5,
    T_COMMA = 6,
    NT_E = 100,
    NT_D = 101,
    NT_T = 102,
    T_EOS
} symbol_t;

typedef enum {
    RULE_TYPE_E1,
    RULE_TYPE_E2,
    RULE_TYPE_D1,
    RULE_TYPE_D2,
    RULE_TYPE_T1,
    RULE_TYPE_T2,
    RULE_TYPE_T3,
} rule_type_t;

typedef enum {
    PA_MATCH,
    PA_PRODUCE,
} parser_action_type_t;


typedef struct Rule_S {
    size_t length;
    rule_type_t type;
    symbol_t source;
    symbol_t production[6];
} rule_t;

typedef struct Parser_Action_S {
    parser_action_type_t type;
    union {
        rule_t* rule;
        token_t token;
    };
} parser_action_t;

typedef stack_t(parser_action_t) pa_stack_t;


pa_stack_t parse_tokens(
        token_t* tokens, 
        size_t token_count);
void print_symbol(symbol_t to_print);
void print_rule(rule_t* rule);
char* symbol_string(symbol_t symbol_number);

#endif//PARSER_H_
