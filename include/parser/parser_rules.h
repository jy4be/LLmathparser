#ifndef PARSER_RULES_H_
#define PARSER_RULES_H_
#include "parser/parser.h"

/* All rules which define the CFG */

const rule_t E1 = 
    {4, RULE_TYPE_E1, NT_E, {T_BRACKET_OPEN, NT_E, T_BRACKET_CLOSE, NT_D}};
const rule_t E2 = 
    {2, RULE_TYPE_E2, NT_E, {NT_T, NT_D}};
const rule_t D1 = 
    {2, RULE_TYPE_D1, NT_D, {T_BIN_OP, NT_E}};
const rule_t D2 = 
    {0, RULE_TYPE_D2, NT_D, {0}};
const rule_t T1 = 
    {6, RULE_TYPE_T1, NT_T, {T_FUNC, T_BRACKET_OPEN, NT_E, T_COMMA, NT_E, T_BRACKET_CLOSE}};
const rule_t T2 = 
    {1, RULE_TYPE_T2, NT_T, {T_VAR}};
const rule_t T3 = 
    {1, RULE_TYPE_T3, NT_T, {T_NUM}};


const rule_t* PARSING_TABLE[3][8] = 
    {{NULL, &E1, NULL, &E2, &E2, &E2, NULL, NULL},
     { &D1, &D2, &D2, &D2, &D2, &D2, &D2, &D2},
     {NULL, NULL, NULL, &T1, &T2, &T3, NULL, NULL}
    };
#endif//PARSER_RULES_H_
