/* Copyright 2018 Tronlong Elec. Tech. Co. Ltd. All Rights Reserved. */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <libgen.h>

/* Get array size */
#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])

/* User-operable LEDs */
static char *g_leds[] = {
    "/sys/class/leds/user-led0",
    "/sys/class/leds/user-led1",
    "/sys/class/leds/user-led2",
    "/sys/class/leds/user-led3"
};

/* Exit flag */
volatile bool g_quit = false;

/* Short option names */
static const char g_shortopts [] = ":n:vh";

/* Option names */
static const struct option g_longopts [] = {
    { "number",      required_argument,      NULL,        'n' },
    { "version",     no_argument,            NULL,        'v' },
    { "help",        no_argument,            NULL,        'h' },
    { 0, 0, 0, 0 }
};

static void usage(FILE *fp, int argc, char **argv) {
    fprintf(fp,
            "Usage: %s [options]\n\n"
            "Options:\n"
            " -n | --number        Number of LEDs, range of 1 to 4 \n"
            " -v | --version       Display version information\n"
            " -h | --help          Show help content\n\n"
            "", basename(argv[0]));
}

static void opt_parsing_err_handle(int argc, char **argv, int flag) {
    /* Exit if no input parameters are entered  */
    int state = 0;
    if (argc < 2) {
        printf("No input parameters are entered, please check the input.\n");
        state = -1;
    } else {
        /* Feedback Error parameter information then exit */
        if (optind < argc || flag) {
            printf("Error:  Parameter parsing failed\n");
            if (flag)
                printf("\tunrecognized option '%s'\n", argv[optind-1]);

            while (optind < argc) {
                printf("\tunrecognized option '%s'\n", argv[optind++]);
            }
            
            state = -1;
        }
    }

    if (state == -1) {
        printf("Tips: '-h' or '--help' to get help\n\n");
        exit(EXIT_FAILURE);
    }
}

void sig_handle(int arg) {
    g_quit = true;
}

int main(int argc, char **argv) {
    int i = 0;
    int c = 0;
    int num = 0;
    int flag = 0;
    char cmd[64] = {0};

    /* Parsing input parameters */
    //g_shortopts为可能输入的短选项
    //g_longopts为可能输入的长选项
    while ((c = getopt_long(argc, argv, g_shortopts, g_longopts, NULL)) != -1) {
        switch (c) {
        case 'n':
            num = atoi(optarg);
            break;

        case 'v':
            /* Display the version */
            printf("version : 1.0\n");
            exit(EXIT_SUCCESS);

        case 'h':
            usage(stdout, argc, argv);
            exit(EXIT_SUCCESS);
                
        default :
            flag = 1;
            break;
        }
    }

    opt_parsing_err_handle(argc, argv, flag);

    /* Check if the number of LEDs is out of preset range */
    if ((num > ARRAY_SIZE(g_leds)) || (num < 1)) {
        printf("Error: The number of LEDs entered exceeds the preset range(1-4)\n");
        exit(EXIT_FAILURE);
    }

    /* Ctrl+c handler */
    signal(SIGINT, sig_handle);

    /* Print LEDs */
    printf("\nSystem leds :\n");
    system("find /sys/class/leds/*");

    printf("\nFlashing leds :\n");
    for (i = 0; i < num; i++)
        printf("%s\n",g_leds[i]);

    while (!g_quit) {
        /* Turn on LEDs */
        for (i = 0; i < num; i++) {
            /* Set the LED brightness value to 1 to turn on the led */
            snprintf(cmd, 64, "echo 1 > %s/brightness", g_leds[i]);
            if (system(cmd) != 0) {
                fprintf(stderr, "Error: Failed to turn on %s\n", g_leds[i]);
                exit(EXIT_FAILURE);
            }
        }

        /* Keep the LEDs on for 500 ms */
        usleep(500 * 1000);

        /* Turn off LEDs */
        for (i = 0; i < num; i++) {
            /* Set the LED brightness value to 0 to turn off the LED */
            snprintf(cmd, 64, "echo 0 > %s/brightness", g_leds[i]);
            if (system(cmd) != 0) {
                fprintf(stderr, "Error: Failed to turn off %s\n", g_leds[i]);
                exit(EXIT_FAILURE);
            }
        }

        /* Keep the LEDs off for 500 ms */
        usleep(500 * 1000);
    }

    printf("Exit\n");
    return 0;
}
