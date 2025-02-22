#include "fun.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int lsh_launch(char **args) {

	pid_t pid, wpid;
	int status;
	int isBackground=is_background(args);
	
	
	pid = fork();
	if(pid == 0) {
		if(execvp(args[0], args) == -1) {
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	}
	if(pid < 0) {
		perror("lsh");
		exit(EXIT_FAILURE);
	}
	else {
		if(!isBackground) {
			do {
				wpid = waitpid(pid, &status, WUNTRACED);
			} while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		else {
			printf("Proces %d działa w tle.\n", pid);
		}
	}
	
	return 1;
}
