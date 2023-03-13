#include "lexer/lexer.h"

#include <string.h>
#include <stdlib.h>

token_t ident_eval(
    char* ident, 
    char** functions,
    size_t fn_count,
    char variable);

/* Lexer - tokenizes the input string. Uses a simple state machine
 * to determine what to do with each character:
 *  LEX_EVAL_ID: Evaluate identifier string and try to construct a token
 *  LEX_PUSH_TOK: Push token generated from this symbol on the stack
 *  LEX_PUSH_ID: Push current character to the identifier
 */
size_t lex_string(
        char* input, 
        char variable, 
        char** functions,
        size_t fn_count,
        token_t* token_buffer)
{
    char ident[IDENTIFIER_MAX_LENGTH];
    size_t ident_index = 0;
    size_t token_index = 0;
    token_t id_token;

    lexer_imperative_t command;
    token_type_t type;
    char operator = '\0';

    for (size_t i = 0; input[i]; i++) {
        switch(input[i]) {
        case ' ':
            command = LEX_EVAL_ID;
            type    = EMPTY;
            break;
        case '(':
            command = LEX_EVAL_ID | LEX_PUSH_TOK;
            type    = BRACKET_OPEN;
            break;
        case ')':
            command = LEX_EVAL_ID | LEX_PUSH_TOK;
            type    = BRACKET_CLOSE;
            break;
        case '+':
            command = LEX_EVAL_ID | LEX_PUSH_TOK;
            type    = OP_BIN;
            operator = '+';
            break;
        case '-':
            command = LEX_EVAL_ID | LEX_PUSH_TOK;
            type    = OP_BIN;
            operator = '-';
            break;
        case '*':
            command = LEX_EVAL_ID | LEX_PUSH_TOK;
            type    = OP_BIN;
            operator = '*';
            break;
        case '/':
            command = LEX_EVAL_ID | LEX_PUSH_TOK;
            type    = OP_BIN;
            operator = '/';
            break;
        default:
            command = LEX_PUSH_ID;
            type    = EMPTY;
            break;
        }

        if(command & LEX_EVAL_ID) {
            id_token = ident_eval(ident, functions, fn_count, variable);
            if(id_token.type != EMPTY)
                token_buffer[token_index++] = id_token;
            ident_index = 0;
            ident[ident_index] = '\0';
        }
        if(command & LEX_PUSH_TOK) {
            token_buffer[token_index++] = 
                (token_t) {.type = type,
                           .operator = operator};
        }
        if(command & LEX_PUSH_ID) {
            ident[ident_index++] = input[i];
            ident[ident_index] = '\0';
        }
    }

    id_token = ident_eval(ident, functions, fn_count, variable);
    if(id_token.type != EMPTY)
        token_buffer[token_index++] = id_token;

    //Last token is End of Intput
    token_buffer[token_index++] = (token_t){.type = SYS_EOF};

    return token_index;
}

//Tries to identify the 'ident' string passed in as a token
token_t ident_eval(
    char* ident, 
    char** functions, 
    size_t fn_count,
    char variable) 
{
    //Identifier is empty, don't generate Token
    if(strlen(ident) == 0)
        return (token_t) {.type = EMPTY};
    //Identifier has length one and is equal to variable, generate var Token
    if(strlen(ident) == 1 && ident[0] == variable)
        return (token_t) {.type = ID_VAR};

    //Check Identifier for equality with any builtin function
    for (size_t i = 0; i < fn_count; i++)
        if(!strcmp(ident, functions[i]))
            return (token_t) {
                .type = ID_FUNC,
                .func = functions[i]};

    //Check if Identifier is numeric, crash if not
    for (size_t i = 0; i < strlen(ident); i++)
        if (ident[i] < 0x30 || ident[i] > 0x39)
            exit(1);

    //generate numeric Token
    return (token_t) {
            .type = ID_NUM,
            .number = atoi(ident)};
}
