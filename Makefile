CC=gcc
CFLAGS= -std=c99 -pedantic -Werror -Wall -Wextra

all:
		$(CC) $(FLAGS) -o tinyprintf src/tinyprintf.c

clean:
		rm tinyprintf
