
all: test.o ashell.o
	gcc -Wall -Werror ashell.o test.c -o test 

testm: test.c
	gcc -Wall -Werror -c test.c

ashell: ashell.c
	gcc -Wall -Werror -c ashell.c

clean:
	rm -rf *.o