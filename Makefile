CFLAGS=-g -O0 -ansi -pedantic-errors -Wall -Werror

EXECUTABLES=2020/day01/ex1 \
            2020/day01/ex2

all: ${EXECUTABLES}

clean:
	rm -f ${EXECUTABLES}
