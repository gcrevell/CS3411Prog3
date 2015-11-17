#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#ifndef readbits_h
#define readbits_h

struct BitReader {
	int count;
	char c;
};

int init(struct BitReader* br);
int readBit(struct BitReader* br, int* read);


#endif
