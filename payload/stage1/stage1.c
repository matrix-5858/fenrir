#include "common.h"
#include "debug.h"
#include "device_config.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    Recovery,
    Fastboot,
    System
} path_t;

static path_t get_path() {
    int (*get_path)(void) = (int (*)(void))GET_PATH_ADDR;
    
    int path = get_path();

    switch (path) {
        case 2:
            printf("Recovery detected!\n");
            return Recovery;
        case 1:
            printf("Fastboot detected!\n");
            return Fastboot;
        default:
            printf("System/other detected!\n");
            return System;
    }
}

static void set_state(int state) {
    void (*set_boot_state)(int) = (void (*)(int))SET_BOOT_STATE_ADDR;
    set_boot_state(state);
}

__attribute__((section(".text.main"))) void main(const char* param) {
    printf("@hexx1edev wuz here!\n");

    int (*ret)(const char*) = (int (*)(const char*))RET_ADDRESS;

    switch (get_path()) {
        case Recovery:
            set_state(2);
            break;
        case Fastboot:
            set_state(0);
            break;
        case System:
            set_state(0);
            break;
    }

    ret(param);

    return;
}