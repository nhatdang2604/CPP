#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define BUF_SIZE 4*1024

void copyFile(char *inF, char *outF) {
	FILE *ptrIn = fopen(inF, "rb");
	FILE *ptrOut = fopen(outF, "wb");
	if (!ptrIn || !ptrOut) {
		return;
	}
	char buf[BUF_SIZE];
	int count;
	do {
		count = fread(buf, 1, BUF_SIZE, ptrIn);
		fwrite(buf, 1, count, ptrOut);
	} while (count == BUF_SIZE);
	fclose(ptrIn);
	fclose(ptrOut);
}

int main()

{
	copyFile("textIn.txt", "textOut.txt");
	return 0;
}