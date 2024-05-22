#include "stringparser.h"
#include <stdio.h>

int main(int argc, char **argv){
	for(;;){
		char input;
		scanf("%c", &input);	
		buffer_write(input);
		if(input == '\n'){
			buffer_print();
			int top, split;
			if(buffer_get_command_split_and_top(&top, &split) == true){
				for(int i = top; i > 0; i--)
					printf("\x1b[33m%d:\x1b[0m %d == '%c'\n", i, buffer_read(i), buffer_read(i));
				printf("Value: %d\n", buffer_get_val_from_split_index(split));
				printf("FORWARD: %d\n", buffer_check_matching_command(top, split, "FORWARD"));
			}
		}
	}
}
