# Define required macros here
SHELL = /bin/sh
PROJECT_NAME = progrmaze

.PHONY: all project check test clean

all: clean project

CFLAG = -Wall -g
CC = gcc
INCLUDES = ./main.c
LIBS = -lncurses

BUILD_DIR = ../build

project:
	mkdir ${BUILD_DIR}
	cp -rf ./levels ${BUILD_DIR}
	${CC} ${CFLAGS} ${INCLUDES} -o ${BUILD_DIR}/${PROJECT_NAME} ${LIBS}

clean:
	rm -rf *.o core *.core ${BUILD_DIR}

install: clean project
	echo "Saving program to /usr/local/bin"
	sudo cp ${BUILD_DIR}/${PROJECT_NAME} /usr/local/bin
