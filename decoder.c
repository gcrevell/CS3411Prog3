#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "ReadBits.h"

void frequent(char freqChar[16]) {
	int cnt;
	char buf[16];
	
	cnt = read(0, buf, sizeof(buf));
	
	for (int i = 0; i < 16; i++) {
		freqChar[i] = buf[i];
	}
}

char binaryToChar(int bin[8]) {
	char c;
	
	for (int i = 0; i < 8; i++) {
		c = c << 1;
		c = c | bin[i];
	}
	
	return c;
}

int binary4ToInt(int bin[4]) {
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		ret = ((ret << 1) | bin[i]);
	}
	return ret;
}

int binary3ToInt(int bin[3]) {
	int ret = 0;
	for (int i = 0; i < 3; i++) {
		ret = ((ret << 1) | bin[i]);
	}
	return ret;
}

int main(int argc, const char* argv[]) {
	char freqChar[16];
	
	frequent(freqChar);
	
	int bit = 0;
	struct BitReader br;
	init(&br);
	
	while (readBit(&br, &bit) > 0) {
		if (bit == 1) {
			int bin[8];
			
			for (int i = 0; i < 8; i++) {
				readBit(&br, &bit);
				//printf("%d ", bit);
				bin[i] = bit;
			}
			
			char c = binaryToChar(bin);
			printf("%c", c);
		} else {
			readBit(&br, &bit);
			if (bit == 1) {
				// 3 bit repeat and 4 bit code
				int bin3[3];
				
				for (int i = 0; i < 3; i++) {
					readBit(&br, &bit);
					bin3[i] = bit;
				}
				
				int cnt = binary3ToInt(bin3) + 1;
				int bin4[4];
				
				for (int i = 0; i < 4; i++) {
					readBit(&br, &bit);
					bin4[i] = bit;
				}
				
				int val = binary4ToInt(bin4);
				char c = freqChar[val];
				
				for (int i = 0; i < cnt; i++) {
					printf("%c", c);
				}
			} else {
				// 4 bit code
				int bin4[4];
				
				for (int i = 0; i < 4; i++) {
					readBit(&br, &bit);
					bin4[i] = bit;
				}
				
				int val = binary4ToInt(bin4);
				if (val == 15) {
					// EOF
					return 0;
				}
				char c = freqChar[val];
				
				printf("%c", c);
			}
		}
	}
}