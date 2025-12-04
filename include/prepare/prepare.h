//
// Created by wangzhaobin on 12/4/2025.
//

#ifndef PREPARE_H
#define PREPARE_H

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
    StatementType type;
} Statement;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);

void execute_statement(Statement *statement);

#endif //PREPARE_H
