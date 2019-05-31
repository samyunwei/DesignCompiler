//
// Created by sam on 2019-04-07.
//
#include <stdio.h>
#include <string.h>
#include <CRB_dev.h>
#include "MEM.h"
#include "DEBUG.h"
#include "CRB_dev.h"
#include "crowbar.h"

#define NATIVE_LIB_NAME "crowbar.lang.file"

static CRB_NativePointerInfo st_native_lib_info = {
        NATIVE_LIB_NAME
};

static void check_argument_count(int arg_count, int true_count) {
    if (arg_count < true_count) {
        crb_runtime_error(0, ARGUMENT_TOO_FEW_ERR, MESSAGE_ARGUMENT_END);
    } else if (arg_count > true_count) {
        crb_runtime_error(0, ARGUMENT_TOO_MANY_ERR, MESSAGE_ARGUMENT_END);
    }
}

CRB_Value crb_nv_print_proc(CRB_Interpreter *interpreter, int arg_count, CRB_Value *args) {
    CRB_Value value;
    char *str;
    value.type = CRB_NULL_VALUE;
    check_argument_count(arg_count, 1);
    str = CRB_value_to_string(&arg_count[0]);
    printf("%s", str);
    MEM_free(str);
    return value;
}

CRB_Value crb_nv_fopen_proc(CRB_Interpreter *interpreter, int arg_count, CRB_Value *args) {
    CRB_Value value;
    FILE *fp;

    if (arg_count < 2) {
        crb_runtime_error(0, ARGUMENT_TOO_FEW_ERR, MESSAGE_ARGUMENT_END);
    } else if (arg_count > 2) {
        crb_runtime_error(0, ARGUMENT_TOO_MANY_ERR, MESSAGE_ARGUMENT_END);
    }
    if (args[0].type != CRB_STRING_VALUE || args[1].type != CRB_STRING_VALUE) {
        crb_runtime_error(0, FOPEN_ARGUMENT_TYPE_ERR, MESSAGE_ARGUMENT_END);
    }

    fp = fopen(args[0].u.string_value->string, args[1].u.string_value->string);
    if (fp == NULL) {
        value.type = CRB_NULL_VALUE;
    } else {
        value.type = CRB_NATIVE_POINTER_VALUE;
        value.u.native_pointer.info = &st_native_lib_info;
        value.u.native_pointer.pointer = fp;
    }
    return value;
}

static CRB_Boolean check_native_pointer(CRB_Value *value) {
    return value->u.native_pointer.info == &st_native_lib_info;
}

CRB_Value crb_nv_fclose_proc(CRB_Interpreter *interpreter, int arg_count, CRB_Value *args) {
    CRB_Value value;
    FILE *fp;

    value.type = CRB_NULL_VALUE;
    if (arg_count < 1) {
        crb_runtime_error(0, ARGUMENT_TOO_FEW_ERR, MESSAGE_ARGUMENT_END);
    } else if (arg_count > 1) {
        crb_runtime_error(0, ARGUMENT_TOO_MANY_ERR, MESSAGE_ARGUMENT_END);
    }
    if (args[0].type != CRB_NATIVE_POINTER_VALUE || !check_native_pointer(&args[0])) {
        crb_runtime_error(0, FCLOSE_ARGUMENT_TYPE_ERR, MESSAGE_ARGUMENT_END);
    }
    fp = args[0].u.native_pointer.pointer;
    fclose(fp);
    return value;
}

CRB_Value crb_nv_fgets_proc(CRB_Interpreter *interpreter, int arg_count, CRB_Value *args) {
    CRB_Value value;
    FILE *fp;
    char buf[LINE_BUF_SIZE];
    char *ret_buf = NULL;
    int ret_len = 0;

    if (arg_count < 1) {
        crb_runtime_error(0, ARGUMENT_TOO_MANY_ERR, MESSAGE_ARGUMENT_END);
    } else if (arg_count > 1) {
        crb_runtime_error(0, ARGUMENT_TOO_MANY_ERR, MESSAGE_ARGUMENT_END);
    }
    if (args[0].type != CRB_NATIVE_POINTER_VALUE || !check_native_pointer(&args[0])) {
        crb_runtime_error(0, FGETS_ARGUMENT_TYPE_ERR, MESSAGE_ARGUMENT_END);
    }
    fp = args[0].u.native_pointer.pointer;

    while (fgets(buf, LINE_BUF_SIZE, fp)) {
        int new_len;
        new_len = ret_len + strlen(buf);
        ret_buf = MEM_realloc(ret_buf, new_len + 1);
        if (ret_len == 0) {
            strcpy(ret_buf, buf);
        } else {
            strcat(ret_buf, buf);
        }
        ret_len = new_len;
        if (ret_buf[ret_len - 1] == '\n') {
            break;
        }
    }
    if (ret_len > 0) {
        value.type = CRB_STRING_VALUE;
        value.u.string_value = crb_create_crowbar_string(interpreter, ret_buf);
    } else {
        value.type = CRB_NULL_VALUE;
    }
    return value;
}

CRB_Value crb_nv_fputs_proc(CRB_Interpreter *interpreter, int arg_count, CRB_Value *args) {
    CRB_Value value;
    FILE *fp;

    value.type = CRB_NULL_VALUE;
    if (arg_count < 2) {
        crb_runtime_error(0, ARGUMENT_TOO_FEW_ERR, MESSAGE_ARGUMENT_END);
    } else if (arg_count > 2) {
        crb_runtime_error(0, ARGUMENT_TOO_MANY_ERR, MESSAGE_ARGUMENT_END);
    }
    if (args[0].type != CRB_STRING_VALUE ||
        (args[1].type != CRB_NATIVE_POINTER_VALUE || !check_native_pointer(&args[1]))) {
        crb_runtime_error(0, FPUTS_ARGUMENT_TYPE_ERR, MESSAGE_ARGUMENT_END);
    }
    fp = args[1].u.native_pointer.pointer;
    fputs(args[0].u.string_value->string, fp);
    return value;
}

void crb_add_std_fp(CRB_Interpreter *inter) {
    CRB_Value fp_value;
    fp_value.type = CRB_NATIVE_POINTER_VALUE;
    fp_value.u.native_pointer.info = &st_native_lib_info;

    fp_value.u.native_pointer.pointer = stdin;
    crb_add_global_variable(inter, "STDIN", &fp_value);

    fp_value.u.native_pointer.pointer = stdout;
    crb_add_global_variable(inter, "STDOUT", &fp_value);

    fp_value.u.native_pointer.pointer = stderr;
    crb_add_global_variable(inter, "STDERR", &fp_value);
}