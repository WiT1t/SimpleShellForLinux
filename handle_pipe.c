#include "fun.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int handle_pipe(char **commands) {
	
	int pipefd[2];
	pid_t pid;
	int fd_in = 0;
	while(*commands != NULL) {
		pipe(pipefd);
		
		if((pid = fork()) == -1) {
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(pid == 0) {
			char **args = lsh_split_line(*commands);
			if(!handle_redirection(args)){
				perror("redirection");
				exit(EXIT_FAILURE);
			}
			if(fd_in != 0) {
				if(dup2(fd_in, 0) == -1) {
					perror("dup2 input");
					exit(EXIT_FAILURE);
				}
			}
			if(*(commands + 1) != NULL) {
				if(dup2(pipefd[1], 1) == -1) {
					perror("dup2 output");
					exit(EXIT_FAILURE);
				}
			}
			close(pipefd[0]);
			close(pipefd[1]);
		
			if((execvp(args[0], args)) == -1) {
				perror("execvp");
				exit(EXIT_FAILURE);
			}
			free(args);
		}
		else {
			waitpid(pid,NULL,0);
			close(pipefd[1]);
			fd_in = pipefd[0];
			commands++;
		}	
	}
	return 1;
}
