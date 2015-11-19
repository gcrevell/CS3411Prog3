// -----------------------------------------------------------
// NAME : Gabriel Revells                    User ID: gcrevell
// DUE DATE : 11/19/2015
// PROGRAM ASSIGNMENT 3
// FILE NAME : ReadBits.c
// PROGRAM PURPOSE :
//    This file defines the functions and struct needed to
//    read bits from stdin.
// -----------------------------------------------------------

#include "ReadBits.h"
#include <stdio.h>

int init(struct BitReader* br) {
	br->count = 0;
	return read(0, &br->c, sizeof(char));
}

int readBit(struct BitReader* br, int* read) {
	*read = ((br->c >> (7 - br->count)) & 1);
	
	br->count++;
	
	if (br->count == 8) {
		return init(br);
	}
	return 1;
}
