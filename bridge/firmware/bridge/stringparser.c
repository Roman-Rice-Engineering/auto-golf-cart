#include "stringparser.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

char buff[BUFFER_SIZE];
int ofst = 0;

void buffer_write(char val){
	buff[ofst] = val;
	ofst = ofst < BUFFER_SIZE - 1 ? ofst + 1 : 0;
}

char buffer_read(int index){
	index += 1;
	index = index % BUFFER_SIZE;

	if(index > ofst){
		index = index - BUFFER_SIZE;
	}
	return buff[ofst - index];
}

void buffer_print(void){
	for(int i = 0; i < BUFFER_SIZE; i++){
		if(i == ofst)
			printf("\x1b[1;33m");
		if(buff[i] == '\n')
			printf("[\\n]");
		else
			printf("[%c], ", buff[i]);
		if(i == ofst)
			printf("\x1b[0m");
		if(i % (int)sqrt(BUFFER_SIZE) == (int)sqrt(BUFFER_SIZE) - 1) 
			printf("\n");   
	}
	printf("\n");
}
bool buffer_get_command_split_and_top(int* top_index, int* split_index){
	*split_index = 0;
	bool found_split = false;
	for(int i = 0; i < BUFFER_SIZE; i++){
		char val = buffer_read(i); 

		if(val == '$'){
			*top_index = i;
			return true;
		}

		if(val == '='){
			if(found_split)
				return false;
			found_split = true;
			*split_index = i;
		}
	}
	return false;
}

//Returns a value 0-255
//Error returns -1
//Query command returns -2
int buffer_get_val_from_split_index(int split_index){
	if(split_index == 0)
		return -2;
	int out_val = 0;
	for(int i = split_index - 1; i > 0; i--){
		char current = buffer_read(i);
		if(!(current >= 48 && current <= 57))
			return -1;
		out_val *= 10;
		out_val += current - 48;
	}	
	if(out_val > 255)
		return -1;
	return out_val;
}

/*void print_buffer(char *buffer, unsigned long len){
  for(int i = 0; i < len; i++){
  Serial.print("[");
  if(buffer[i] == '\n')
  Serial.print("\\n");
  else
  Serial.print(buffer[i]);
  Serial.print("], ");
  if(i % (int)sqrt(len) == (int)sqrt(len) - 1) 
  Serial.println();
  }
  Serial.println();
  }*/

/*Static pattern identifying commands*/

bool buffer_check_matching_command(int top_index, int split_index, char *str){
	top_index = top_index - 1;
	if(top_index - split_index != strlen(str))
		return false;
	for(int i = 0; i < top_index - split_index; i++){
		if(tolower(str[i]) != tolower(buffer_read(top_index - i)))	
			return false;
	}
	return true;
}
