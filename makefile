
all: main.c parser.o ashell.o utilities.o
	gcc -Wall -Werror ashell.o main.c parser.o utilities.o -o ashell 

test: test.o ashell.o parser.o utilities.o
	gcc -Wall -Werror ashell.o test.o parser.o utilities.o -o test 

testm: test.c
	gcc -Wall -Werror -c test.c

ashell: ashell.c
	gcc -Wall -Werror -c ashell.c

utilities: utilities.c utilities.h
	gcc -Wall -Werror -c utilities.c

parser: parser.c parser.h
	gcc -Wall -Werror -c parser.c

clean:
	rm -rf *.o