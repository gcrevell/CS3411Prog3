// -----------------------------------------------------------
// NAME : Gabriel Revells                    User ID: gcrevell
// DUE DATE : 11/19/2015
// PROGRAM ASSIGNMENT 3
// FILE NAME : WriteBits.c
// PROGRAM PURPOSE :
//    This file defines the functions defined in WriteBits.h
// -----------------------------------------------------------

#include "WriteBits.h"

void init(struct BitWriter* bw) {
	bw->count = 0;
	bw->c = '\0';
}

int writeBit(struct BitWriter* bw, int bit) {
	if (bit < 0 || bit > 1) {
		return -1;
	}
	
	bw->c = bw->c << 1;
	
	bw->c = bw->c ^ bit;
	
	bw->count++;
	
	if (bw->count == 8) {
		write(1, &bw->c, 1);
		bw->count = 0;
	}
	
	return 0;
}

void flush(struct BitWriter* bw) {
	if (bw->count == 0) {
		return;
	}
	
	while (bw->count < 7) {
		writeBit(bw, 0);
	}
	
	writeBit(bw, 0);
}
