//
// Created by sam on 2019-02-10.
//

#ifndef DESIGNCOMPLIER_TOKEN_H
#define DESIGNCOMPLIER_TOKEN_H

typedef enum {
    BAD_TOKEN,
    NUMBER_TOKEN,
    ADD_OPERATOR_TOKEN,
    SUB_OPERATOR_TOKEN,
    MUL_OPERATOR_TOKEN,
    DIV_OPERATOR_TOKEN,
    LEFT_PAREN_TOKEN,
    RIGHT_PAREN_TOKEN,
    END_OF_OPERATOR_TOKEN
} TokenKind;

#define MAX_TOKEN_SIZE (100)

typedef struct {
    TokenKind kind;
    double value;
    char str[MAX_TOKEN_SIZE];
} Token;

void set_line(char *line);

void get_token(Token *token);


#endif //DESIGNCOMPLIER_TOKEN_H
