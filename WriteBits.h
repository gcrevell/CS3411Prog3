#include <unistd.h>

#ifndef writebits_h
#define writebits_h

struct BitWriter {
	int count;
	char c;
};

void init(struct BitWriter* bw);
int writeBit(struct BitWriter* bw, int bit);
void flush(struct BitWriter* bw);

#endif
