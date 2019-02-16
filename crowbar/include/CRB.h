//
// Created by sam on 2019-02-16.
//

#ifndef DESIGNCOMPLIER_CRB_H
#define DESIGNCOMPLIER_CRB_H

#include <stdio.h>

typedef struct CRB_Interpreter_tag CRB_Interpreter;
CRB_Interpreter *CRB_create_interpreter;

void CRB_compile(CRB_Interpreter *interpreter, FILE *fp);

void CRB_interpret(CRB_Interpreter *interpreter);

void CRB_dispose_interpreter(CRB_Interpreter *interpreter);

#endif //DESIGNCOMPLIER_CRB_H
