//
// Created by sam on 2019-02-16.
//

#ifndef DESIGNCOMPLIER_CRB_DEV_H
#define DESIGNCOMPLIER_CRB_DEV_H

#include "CRB.h"

typedef enum {
    CRB_FALSE = 0,
    CRB_TRUE = 1
} CRB_Boolean;

typedef struct CRB_String_tag CRB_String;

typedef struct CRB_Object_tag CRB_Object;

typedef struct CRB_Array_tag CRB_Array;

typedef struct LocalEnvironment_tag LocalEnvironment;

typedef struct {
    char *name;
} CRB_NativePointerInfo;

typedef enum {
    CRB_BOOLEAN_VALUE = 1,
    CRB_INT_VALUE,
    CRB_DOUBLE_VALUE,
    CRB_STRING_VALUE,
    CRB_NATIVE_POINTER_VALUE,
    CRB_NULL_VALUE,
    CRB_ARRAY_VALUE
} CRB_ValueType;

typedef struct {
    CRB_NativePointerInfo *info;
    void *pointer;
} CRB_NativePointer;

typedef struct {
    CRB_ValueType type;
    union {
        CRB_Boolean boolean_value;
        int int_value;
        double double_value;
        CRB_NativePointer native_pointer;
        CRB_Object *object;
    } u;

} CRB_Value;

typedef CRB_Value CRB_NativeFunctionProc(CRB_Interpreter *interpreter,
                                         int arg_count, CRB_Value *args);

void CRB_add_native_function(CRB_Interpreter *interpreter, char *name, CRB_NativeFunctionProc *proc);

void CRB_add_native_functuin(CRB_Interpreter *interpreter, char *name, CRB_NativeFunctionProc *proc);

void CRB_add_global_variable(CRB_Interpreter *inter, LocalEnvironment *env, char *str);

CRB_Object *CRB_create_crowbar_string(CRB_Interpreter *inter, LocalEnvironment *env, char *str);

CRB_Object *CRB_create_array(CRB_Interpreter *inter, LocalEnvironment *env, int size);

char *CRB_value_to_string(CRB_Value *value);

#endif //DESIGNCOMPLIER_CRB_DEV_H
