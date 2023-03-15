#include "lexer/lexer.h"

#include "stdio.h"

/* Print token and possible information about it */
void print_tokens(token_t* token_list, size_t tok_count) {
    for (size_t i = 0; i < tok_count; i++){
        switch(token_list[i].type){
        case BRACKET_OPEN:
            printf("{BRACKET_OPEN}\n");
            break;
        case BRACKET_CLOSE:
            printf("{BRACKET_CLOSE}\n");
            break;
        case OP_BIN:
            printf("{OP_BIN, operator: %c}\n", token_list[i].operator);
            break;
        case ID_VAR:
            printf("{ID_VAR}\n");
            break;
        case ID_FUNC:
            printf("{ID_FUNC, name: %s}\n", token_list[i].func);
            break;
        case ID_NUM:
            printf("{ID_NUM, value: %d}\n", token_list[i].number);
            break;
        case SYS_EOF:
            printf("{SYS_END_OF_FILE}\n");
            break;
        case COMMA:
            printf("{COMMA}\n");
            break;
        default:
            printf("UNKOWN TOKEN TYPE\n");
        }
    }
}
