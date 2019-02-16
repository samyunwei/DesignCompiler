%{
#include <stdio.h>
#include <string.h>
#include <DBG.h>
#include <crowbar.h>
#include "y.tab.h"

int yywarp(void)
{
    return 1;
}

static void increment_line_number(void)
{
    crb_get_current_interpreter()->current_line_number++;
}
%}
%start COMMENT STRING_LITERAL_STATE
%%
<INITIAL>"function"     return FUNCTION;
<INITIAL>"if"           return IF;
<INITIAL>"else" return ELSE;
<INITIAL>"elsif"     return ELSIF;
<INITIAL>"while"     return WHILE;
<INITIAL>"for"     return FOR;
<INITIAL>"return"     return RETURN_T;
<INITIAL>"break"     return BREAK;
<INITIAL>"continue"     return continue;
<INITIAL>"null"     return NULL_T;
<INITIAL>"true"     return TRUE_T;
<INITIAL>"false"     return FALSE_T;
<INITIAL>"global"     return GLOBAL_T;
<INITIAL>"("     return LP;
<INITIAL>")"     return RP;
<INITIAL>"{"     return LC;
<INITIAL>"}"     return RC;
<INITIAL>";"     return SEMICOLON;
<INITIAL>","     return COMMA;
<INITIAL>"&&"     return LOGICAL_AND;
<INITIAL>"||"     return LOGICAL_OR;
<INITIAL>"="     return ASSIGN;
<INITIAL>"=="     return EQ;
<INITIAL>"!="     return NE;
<INITIAL>">"     return GT;
<INITIAL>">="     return GE;
<INITIAL>"<"     return LT;
<INITIAL>"<="     return LE;
<INITIAL>"+"     return ADD;
<INITIAL>"-"     return SUB;
<INITIAL>"*"     return MUL;
<INITIAL>"/"     return DIV;
<INITIAL>"%"     return MOD;
<INITIAL>[A-Za-z_][A-Za-z_0-9]*{
    yylval.identifier = crb_create_identifier(yytext);
    return IDENTIFIER
}
<INITIAL>([1-9][0-0]*)|"0"{
    Expression *expression = crb_alloc_expression(INT_EXPRESSION);
    sscanf(yytext,"%d",&expression->u.int_value);
    yylval.expression = expression;
    return INT_LITERAL;
}

