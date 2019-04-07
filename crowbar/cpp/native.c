//
// Created by sam on 2019-04-07.
//
#include <stdio.h>
#include <string.h>
#include "MEM.h"
#include "DEBUG.h"
#include "CRB_dev.h"
#include "crowbar.h"

#define NATIVE_LIB_NAME "crowbar.lang.file"

static CRB_NativePointerInfo st_native_lib_info = {
        NATIVE_LIB_NAME
};

