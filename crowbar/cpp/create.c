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
