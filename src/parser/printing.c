#include "parser/parser.h"
#include <stdio.h>

/* Print a production rule */
void print_rule(rule_t* rule) {
    printf("%d: %s -> ",rule->type, symbol_string(rule->source));
    for(size_t i = 0; i < rule->length;i++) {
        printf("%s ", symbol_string(rule->production[i]));
    }
}

/* String representation of symbol type */
char* symbol_string(symbol_t symbol_number) {
    switch(symbol_number) {
    case T_BIN_OP:
        return "T_BIN_OP";
    case T_BRACKET_OPEN:
        return "T_BRACKET_OPEN";
    case T_BRACKET_CLOSE:
        return "T_BRACKET_CLOSE";
    case T_FUNC:
        return "T_FUNC";
    case T_VAR:
        return "T_VAR";
    case T_NUM:
        return "T_NUM";
    case NT_E:
        return "NT_E";
    case NT_D:
        return "NT_D";
    case NT_T:
        return "NT_T";
    case T_EOS:
        return "$";
    case T_COMMA:
        return "T_COMMA";
    }
}
