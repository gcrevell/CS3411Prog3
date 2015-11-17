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
