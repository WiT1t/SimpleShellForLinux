#include "fun.h"
#include<stdio.h>

int is_background(char **args) {
	
	int i=0;
	int ans = 0;
	while(args[i] != NULL) {i++;}
	i=i-1;
	if(i>0 && args[i][0]=='&' && args[i][1]=='\0') {
		ans = 1;
	}
	if(ans) {
		args[i] = NULL;
	}
	
	return ans;
}
