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
//(1)只有一个字符，不带冒号——只表示选项， 如-c
//(2)一个字符，后接一个冒号——表示选项后面带一个参数，如-a 100
//(3)一个字符，后接两个冒号——表示选项后面带一个可选参数，即参数可有可无， 
//如果带参数，则选项与参数直接不能有空格-b100
static const char short_opts [] = ":d:F:w:h:n:v";
//name:表示选项的名称,比如daemon,dir,out等。
//has_arg:表示选项是否需要参数。
/*
a: no_argument(或者是0)时 ——参数后面不跟参数值，eg: --version,–help b:
required_argument(或者是1)时 ——参数输入格式为：–参数 值 或者 --参数=值。eg:–dir=/home c:
optional_argument(或者是2)时 ——参数输入格式只能为：–参数=值
*/
//flag:NULL表示选中某个长选项的时候，getopt_long将返回val值。
//如果参数不为空，那么当选中某个长选项的时候，getopt_long将返回0，并且将flag指针参数指向val值。
//val:表示指定函数找到该选项时的返回值，或者当flag非空时指定flag指向的数据的值val。
static const struct option long_opts [] = {
    { "device",         required_argument,    NULL, 'd' },
    { "Format",         required_argument,    NULL, 'F' },
    { "width",          required_argument,    NULL, 'w' },
    { "height",         required_argument,    NULL, 'h' },
    { "number",         required_argument,    NULL, 'n' },
    { "version",        no_argument,          NULL, 'v' },
    { "help",           no_argument,          NULL, 0   },
    { 0, 0, 0, 0 }//必要填充
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
            params->device = optarg;//optrag表示-x后面的指向参数的指针
            break;
        case 'F':
            //YUV也常常叫做YCbCr， YCbCr中的Cb指蓝色色度分量，而Cr指红色色度分量。
            //YUV 4:2:2 格式。它是一种用于视频压缩和传输的颜色编码格式。
            //YUYV 格式按顺序存储亮度（Y）和色度（U 和 V）信息。具体来说，每两个像素共用一个 U 和一个 V 值。
            if (strcmp(optarg, "YUYV") == 0) {
                params->format = "YUYV";
            }
            //RGB565 每个像素用16位表示，RGB分量各使用5位、6位、5位；
            else if (strcmp(optarg, "RGB565") == 0) {
                params->format = "RGB565";
            }
            /*raw数据是sensor输出的原始数据，是sensor将光信号转化为电信号时的电平高低的原始记录，
            单纯地没有进行任何处理的图像数据，即摄像元件直接得到的电信号进行数字化处理而得到的。
            raw数据在输出的时候是有一定顺序的，主要有四种: GRBG、RGGB、BGGR、GBRG*/
            else if (strcmp(optarg, "RGGB") == 0) {
                params->format = "RGGB";
            }
            else if (strcmp(optarg, "BGGR") == 0) {
                params->format = "BGGR";
            }
            /*它同样采用了YUV 4:2:0的采样方式。NV12的Y分量是亮度信息，V和U分量也是色度信息。不同的是，
            与NV21不同的是，NV12的Y、V、U三个分量分别采用了不同的采样率，
            即垂直方向上每两个像素采样一次，水平方向上每隔一个像素采样一次。*/
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
