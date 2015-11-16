#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void frequent(int ret[256]) {
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
		int max = 0;
		
		// Find value in ret that isn't already max.
		while (ret[max++] != 0);
		
		for (int j = 0; j < 256; j++) {
			if (frequency[max] < frequency[j]) {
				max = j;
			}
		}
		
		ret[max] = 1;
		frequency[max] = -1;
	}
}

int main(int argc, const char* argv[]) {
	int freq[256];
	char buf[1024];
	frequent(freq);
	
	for (int i = 0; i < 256; i++) {
		if (freq[i] == 1) {
			char c = (char)i;
			write(1, &c, sizeof(char));
		}
	}
	
	if (lseek(0, 0, SEEK_SET) == -1) {
		sprintf(buf, "Seeking of the source has failed.\n");
		write(2, buf, strlen(buf));
	}
	
	
}