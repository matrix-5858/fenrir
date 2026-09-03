#include "common.h"
#include "debug.h"
#include "device_config.h"
#include <stdint.h>
#include <stdbool.h>

#ifndef GET_PATH_ADDR 
    #define GET_PATH_ADDR 0x0
#endif

#ifndef SET_BOOT_STATE_ADDR
    #define SET_BOOT_STATE_ADDR 0x0
#endif

#ifndef RET_ADDRESS 
    #define RET_ADDRESS 0x0
#endif


typedef enum {
    Recovery,
    System
} path_t;

static path_t get_path() {
    int (*get_path)(void) = (int (*)(void))GET_PATH_ADDR;
    
    int path = get_path();

    switch (path) {
        case 2:
            printf("Recovery detected! Keeping orange state!\n");
            return Recovery;
        default:
            printf("System/other detected! Patching BOOT_STATE to green!\n");
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
        case System:
            set_state(0);
            break;
    }

    ret(param);

    return;
}
