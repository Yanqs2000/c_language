/* Copyright 2019 Tronlong Elec. Tech. Co. Ltd. All Rights Reserved. */

#ifndef V4L2_DEVICE_CONTROL_H
#define V4L2_DEVICE_CONTROL_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#if defined (__cplusplus)
extern "C" {
#endif

/* This set for camera */
typedef struct _V4l2Device {
    const void *data;
    size_t      data_size;
    uint32_t    offset;

    uint32_t    width;
    uint32_t    height;
    uint32_t    pixfmt;
    uint32_t    field;
    uint32_t    fps;

    struct PrivateAttributes *pAttr;
} V4l2Device;

V4l2Device *v4l2_device_open(const char *dev_name,
                             const char *type,
                             const char *format,
                             uint32_t width, uint32_t height, uint32_t fps);

bool v4l2_device_list_format(V4l2Device *v4l2_device);

bool v4l2_device_setup(V4l2Device *v4l2_device);

bool v4l2_device_stream_on(V4l2Device *v4l2_device);

/* v4l2_device_get_buffer() and v4l2_device_put_buffer() Must be used in combination */
bool v4l2_device_get_buffer(V4l2Device *v4l2_device, int timeout_s);

bool v4l2_device_put_buffer(V4l2Device *v4l2_device);

bool v4l2_device_stream_off(V4l2Device *v4l2_device);

bool v4l2_device_close(V4l2Device *v4l2_device);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* V4L2_DEVICE_CONTROL_H */
