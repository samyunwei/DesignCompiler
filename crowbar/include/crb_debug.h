//
// Created by sam on 2019-04-13.
//

#ifndef DESIGNCOMPLIER_CRB_DEBUG_H
#define DESIGNCOMPLIER_CRB_DEBUG_H

#include <stdio.h>
#include "DEBUG.h"

struct DBG_Controller_tag {
    FILE *debug_write_fp;
    int current_debug_level;
};

#endif //DESIGNCOMPLIER_CRB_DEBUG_H
