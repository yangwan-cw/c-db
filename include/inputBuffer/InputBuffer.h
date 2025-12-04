//
// Created by wangzhaobin on 12/4/2025.
//

#include <stddef.h>   // 解决 size_t
#include <stdlib.h>   // 也可包含 size_t
#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H
typedef struct {
    char * buffer; // 实际字符
    size_t buffer_length; // 缓冲区分配的总容量
    ssize_t input_length; // 实际读取的字节数（-1 表示错误）
} InputBuffer;

InputBuffer *new_input_buffer();

ssize_t  read_input_buffer(InputBuffer *input_buffer);
void close_input_buffer(InputBuffer* input_buffer);
#endif //INPUTBUFFER_H
