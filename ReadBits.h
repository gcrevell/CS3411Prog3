// -----------------------------------------------------------
// NAME : Gabriel Revells                    User ID: gcrevell
// DUE DATE : 11/19/2015
// PROGRAM ASSIGNMENT 3
// FILE NAME : ReadBits.h
// PROGRAM PURPOSE :
//    This file defines the functions and struct needed to
//    read bits from stdin.
// -----------------------------------------------------------

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#ifndef readbits_h
#define readbits_h

struct BitReader {
	int count;
	char c;
};

// -----------------------------------------------------------
// FUNCTION  init :
//    This function initalizes the given BitReader struct
//    setting the count to 0 and reads in a char from stdin.
// PARAMETER USAGE :
//    struct BitReader* br - The given BitReader to init.
// RETURN VALUE :
//    This function returns 1 if there was a character to
//    read, 0 otherwise.
// -----------------------------------------------------------
int init(struct BitReader* br);

// -----------------------------------------------------------
// FUNCTION  readBit :
//    This function reads in a single bit and, if the full
//    char is used it reads in another char.
// PARAMETER USAGE :
//    struct BitReader* br - The given BitReader to read from.
// RETURN VALUE :
//    This function returns 1 if there are more bits to
//    read, 0 otherwise.
// -----------------------------------------------------------
int readBit(struct BitReader* br, int* read);


#endif
