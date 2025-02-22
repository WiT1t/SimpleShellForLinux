all: main

main: main.o lsh_read_line.o lsh_split_line.o lsh_loop.o lsh_launch.o lsh_execute.o is_background.o handle_pipe.o split_pipe.o handle_redirection.o
	clang -o main main.o lsh_read_line.o lsh_split_line.o lsh_loop.o lsh_launch.o lsh_execute.o is_background.o handle_pipe.o split_pipe.o handle_redirection.o
	
main.o: main.c
	clang -c main.c

lsh_read_line.o: lsh_read_line.c
	clang -c lsh_read_line.c

lsh_split_line.o: lsh_split_line.c
	clang -c lsh_split_line.c
	
lsh_loop.o: lsh_loop.c
	clang -c lsh_loop.c
	
lsh_launch.o: lsh_launch.c
	clang -c lsh_launch.c

lsh_execute.o: lsh_execute.c
	clang -c lsh_execute.c
	
is_background.o: is_background.c
	clang -c is_background.c
	
handle_pipe.o: handle_pipe.c
	clang -c handle_pipe.c
	
split_pipe.o: split_pipe.c
	clang -c split_pipe.c
	
handle_redirection.o: handle_redirection.c
	clang -c handle_redirection.c
	
clean: 
	rm -f main *.o *~
