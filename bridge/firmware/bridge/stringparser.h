#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#include <stdbool.h>

#define BUFFER_SIZE 16

void buffer_zero(void);

void buffer_write(char val);

char buffer_read(int index);

bool buffer_get_command_split_and_top(int* top_index, int* split_index);

int buffer_get_val_from_split_index(int split_index);

bool buffer_check_matching_command(int top_index, int split_index, char *str);

void buffer_print(void);

#endif
