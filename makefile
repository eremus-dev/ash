
test: test.c ashell.o
 	gcc -Wall -Werror -o test ./test.c ./ashell.o

ashell: ashell.c
	gcc -Wall -Werror -g ashell.c

clean:
	rm -rf *.o