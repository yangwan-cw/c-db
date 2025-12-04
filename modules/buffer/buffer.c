//
// Created by wangzhaobin on 12/4/2025.
//
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inputBuffer/InputBuffer.h"


/**
 * 
 * @return 返回初始化的输入缓冲区
 */
InputBuffer *new_input_buffer() {
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}


ssize_t getline(char **buffer, size_t *buffer_length, FILE *file);

ssize_t  read_input_buffer(InputBuffer *input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);


    if (bytes_read < 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
    return bytes_read;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}
/*
 * my_getline:
 *   lineptr : 指向 char* 的指针（由调用者传入）
 *   n       : 指向缓冲区大小的变量
 *   stream  : 输入文件流
 *
 * 返回值:
 *   >=0: 实际读取的字符数（包含 '\n'）
 *   -1 : EOF 且无数据可读
 */
ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
    /* 参数检查 */
    if (lineptr == NULL || n == NULL || stream == NULL) {
        errno = EINVAL;
        return -1;
    }

    char *buf = *lineptr;
    size_t buf_size = *n;

    /* 如果 buffer 为空，初始化一个默认大小 */
    if (buf == NULL || buf_size == 0) {
        buf_size = 128;
        buf = (char *) malloc(buf_size);
        if (!buf) return -1; // 内存分配失败
        *lineptr = buf;
        *n = buf_size;
    }

    size_t pos = 0;
    int c;

    while (1) {
        c = getc(stream);

        /* 如果一开始就 EOF */
        if (c == EOF && pos == 0) {
            return -1;
        }

        /* 若缓冲区不够，需要扩容 */
        if (pos + 1 >= buf_size) {
            size_t new_size = buf_size * 2;
            char *new_buf = (char *) realloc(buf, new_size);
            if (!new_buf) {
                return -1; // 扩容失败
            }
            buf = new_buf;
            buf_size = new_size;
            *lineptr = buf;
            *n = buf_size;
        }

        /* 存入字符 */
        if (c == EOF) {
            buf[pos] = '\0';
            break;
        }

        buf[pos++] = (char) c;

        /* 遇到换行，则结束读取 */
        if (c == '\n') {
            break;
        }
    }

    buf[pos] = '\0'; // C字符串结尾
    return pos; // 返回读取的长度
}
