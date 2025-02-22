#include "fun.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

int handle_redirection(char **args) {
	int i=0;
	int fd;
	char *infile=NULL;
	char *outfile=NULL;
	char *errfile=NULL;
	
	while(args[i] != NULL) {
		if(strcmp(args[i], "<")==0) {
			infile = args[i+1];
			args[i] = NULL;
			break;
		}
		i++;
	}
	
	i=0;
	while(args[i] != NULL) {
		if(strcmp(args[i], ">")==0) {
			outfile = args[i+1];
			args[i] = NULL;
			break;
		}
		i++;
	}
	
	i=0;
	while(args[i] != NULL) {
		if(strcmp(args[i], "2>")==0) {
			errfile = args[i+1];
			args[i] = NULL;
			break;
		}
		i++;
	}
	
	if(infile != NULL) {
		fd = open(infile, O_RDONLY);
		if(fd == -1) {
			perror("open input file");
			return 0;
		}
		if(dup2(fd,0) == -1) {
			perror("dup2 input");
			close(fd);
			return 0;
		}
		close(fd);
	}
	
	if(outfile != NULL) {
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd == -1) {
			perror("open output file");
			return 0;
		}
		if(dup2(fd,1) == -1) {
			perror("dup2 output");
			close(fd);
			return 0;
		}
		close(fd);
	}
	
	if(errfile != NULL) {
		fd = open(errfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd == -1) {
			perror("open error file");
			return 0;
		}
		if(dup2(fd,2) == -1) {
			perror("dup2 output");
			close(fd);
			return 0;
		}
		close(fd);
	}
	
	return 1;
}

