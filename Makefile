CFLAGS=-g -O0 -ansi -pedantic-errors -Wall -Werror

EXECUTABLES=2020/day01/ex1 \
            2020/day01/ex2 \
            2020/day02/ex1 \
            2020/day02/ex2 \
            2020/day03/ex1 \
            2020/day03/ex2 \
            2020/day04/ex1 \
            2020/day04/ex2 \
            2020/day05/ex1 \
            2020/day05/ex2 \
            2020/day06/ex1 \
            2020/day06/ex2 \
            2020/day07/ex1 \
            2020/day07/ex2

all: ${EXECUTABLES}

clean:
	rm -f ${EXECUTABLES}
