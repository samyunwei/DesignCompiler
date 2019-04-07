//
// Created by sam on 2019-04-07.
//

#ifndef DESIGNCOMPLIER_CRB_MEMORY_H
#define DESIGNCOMPLIER_CRB_MEMORY_H

#include "MEM.h"

typedef union Header_tag Header;

struct MEM_Controller_tag {
    FILE *error_fp;
    MEM_ErrorHandler error_handler;
    MEM_FailMode failMode;
    Header *block_header;
};

#endif //DESIGNCOMPLIER_CRB_MEMORY_H
