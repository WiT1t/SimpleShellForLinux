#include "fun.h"
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

void lsh_loop() {
	char *line;
	int status;
	
	
	
	int status1;
	pid_t pid;
		
	do {
		int saved_stdout = dup(STDOUT_FILENO);
		int saved_stdin = dup(STDIN_FILENO);
		printf("lsh > ");
		
		line = lsh_read_line();
		status = lsh_execute(line);
		
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		
		close(saved_stdin);
		close(saved_stdout);
		free(line);
		
		while((pid = waitpid(-1,&status1,WNOHANG))>0) {
			printf("Proces %d zakończony.\n", pid);
		}
	} while(status);
}
