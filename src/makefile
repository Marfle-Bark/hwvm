COMPILER = gcc
SOURCES = main.c
FLAGS = -Wall -Wextra -g -std=c1x
OUTPUT = hwvm.out

all: build clean

build:
	${COMPILER} ${SOURCES} ${FLAGS} -o ${OUTPUT}
	chmod a+x hwvm.out
	mv hwvm.out ../bin/hwvm.out

clean:
	rm -rf *.o build
	clear
	ls