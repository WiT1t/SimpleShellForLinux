#include "fun.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>

#define LSH_TOK_BUFSIZE 64
char** split_pipe(char* line) {
	
	int bufsize = LSH_TOK_BUFSIZE;
	int position = 0;
	char **tokens = malloc(sizeof(char*) * bufsize);
	char *token = NULL;
	bool inquotes = false;
	char *current = line;
	
	if(!tokens) {
		fprintf(stderr, "lsh: allocation error.\n");
		exit(EXIT_FAILURE);
	}
	
	while(*current != '\0') {
		if(!token && *current != '|') {
			token = current;
		}
		if(*current == '"') {
			inquotes = !inquotes;
		}
		else if(*current == '|' && inquotes == false) {
			*current = '\0';
			if(token) {
				tokens[position] = token;
				position++;
				if(position >= bufsize) {
					bufsize += LSH_TOK_BUFSIZE;
					tokens = realloc(tokens, bufsize * sizeof(char*));
					if(!tokens) {
						fprintf(stderr, "lsh: allocation error.\n");
						exit(EXIT_FAILURE);
					}
				}
				token = NULL;
			}
		}
		current++;
	}
	if(token) {
		tokens[position] = token;
		position++;
		if(position >= bufsize) {
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens) {
				fprintf(stderr, "lsh: allocation error.\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	tokens[position] = NULL;
	
	return tokens;
}
