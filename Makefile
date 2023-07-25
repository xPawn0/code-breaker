CC=gcc
CFLAGS=-Wall -Wextra -I./libs/argparse/ -I./src/
EXECFILE=code-breaker
FULLEXECPATH=bin/code-breaker
SOURCES=$(wildcard libs/*/*.c src/*.c)


build:
	${CC} ${CFLAGS} code-breaker.c ${SOURCES} -o ${FULLEXECPATH}

binary: build
	cp ${FULLEXECPATH} ~/.local/bin/cbreaker

run: build
	./${FULLEXECPATH}

remove:
	rm -f bin/* ~/.local/bin/cbreaker
