char** lsh_split_line(char* line);
char* lsh_read_line();
void lsh_loop();
int lsh_launch(char **args);
int lsh_execute(char *line);
int is_background(char **args);
int handle_pipe(char **commands);
char** split_pipe(char* line);
int handle_redirection(char **args);
