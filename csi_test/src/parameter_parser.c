/* Copyright 2019 Tronlong Elec. Tech. Co. Ltd. All Rights Reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <libgen.h>

#include "parameter_parser.h"

const char * const VERSION = "1.0";

static const char short_opts [] = ":d:F:w:h:n:v";
static const struct option long_opts [] = {
    { "device",         required_argument,    NULL, 'd' },
    { "Format",         required_argument,    NULL, 'F' },
    { "width",          required_argument,    NULL, 'w' },
    { "height",         required_argument,    NULL, 'h' },
    { "number",         required_argument,    NULL, 'n' },
    { "version",        no_argument,          NULL, 'v' },
    { "help",           no_argument,          NULL, 0   },
    { 0, 0, 0, 0 }
};

static void usage(char *prog_name)
{
    printf ("Usage: %s [options]\n\n"
            "Options:\n"
            " -d | --device         v4l2 device.\n"
            " -F | --Format         V4L2 device capture supported format in this program.\n"
            " -w | --width          V4L2 device capture format width.\n"
            " -h | --height         V4L2 device capture format height.\n"
            " -n | --number         Number of frames to be saved.\n"
            " -v | --version        Version Info.\n"
            " --help                Show this message.\n\n"
            "e.g. :\n"
            "   ./%s -d /dev/video0 -w 1024 -h 512 -F BGGR -n 120\n"
            "\n", prog_name, prog_name);
}


/* Parsing input parameters */
bool parse_parameter(struct _Params *params, int argc, char **argv)
{
    /* default values */
    params->type = "usb";
    params->format = "YUYV";
    params->width = 0;
    params->height = 0;

    int c = 0;
    while ((c = getopt_long(argc, argv, short_opts, long_opts, NULL))!= -1) {
        switch (c) {
        case 'd':
            params->device = optarg;
            break;
        case 'F':
            if (strcmp(optarg, "YUYV") == 0) {
                params->format = "YUYV";
            }
            else if (strcmp(optarg, "RGB565") == 0) {
                params->format = "RGB565";
            }
            else if (strcmp(optarg, "RGGB") == 0) {
                params->format = "RGGB";
            }
            else if (strcmp(optarg, "BGGR") == 0) {
                params->format = "BGGR";
            }
            else if (strcmp(optarg, "NV12") == 0) {
                params->format = "NV12";
            }
            else {
                printf("Not support format: %s\n", optarg);
                return false;
            }
            break;
        case 'w':
            params->width = strtoul(optarg, 0, 10);
            break;
        case 'h':
            params->height = strtoul(optarg, 0, 10);
            break;
        case 'n':
            params->number = strtoul(optarg, 0, 10);
            break;
        case 'v':
            printf("version : %s\n", VERSION);
            exit(0);
        case 0: //--help
            usage(basename(argv[0]));
            exit(0);
        default :
            return false;
        }
    }
    /* Some parameters MUST specify when the mode is display or save. */
    if ((params->device == NULL || params->width == 0 || params->height == 0)) {
        return false;
    }

    return true;
}
