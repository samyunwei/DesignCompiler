//
// Created by sam on 2019-03-03.
//
#include <crowbar.h>
#include "MEM.h"
#include "DEBUG.h"
#include "crowbar.h"

void crb_function_define(char *identifier, ParameterList *parameter_list, Block *block) {
    FunctionDefinition *f;
    CRB_Interpreter *inter;

    if (crb_search_function(identifier)) {
        crb_compile_error(FUNCTION_MULTIPLE_DEFINE_ERR,
                          STRING_MESSAGE_ARGUMENT, "name", identifier, MESSAGE_ARGUMENT_END);
    }

    inter = crb_get_current_interpreter();
    f = crb_malloc(sizeof(FunctionDefinition));
    f->name = identifier;
    f->type = identifier;
    f->u.crowbar_f.parameter = parameter_list;
    f->u.crowbar_f.block = block;
    f->next = inter->function_list;
    inter->function_list = f;
}

ParameterList *crb_create_parameter(char *identifier) {
    ParameterList *p;

    p = crb_malloc(sizeof(ParameterList));
    p->name = identifier;
    p->next = NULL;

    return p;
}

ParameterList *crb_chain_parameter(ParameterList *list, char *identifier) {
    ParameterList *pos;
    for (pos = list; pos->next; pos = pos->next);
    pos->next = crb_create_parameter(identifier);
    return list;
}

ArgumentList *crb_create_argument_list(Expression *expression) {
    ArgumentList *al;
    al = crb_malloc(sizeof(ArgumentList));
    al->expression = expression;
    al->next = NULL;

    return al;
}

ArgumentList *crb_chain_argument_list(ArgumentList *list, Expression *expr) {
    ArgumentList *pos;
    for (pos = list; pos->next; pos = pos->next);

    pos->next = crb_create_argument_list(expr);
    return list;
}

StatementList *crb_create_statement_list(StatementList *statement) {
    StatementList *sl;

    sl = crb_malloc(sizeof(StatementList));
    sl->statement = statement;
    sl->next = NULL;

    return sl;
}

StatementList *crb_chain_statement_list(StatementList *list, Statement *statement) {
    StatementList *pos;

    if (list == NULL) {
        return crb_create_argument_list(statement);
    }
    for (pos = list; pos->next; pos = pos->next);

    pos->next = crb_create_argument_list(statement);
    return list;
}

Expression *crb_alloc_expression(ExpressionType type) {
    Expression *exp;

    exp = crb_malloc(sizeof(Expression));
    exp->type = type;
    exp->line_number = crb_get_current_interpreter()->current_line_number;

    return exp;

}

Expression *crb_create_assign_expression(char *variable, Expression *operand) {
    Expression *exp;

    exp = crb_alloc_expression(ASSIGN_EXPRESSION);
    exp->u.assign_expression.variable = variable;
    exp->u.assign_expression.operand = operand;

    return exp;
}