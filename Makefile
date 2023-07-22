CC=gcc
CFLAGS=-Wall -Wextra -I./libs/argparse/
EXECFILE=code-breaker
FULLEXECPATH=bin/code-breaker
LIBS=$(wildcard libs/*/*.c)


build:
	${CC} ${CFLAGS} code-breaker.c ${LIBS} -o ${FULLEXECPATH}

binary: build
	cp ${FULLEXECPATH} ~/.local/bin/cbreaker

run: build
	./${FULLEXECPATH}

remove:
	rm -f bin/* ~/.local/bin/cbreaker
