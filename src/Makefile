# Define required macros here
SHELL = /bin/sh
PROJECT_NAME = progrmaze

.PHONY: all project check test clean

CFLAG = -Wall -g
CC = gcc
INCLUDES = ./main.c
LIBS = -lncurses

BUILD_DIR = ../build

project:
	${CC} ${CFLAGS} ${INCLUDES} -o ${BUILD_DIR}/${PROJECT_NAME} ${LIBS}

clean:
	rm -f *.o core *.core
