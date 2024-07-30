/**
 * Copyright (C) 2013 Guangzhou Tronlong Electronic Technology Co., Ltd. - www.tronlong.com
 *
 * @file csi_test.c
 *
 * @brief Example application main file.
 * This application continuously collects the specified frame number image,
 * calculates the time, prints the rate, checks the last frame image data.
 *
 * @author Tronlong <support@tronlong.com>
 *
 * @version V1.0
 *
 * @date 2022-8-15
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <stdint.h>
#include <sys/time.h>

#include "v4l2_device_control.h"
#include "parameter_parser.h"

volatile bool g_quit = false;

static void sig_handle(int signal)
{
    g_quit = true;
}

bool check_data(const uint8_t *data, uint32_t width, uint32_t height)
{
    uint32_t value = 0;
    uint32_t check_value;
    uint32_t error_num = 0;
    int status = 0;
    int i;

    for (i = 0; i <= width * height; i++) {
        check_value = value % 256;
        if (check_value != data[i]) {
            error_num = error_num + 1;
            status = 1;
        }
        value++;
    }
    printf("byte error rate= %.1f%%\n", ((float)error_num / (width * height)) * 100);

    if (status == 0) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char **argv)
{
    struct _Params params;
    int frame_cnt = 0;
    struct timeval time_start, time_end, time_diff;
    uint32_t cost_time;
    float average_rate;

    memset(&params, 0, sizeof(params));
    if (parse_parameter(&params, argc, argv) == false) {
        printf("Please try --help to see usage.\n");
        exit(2);
    }

    /* Ctrl+c handler */
    signal(SIGINT, sig_handle);

    V4l2Device *camera = v4l2_device_open(params.device, params.type, params.format,
                                              params.width, params.height, params.fps);

    printf("User Inputs:\n"
            "    Device       : %s\n"
            "    Fomat        : %s\n"
            "    Width        : %d\n"
            "    Height       : %d\n"
            "\n",
            params.device,
            params.format,
            params.width,
            params.height);

    v4l2_device_setup(camera);
    v4l2_device_stream_on(camera);

    gettimeofday(&time_start, NULL);
    while (!g_quit) {
        /* Get one frame */
        if (v4l2_device_get_buffer(camera, 3)) {
            ++frame_cnt;

            if (params.number == frame_cnt) {
                g_quit = true;
            }

            printf("\r\033[KAccept Frames: %d", frame_cnt);
            char filename[100];
            sprintf(filename, "/mnt/usb/sda1/frame_%d.bin", frame_cnt);
            FILE* file = fopen(filename, "wb");
            if (file == NULL) {
                printf("无法打开文件\n");
                return 1;
            }

            fwrite(camera->data, sizeof(unsigned char), params.width * params.height, file);
            fclose(file);

            //return 0;
            fflush(stdout);
        } else {
            printf("Get frames failed!\n");
            break;
        }

        v4l2_device_put_buffer(camera);
    }
    printf ("\n");

    /* Calculate the acquisition time and average rate */
    gettimeofday(&time_end, NULL);
    timersub(&time_end, &time_start, &time_diff);
    cost_time = time_diff.tv_sec * 1000000.0 + time_diff.tv_usec;
    average_rate = (params.width * params.height * frame_cnt / (cost_time / 1000000.0) / 1024 / 1024);
    printf("time: %d ms, rate: %g MB/s\n", cost_time / 1000, average_rate);

    /* Check the last frame */
    check_data((uint8_t *)camera->data, params.width, params.height);

    v4l2_device_stream_off(camera);
    return 0;
}
