
all: test.o ashell.o parser.o
	gcc -Wall -Werror ashell.o test.o parser.o -o test 

testm: test.c
	gcc -Wall -Werror -c test.c

ashell: ashell.c
	gcc -Wall -Werror -c ashell.c

parser: parser.c parser.h
	gcc -Wall -Werror -c parser.c

clean:
	rm -rf *.o