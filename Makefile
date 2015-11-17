.SUFFIXES: .c .o
CC = gcc
EXEC = encoder decoder
CCFLAGS = -Wall -std=c99
OBJS = encoder.o decoder.o WriteBits.o

all: encoder decoder
	

encoder: WriteBits.c encoder.c
	${CC} ${CCFLAGS} -lm -o encoder encoder.c WriteBits.c

decoder: decoder.c ReadBits.c
	${CC} ${CCFLAGS} -lm -o decoder decoder.c ReadBits.c

.c.o:
	${CC} ${CCFLAGS} -c $<
    
clean:
	rm -r -f ${EXEC} ${OBJS} *.dSYM

copy.o: copy.c