#include "fun.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define LSH_RL_BUFSIZE 1024
char* lsh_read_line() {
	int bufsize = LSH_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;
	
	if(!buffer) {
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	while(1) {
		c = getchar();
		if(position == 0 && c == EOF) {
			buffer[0] = EOF;
			buffer[1] ='\0';
			return buffer;
		}
		if(c == EOF || c == '\n') {
			buffer[position] ='\0';
			return buffer;
		}
		else {
			buffer[position] = c;
		}
		position++;
		
		if(position > bufsize) {
			bufsize += LSH_RL_BUFSIZE;
			buffer = realloc(buffer, sizeof(char) * bufsize);
			if(!buffer) {
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
