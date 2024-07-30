/* Copyright 2019 Tronlong Elec. Tech. Co. Ltd. All Rights Reserved. */

#ifndef PARAMETER_PARSER_H
#define PARAMETER_PARSER_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#if defined (__cplusplus)
extern "C" {
#endif

struct _Params {
    char        *device;
    char        *type;
    char        *format;
    uint32_t    width;
    uint32_t    height;
    uint32_t    fps;
    uint32_t    number;
};

bool parse_parameter(struct _Params *params, int argc, char **argv);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* PARAMETER_PARSER_H */
