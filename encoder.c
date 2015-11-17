#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>
#include "WriteBits.h"

void frequent(int ret[256], char freqChar[16]) {
	int frequency[256];
	char buf[1024];
	
	for (int i = 0; i < 256; i++) {
		frequency[i] = 0;
		ret[i] = 0;
	}
	
	int cnt;
	
	while ((cnt = read(0, buf, sizeof(buf))) > 0) {
		// Read in all characters in SIN
		
		for (int i = 0; i < cnt; i++) {
			frequency[(int)buf[i]]++;
		}
	}
	
	for (int i = 0; i < 15; i++) {
		int max = 1;
		
		// Find value in ret that isn't already max.
		while (ret[max++] != 0);
		
		for (int j = 1; j < 256; j++) {
			if (frequency[max] < frequency[j]) {
				max = j;
			}
		}
		
		if (frequency[max] == 0) {
			break;
		}
		
		ret[max] = 1;
		frequency[max] = -1;
	}
	
	int index = 0;
	for (int i = 0; i < 256; i++) {
		if (ret[i] == 1) {
			freqChar[index++] = i;
		}
	}
	
	for (; index < 15;) {
		freqChar[index++] = 0;
	}
	
	freqChar[15] = 255;
}

void getFourBitInt(int in, int ret[4]) {
	for (int i = 3; i >= 0; i--) {
		ret[i] = in & 1;
		in = in >> 1;
	}
}

void getThreeBitInt(int in, int ret[3]) {
	for (int i = 2; i >= 0; i--) {
		ret[i] = in & 1;
		in = in >> 1;
	}
}

void charToBinary(char c, int ret[8]) {
	for (int i = 7; i >= 0; i--) {
		ret[i] = c & 1;
		c = c >> 1;
	}
}

int main(int argc, const char* argv[]) {
	int freq[256];
	char buf[1024];
	char freqChars[16];
	frequent(freq, freqChars);
	
	for (int i = 0; i < 16; i++) {
		write(1, &freqChars[i], sizeof(char));
	}
	
	if (lseek(0, 0, SEEK_SET) == -1) {
		sprintf(buf, "Seeking of the source has failed.\n");
		write(2, buf, strlen(buf));
	}
	
	struct BitWriter bw;
	init(&bw);
	
	int cnt;
	while ((cnt = read(0, buf, sizeof(buf))) > 0) {
		// Read in all characters in SIN
		
		for (int i = 0; i < cnt; i++) {
			//printf("\n\n\n\n");
			//printf("looking at char %c:\n", buf[i]);
			if (freq[(int)buf[i]] == 1) {
				// Is a frequent char
				//printf("It is frequent\n");
				writeBit(&bw, 0);
				
				// Count repeat times
				int j;
				int origCnt = cnt;
				for (j = i + 1; j - i < 8 && buf[j % origCnt] == buf[i]; j++) {
					// Still equal and counting
					if (j == cnt - 1) {
						// J passed end. Get more input
						cnt = read(0, buf, sizeof(buf));
						if (cnt == 0) {
							// No more input
							break;
						}
					}
				}
				
				int tmp = i;
				i = j - 1;
				// Set j to number of repeated times
				j = j - tmp;
				
				if (j == 1) {
					// Just one frequent char
					//printf("It does not repeat.\n");
					writeBit(&bw, 0);
				} else {
					// More than one. Print count
					//printf("It does repeat %d times\n", j);
					writeBit(&bw, 1);
					int bits[3];
					
					getThreeBitInt(j - 1, bits);
					
					for (int k = 0; k < 3; k++) {
						writeBit(&bw, bits[k]);
					}
				}
				
				// Write frequent char number
				for (int k = 0; k < 15; k++) {
					if (freqChars[k] == buf[i]) {
						int bits[4];
						
						getFourBitInt(k, bits);
						
						for (int l = 0; l < 4; l++) {
							writeBit(&bw, bits[l]);
						}
						break;
					}
				}
			} else {
				// Not a frequent character
				//printf("It is not frequent\n");
				writeBit(&bw, 1);
				
				int bits[8];
				charToBinary(buf[i], bits);
				
				for (int k = 0; k < 8; k++) {
					writeBit(&bw, bits[k]);
				}
			}
		}
	}
	
	writeBit(&bw, 0);
	writeBit(&bw, 0);
	writeBit(&bw, 1);
	writeBit(&bw, 1);
	writeBit(&bw, 1);
	writeBit(&bw, 1);
	
	flush(&bw);
}