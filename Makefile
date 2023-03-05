CC=gcc
CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra -lcriterion

all:
		$(CC) $(FLAGS) -o tinyprintf src/tinyprintf.c

check:
		$(CC) $(CFLAGS) -o test tests/tests.c
		./test

clean:
		rm test tinyprintf
