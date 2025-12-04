#include <stdio.h>
//
// Created by wangzhaobin on 12/4/2025.
//
#include "banner/banner.h"

/**
 * 打印欢迎横幅
 */
void printBanner(char * version) {
    printf("Welcome to the simple c-db!\n");
    printf("Type 'help' for a list of commands.\n");
    printf("Version %s\n", version);
}

/**
 * 打印提示符
 */
void print_prompt() { printf("db > "); }
