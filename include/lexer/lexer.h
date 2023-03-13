#ifndef LEXER_H_
#define LEXER_H_
#include <stdint.h>
#include <stddef.h>

#define IDENTIFIER_MAX_LENGTH 64

typedef enum {
    OP_BIN = 0,
    BRACKET_OPEN = 1,
    BRACKET_CLOSE = 2,
    ID_FUNC = 3,
    ID_VAR = 4,
    ID_NUM = 5,
    SYS_EOF = 6,
    EMPTY = 7,
} token_type_t;

typedef enum {
    LEX_EVAL_ID  = 0x1,
    LEX_PUSH_TOK = 0x2,
    LEX_PUSH_ID  = 0x4
} lexer_imperative_t;

typedef struct Token_S {
    token_type_t type;
    union {
        int number;
        char* func;
        char operator;
    };
} token_t;

void print_tokens(token_t* token_list, size_t tok_count);
size_t lex_string(
        char* input, 
        char variable, 
        char** functions,
        size_t fn_count,
        token_t* token_buffer);
#endif//LEXER_H_
