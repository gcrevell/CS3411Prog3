.SUFFIXES: .c .o
CC = gcc
EXEC = encoder decoder
CCFLAGS = -Wall -std=c99
OBJS = encoder.o decoder.o

all: encoder decoder

encoder: encoder.c
	${CC} ${CCFLAGS} -lm -o encoder encoder.c

decoder: decoder.c
	${CC} ${CCFLAGS} -lm -o decoder decoder.c

.c.o:
	${CC} ${CCFLAGS} -c $<
    
clean:
	rm -f ${EXEC} ${OBJS}

copy.o: copy.c