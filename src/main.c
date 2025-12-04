#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <banner/banner.h>


#include "inputBuffer/InputBuffer.h"
#include "prepare/prepare.h"


typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


MetaCommandResult do_meta_command(InputBuffer *input_buffer);

MetaCommandResult do_meta_command(InputBuffer *input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(input_buffer->buffer, ".help") == 0) {
        printf("Available commands:\n");
        printf("  .help    - Show this help message\n");
        printf("  .exit    - Exit the program\n");
        printf("  .tables  - List all tables\n");
        printf("  .version - Show version info\n");
        printf("\n");
        printf("SQL statements:\n");
        printf("  SELECT   - Query data\n");
        printf("  INSERT   - Insert data\n");
        return META_COMMAND_SUCCESS;
    } else if (strcmp(input_buffer->buffer, ".version") == 0) {
        printf("c-db version 1.0.0\n");
        return META_COMMAND_SUCCESS;
    } else if (strcmp(input_buffer->buffer, ".tables") == 0) {
        // TODO: 实现列出所有表
        printf("(no tables yet)\n");
        return META_COMMAND_SUCCESS;
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

int main(int argc, char *argv[]) {
    printBanner("1.0.0");
    InputBuffer *input_buffer = new_input_buffer();
    while (true) {
        print_prompt();
        read_input_buffer(input_buffer);

        // if (strcmp(input_buffer->buffer, ".exit") == 0) {
        //     printf("Bye!\n");
        //     close_input_buffer(input_buffer);
        //     exit(EXIT_SUCCESS);
        // } else {
        //     printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        // }

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("error command\n");
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }
        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n",
                       input_buffer->buffer);
                continue;
            default: ;
        }
        execute_statement(&statement);
        printf("Executed.\n");
    }
}
