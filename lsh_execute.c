#include "fun.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int lsh_execute(char *line) {
	int x=0;
	int ifpipe = 0;
	while(line[x] != '\0') {
		if(line[x] == '|') {
			ifpipe = 1;
		}
		x++;
	}
	
	if(ifpipe) {
		char** pipe_commands = split_pipe(line);
		if(pipe_commands[1] != NULL) {
			int result = handle_pipe(pipe_commands);
			free(pipe_commands);
			return result;
		}
		free(pipe_commands);
	}
	
	else {
		char** args = lsh_split_line(line);
		
		if(args[0] == NULL) {
			free(args);
			return 1;
		}
		
		if(!handle_redirection(args)) {
			perror("redirection");
			return 0;
		}
		
		if(strcmp(args[0], "exit") == 0) {
			free(args);
			return 0;
		}
		
		if(args[0][0] == EOF) {
			printf("\n");
			free(args);
			return 0;
		}
		
		if(strcmp(args[0], "cd") == 0) {
			if(args[1] == NULL) {
				fprintf(stderr, "lsh: expected argument to \"cd\"\n");
			}
			else {
				if(chdir(args[1]) != 0) {
				perror("lsh");
				}
			}
			free(args);
			return 1;
		}
		
		int result = lsh_launch(args);
		free(args);
		return result;
	}
	return 0;
}
