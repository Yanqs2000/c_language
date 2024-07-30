/* Copyright 2019 Tronlong Elec. Tech. Co. Ltd. All Rights Reserved. */

#include "v4l2_device_control.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <linux/videodev2.h>

#define CLEAR(x) memset(&(x), 0, sizeof(x))
#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])

struct Buffer{
    void   *start;
    size_t  length;
    int     index;
};

struct PrivateAttributes {
    const char *dev_name;
    int         fd;
    bool        status;

    uint32_t    buffer_num;
    struct Buffer *buffers;
};

typedef struct {
    uint32_t type;
    const char *name;
} FormatType;

FormatType format_type[]={
    {V4L2_PIX_FMT_YUYV,    "YUYV"},
    {V4L2_PIX_FMT_RGB565 , "RGB565"},
    {V4L2_PIX_FMT_SRGGB10, "RGGB"},
    {V4L2_PIX_FMT_SBGGR8, "BGGR"},
    {V4L2_PIX_FMT_NV12, "NV12"},
};

/* Type of the data stream, set by the application. Only these types are valid here */
typedef struct {
    uint32_t type;
    const char *name;
} FormatDesc;

FormatDesc enum_fmt[]={
    {V4L2_CAP_VIDEO_CAPTURE,        "V4L2_CAP_VIDEO_CAPTURE"},
    {V4L2_CAP_VIDEO_CAPTURE_MPLANE, "V4L2_CAP_VIDEO_CAPTURE_MPLANE"},
    {V4L2_CAP_VIDEO_OUTPUT,         "V4L2_CAP_VIDEO_OUTPUT"},
    {V4L2_CAP_VIDEO_OUTPUT_MPLANE,  "V4L2_CAP_VIDEO_OUTPUT_MPLANE"},
    {V4L2_CAP_VIDEO_OVERLAY,        "V4L2_CAP_VIDEO_OVERLAY"},
};

/* Enumerate all frame intervals that the device supports for the given pixel format and frame resolution */
void list_framerates(int fd, uint32_t pixfmt, uint32_t width, uint32_t height) {
    struct v4l2_frmivalenum frmival;
    memset(&frmival, 0, sizeof(frmival));
    frmival.index = 0;
    frmival.pixel_format = pixfmt;
    frmival.width = width;
    frmival.height = height;

    printf("fps: ");
    while (ioctl(fd, VIDIOC_ENUM_FRAMEINTERVALS, &frmival) != -1) {
        switch (frmival.type) {
        /* Discrete frame size. */
        case V4L2_FRMSIZE_TYPE_DISCRETE:
            if (frmival.discrete.numerator != 0)
                printf("%u, ", frmival.discrete.denominator / frmival.discrete.numerator);
            break;
        default:
            break;
        }

        frmival.index++;
    }
    printf("\b\b \n");
    return;
}

/* Enumerate all frame sizes that the device supports for the given pixel format */
void list_resolutions(int fd, uint32_t pixelformat) {
    if (fd < 0) {
        printf("Invalid device Descriptor\n");
        return;
    }

    struct v4l2_frmsizeenum frmsize;
    memset(&frmsize, 0, sizeof(frmsize));
    frmsize.index = 0;
    frmsize.pixel_format = pixelformat;

    while (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) != -1) {
        switch (frmsize.type) {
        /* Discrete frame size. */
        case V4L2_FRMSIZE_TYPE_DISCRETE:
            printf("\tresolution: %ux%u ", frmsize.discrete.width, frmsize.discrete.height);
            list_framerates(fd, frmsize.pixel_format, frmsize.discrete.width, frmsize.discrete.height);
            break;
        default:
            break;
        }

        frmsize.index ++;
    }
    return;
}

/* Initialization of memory mappings */
bool init_buffers(V4l2Device *v4l2_device) {
    if (v4l2_device == NULL)
        return false;

    v4l2_device->pAttr->buffers =
        (struct Buffer *)calloc(v4l2_device->pAttr->buffer_num,
                                sizeof(*v4l2_device->pAttr->buffers));
    if (v4l2_device->pAttr->buffers == NULL)
        return false;

    struct v4l2_requestbuffers req;
    CLEAR(req);
    req.count = v4l2_device->pAttr->buffer_num;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_REQBUFS, &req) < 0) {
        perror("VIDIOC_REQBUFS");
        return false;
    }

    if (req.count < 2) {
        perror("Insufficient buffer memory");
        return false;
    }

    if (! v4l2_device->pAttr->buffers) {
        perror("Out of memory");
        return false;
    }

    uint32_t i;
    for (i = 0; i < req.count; i++) {
        struct v4l2_buffer buf;
        CLEAR(buf);
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;

        if (ioctl(v4l2_device->pAttr->fd, VIDIOC_QUERYBUF, &buf) < 0) {
            perror("VIDIOC_QUERYBUF");
            return false;
        }

        v4l2_device->pAttr->buffers[i].index =  i;
        v4l2_device->pAttr->buffers[i].length = buf.length;
        v4l2_device->pAttr->buffers[i].start =
            mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                    MAP_SHARED, v4l2_device->pAttr->fd, buf.m.offset);

        if (MAP_FAILED == v4l2_device->pAttr->buffers[i].start) {
            perror("mmap()");
            return false;
        }
    }

    for (i = 0; i < v4l2_device->pAttr->buffer_num; i++) {
        struct v4l2_buffer buf;
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (ioctl(v4l2_device->pAttr->fd, VIDIOC_QBUF, &buf) != 0) {
            perror("VIDIOC_QBUF");
            return false;
        }
    }

    return true;
}

/* to support TL2640 */
bool vpif_camera_init(V4l2Device *v4l2_device) {
    if (v4l2_device == NULL)
        return false;

    bool found = false;
    int input_idx;

    /* Enumerate inputs to get the name of the input chosen by user*/
    struct v4l2_input input;
    input.index = 0;
    while (1) {
        int ret = ioctl(v4l2_device->pAttr->fd, VIDIOC_ENUMINPUT, &input);
        if (ret < 0) {
            perror("VIDIOC_ENUMINPUT\n");
            return false;
        }

        if (strncmp((char*)input.name, "Camera", 6) == 0) {
            found = true;
            break;
        }
    }

    if (!found)
        return false;

    /* Set input
     * VIDIOC_G_INPUT ioctl detects the inputs connected. It returns
     * error if no inputs are connected. Otherwise it returns index of
     * the input connected. */
    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_S_INPUT, &input.index) < 0) {
        perror("VIDIOC_S_INPUT\n");
        return false;
    }

    /* check if input is selected correctly */
    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_G_INPUT, &input_idx) < 0) {
        perror("VIDIOC_G_INPUT\n");
        return false;
    }

    if (input_idx != input.index) {
        printf("Couldn't set input correctly\n");
        return false;
    }

    v4l2_std_id input_std_id;
#ifdef VPIF
    if (v4l2_device->width == 320 && v4l2_device->height == 240) {
        input_std_id = V4L2_STD_BAYER_320;
    } else if (v4l2_device->width == 640  && v4l2_device->height == 480) {
        input_std_id = V4L2_STD_BAYER_640;
    } else if (v4l2_device->width == 800  && v4l2_device->height == 600) {
        input_std_id = V4L2_STD_BAYER_800;
    } else if (v4l2_device->width == 1024 && v4l2_device->height == 768) {
        input_std_id = V4L2_STD_BAYER_1024;
    } else if (v4l2_device->width == 1280 && v4l2_device->height == 1024) {
        input_std_id = V4L2_STD_BAYER_1280;
    } else if (v4l2_device->width == 1600 && v4l2_device->height == 1200) {
        input_std_id = V4L2_STD_BAYER_1600;
    } else {
        printf ("No suitable standard\n");
        return false;
    }
#else
    printf ("VPIF is not supported\n");
    return false;
#endif // ENABLE VPIF

    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_S_STD, &input_std_id) < 0) {
        perror("VIDIOC_S_STD failed\n");
        return false;
    }

    return true;
}

V4l2Device *v4l2_device_open(const char *dev_name,
                             const char *type,
                             const char *format,
                             uint32_t width, uint32_t height, uint32_t fps) {
    if (dev_name == NULL)
        return NULL;

    V4l2Device *v4l2_device = (V4l2Device *)malloc(sizeof(V4l2Device));
    if (v4l2_device == NULL) {
        return NULL;
    }

    v4l2_device->pAttr = (struct PrivateAttributes *)malloc(sizeof(struct PrivateAttributes));
    if (v4l2_device->pAttr == NULL) {
        free(v4l2_device);
        v4l2_device = NULL;
        return NULL;
    }

    v4l2_device->pAttr->dev_name = strdup(dev_name);
    if (v4l2_device->pAttr->dev_name == NULL) {
        free(v4l2_device);
        v4l2_device = NULL;
        return NULL;
    }

    struct stat st;
    if (stat(v4l2_device->pAttr->dev_name, &st) == -1) {
        perror("Cannot identify this device");
        free(v4l2_device);
        v4l2_device = NULL;
        return NULL;
    }

    if (!S_ISCHR(st.st_mode)) {
        perror("Not a device");
        free(v4l2_device);
        v4l2_device = NULL;
        return NULL;
    }

    v4l2_device->pAttr->fd = open(v4l2_device->pAttr->dev_name, O_RDWR | O_NONBLOCK, 0);
    if (v4l2_device->pAttr->fd < 0) {
        perror("open()");
        free(v4l2_device);
        v4l2_device = NULL;
        return NULL;
    }

    v4l2_device->width = width;
    v4l2_device->height = height;
    v4l2_device->field = V4L2_FIELD_NONE;
    v4l2_device->fps = fps;
    v4l2_device->pAttr->buffer_num = 3;

    bool found = false;
    int i;
    for (i = 0; i < ARRAY_SIZE(format_type); i++) {
        if (strcmp(format_type[i].name, format) == 0) {
            v4l2_device->pixfmt = format_type[i].type;
            found = true;
            break;
        }
    }

    if (!found) {
        printf("This format is not supported.\n");
        return NULL;
    }

    /* Camera type of VPIF */
    if (strcmp(type, "vpif") == 0) {
        if (vpif_camera_init(v4l2_device) == false) {
            return NULL;
        }
    }

    /* setup or not  */
    v4l2_device->pAttr->status = false;

    return v4l2_device;
}

/* Enumerate image formats*/
bool v4l2_device_list_format(V4l2Device *v4l2_device) {
    if (v4l2_device == NULL)
        return false;

    int i = 0;
    struct v4l2_fmtdesc fmt;

    printf("Supported Formats:\n");
    for (i = 0; i < ARRAY_SIZE(enum_fmt); i++) {
        memset(&fmt, 0, sizeof(fmt));
        fmt.index = 0;
        fmt.type = enum_fmt[i].type;

        while (ioctl(v4l2_device->pAttr->fd, VIDIOC_ENUM_FMT, &fmt) != -1) {
            printf("   %s: pixelformat = %c%c%c%c, description = '%s'\n",
                    enum_fmt[i].name, fmt.pixelformat & 0xff,
                    (fmt.pixelformat >> 8) & 0xff,
                    (fmt.pixelformat >> 16) & 0xff,
                    (fmt.pixelformat >> 24) & 0xff,
                    fmt.description);
            list_resolutions(v4l2_device->pAttr->fd, fmt.pixelformat);
            fmt.index ++;
        }
    }

    printf("\n");
    return true;
}

bool v4l2_device_setup(V4l2Device *v4l2_device) {
    if (v4l2_device == NULL)
        return false;

    if (v4l2_device->pAttr->status == true)
        return false;

    struct v4l2_capability cap;
    struct v4l2_format fmt;
    struct v4l2_streamparm stream_parm;
    struct v4l2_input inp;

    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_QUERYCAP, &cap) != 0) {
        perror("VIDIOC_QUERYCAP");
        return false;
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        perror("No video capture device");
        return false;
    }

    /* Set input type */
    inp.index = 0;
    inp.type = V4L2_INPUT_TYPE_CAMERA;
    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_S_INPUT, &inp) == -1) {
        perror("VIDIOC_S_INPUT");
        return false;
    }

    CLEAR(fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width        = v4l2_device->width;
    fmt.fmt.pix.height       = v4l2_device->height;
    fmt.fmt.pix.pixelformat  = v4l2_device->pixfmt;
    fmt.fmt.pix.field        = v4l2_device->field;
    fmt.fmt.pix.bytesperline = v4l2_device->width * 2;
    fmt.fmt.pix.sizeimage    = v4l2_device->height * v4l2_device->width * 2;

    /* It is possible to set a failure even if it returns 0 */
    //VIDIOC_S_FMT 用于设置（Set）格式
    //VIDIOC_G_FMT 用于获取（Get）格式
    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_S_FMT, &fmt) < 0) {
        perror("VIDIOC_S_FMT");
        return false;
    }

    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_G_FMT, &fmt) < 0) {
        perror("VIDIOC_G_FMT");
        return false;
    }

    CLEAR(stream_parm);
    stream_parm.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    stream_parm.parm.capture.timeperframe.numerator = 1;
    stream_parm.parm.capture.timeperframe.denominator = v4l2_device->fps;

    if (v4l2_device->fps != 0) {
        /* It is possible to set a failure even if it returns 0 */
        if (ioctl(v4l2_device->pAttr->fd, VIDIOC_S_PARM, &stream_parm) < 0) {
            perror("VIDIOC_S_PARM");
            return false;
        }

        if (ioctl(v4l2_device->pAttr->fd, VIDIOC_G_PARM, &stream_parm) < 0) {
            perror("VIDIOC_G_PARM");
            return false;
        }

        uint32_t fps = stream_parm.parm.capture.timeperframe.denominator /
                    stream_parm.parm.capture.timeperframe.numerator;
        if (v4l2_device->fps != fps) {
            perror("VIDIOC_S_PARM");
            return false;
        }
    }

    if (!init_buffers(v4l2_device))
        return false;

    v4l2_device->pAttr->status = true;

    return true;
}

bool v4l2_device_stream_on(V4l2Device *v4l2_device) {
    if (v4l2_device == NULL)
        return false;

    if (v4l2_device->pAttr->status == false)
        return false;

    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_STREAMON, &type) < 0) {
        perror("VIDIOC_STREAMON");
        return false;
    }

    return true;
}

bool v4l2_device_get_buffer(V4l2Device *v4l2_device, int timeout_s) {
    if (v4l2_device == NULL || v4l2_device->pAttr->status == false)
        return false;

    int i = 0;
    while (true) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(v4l2_device->pAttr->fd, &fds);

        /* Set timeout. */
        struct timeval tv;
        tv.tv_sec = timeout_s;
        tv.tv_usec = 0;

        int ret = select(v4l2_device->pAttr->fd + 1, &fds, NULL, NULL, &tv);
        if (ret == 0) {
            if (++i >= 3) {
                perror("capture timeout");
                return false;
            }
        } else if (ret == -1) {
            if (EINTR == errno)
                continue;

            perror("select()");
            return false;
        } else {
            struct v4l2_buffer buf;
            CLEAR (buf);

            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;

            if (ioctl (v4l2_device->pAttr->fd, VIDIOC_DQBUF, &buf) < 0) {
                perror("VIDIOC_DQBUF");
                return false;
            }

            assert (buf.index < v4l2_device->pAttr->buffer_num);

            v4l2_device->offset = buf.m.offset;
            v4l2_device->data = v4l2_device->pAttr->buffers[buf.index].start;
            v4l2_device->data_size = buf.bytesused;

            return true;
        }
    }
}

bool v4l2_device_put_buffer(V4l2Device *v4l2_device) {
    if (v4l2_device->data == NULL)
        return false;

    struct v4l2_buffer buf;
    CLEAR (buf);

    int i, index = 0;
    for (i = 0; i < v4l2_device->pAttr->buffer_num; i++) {
        if (v4l2_device->data == v4l2_device->pAttr->buffers[i].start) {
            index = v4l2_device->pAttr->buffers[i].index;
            break;
        }
    }

    if (i == v4l2_device->pAttr->buffer_num)
        return false;

    /* Enqueue the buffer */
    buf.m.offset = (unsigned long)v4l2_device->data;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = index;

    if (ioctl (v4l2_device->pAttr->fd, VIDIOC_QBUF, &buf) < 0) {
        perror("VIDIOC_QBUF");
        return false;
    }

    return true;
}

bool v4l2_device_stream_off(V4l2Device *v4l2_device) {
    if (v4l2_device == NULL)
        return false;

    if (v4l2_device->pAttr->status == false)
        return false;

    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(v4l2_device->pAttr->fd, VIDIOC_STREAMOFF, &type) < 0) {
        perror("Stop capture failed");
        return false;
    }

    return true ;
}

bool v4l2_device_close(V4l2Device *v4l2_device) {
    if (v4l2_device == NULL)
        return false;

    uint32_t i;
    if (v4l2_device->pAttr->buffers != NULL) {
        for (i = 0; i < v4l2_device->pAttr->buffer_num; i++) {
            if (v4l2_device->pAttr->buffers[i].start == NULL)
                continue;

            if (munmap(v4l2_device->pAttr->buffers[i].start, v4l2_device->pAttr->buffers[i].length) == -1) {
                perror("munmap()");
                return false;
            }

            v4l2_device->pAttr->buffers[i].start = NULL;
            usleep(1000);
        }
    }

    if (close(v4l2_device->pAttr->fd) < 0) {
        perror("close device failed");
        return false;
    }

    if (v4l2_device->pAttr != NULL)
        free(v4l2_device->pAttr);

    free(v4l2_device);

    return true;
}
