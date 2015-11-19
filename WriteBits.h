// -----------------------------------------------------------
// NAME : Gabriel Revells                    User ID: gcrevell
// DUE DATE : 11/19/2015
// PROGRAM ASSIGNMENT 3
// FILE NAME : WriteBits.h
// PROGRAM PURPOSE :
//    This file defines the functions and struct needed to
//    write to stdout bit by bit.
// -----------------------------------------------------------

#include <unistd.h>

#ifndef writebits_h
#define writebits_h

struct BitWriter {
	int count;
	char c;
};

// -----------------------------------------------------------
// FUNCTION  init :
//    This function initalizes the given BitWriter struct
//    setting the values to 0.
// PARAMETER USAGE :
//    struct BitWriter* bw - The given BitWriter to init.
// -----------------------------------------------------------
void init(struct BitWriter* bw);

// -----------------------------------------------------------
// FUNCTION  writeBit :
//    This function writes a single bit to the given BitWriter
//    and writes the output to stdout if the byte is full.
// PARAMETER USAGE :
//    struct BitWriter* bw - The given BitWriter to write a
//      bit to.
//    int bit - THh bit, 1 or 0, to write.
// RETURN VALUE :
//    Returns -1 if the bit is not 1 or 0, 0 otherwise.
// -----------------------------------------------------------
int writeBit(struct BitWriter* bw, int bit);

// -----------------------------------------------------------
// FUNCTION  flush :
//    This function pads the remaining bits with 0 and writes
//    the bits to stdout.
// PARAMETER USAGE :
//    struct BitWriter* bw - The BitWriter to flush.
// -----------------------------------------------------------
void flush(struct BitWriter* bw);

#endif
