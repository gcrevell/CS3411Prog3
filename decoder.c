// -----------------------------------------------------------
// NAME : Gabriel Revells                    User ID: gcrevell
// DUE DATE : 11/19/2015
// PROGRAM ASSIGNMENT 3
// FILE NAME : decoder.c
// PROGRAM PURPOSE :
//    This file decompresses a file given through stdin.
// -----------------------------------------------------------

#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "ReadBits.h"

// -----------------------------------------------------------
// FUNCTION  frequent :
//    This function reads the first 16 characters of the file
//    which are the frequent characters.
// PARAMETER USAGE :
//    char freqChar[] - The array of characters that are
//      frequent.
// -----------------------------------------------------------
void frequent(char freqChar[16]) {
	int cnt;
	char buf[16];
	
	cnt = read(0, buf, sizeof(buf));
	
	for (int i = 0; i < cnt; i++) {
		freqChar[i] = buf[i];
	}
}

// -----------------------------------------------------------
// FUNCTION  binaryToChar :
//    This function uses an int array of bits to create a
//    char.
// PARAMETER USAGE :
//    char bin[] - The array of bits that create the char.
// RETURN VALUE :
//    Returns the computed char.
// -----------------------------------------------------------
char binaryToChar(int bin[8]) {
	char c;
	
	for (int i = 0; i < 8; i++) {
		c = c << 1;
		c = c | bin[i];
	}
	
	return c;
}

// -----------------------------------------------------------
// FUNCTION  binary4ToInt :
//    This function converts an int array of 4 bits into an
//    int.
// PARAMETER USAGE :
//    char bin[] - The array of ints that are used to create
//      the int value.
// RETURN VALUE :
//    The int value created from the bits.
// -----------------------------------------------------------
int binary4ToInt(int bin[4]) {
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		ret = ((ret << 1) | bin[i]);
	}
	return ret;
}

// -----------------------------------------------------------
// FUNCTION  binary3ToInt :
//    This function converts an int array of 3 bits into an
//    int.
// PARAMETER USAGE :
//    int bin[] - The array of ints that are used to create
//      the int value.
// RETURN VALUE :
//    The int value created from the bits.
// -----------------------------------------------------------
int binary3ToInt(int bin[3]) {
	int ret = 0;
	for (int i = 0; i < 3; i++) {
		ret = ((ret << 1) | bin[i]);
	}
	return ret;
}

// -----------------------------------------------------------
// FUNCTION  main :
//    This function reads in a compressed file with stdin and
//    decompresses it.
// PARAMETER USAGE :
//    int argc - The number of arguments.
//    char* argv[] - The arguments.
// RETURN VALUE :
//    The main return value.
// -----------------------------------------------------------
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