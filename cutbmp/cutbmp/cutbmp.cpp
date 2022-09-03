// cutbmp.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "windows.h"
using namespace std;

#pragma pack(1)

#define MAX_CHARACTER 255

struct Color {
	char blue;
	char green;
	char red;
};

struct Header {
	char sign[2];
	uint32_t sizeOnDisk;
	uint16_t specific1;
	uint16_t specific2;
	uint32_t dataOffset;
};

struct DIB {
	uint32_t DIBSize;
	uint32_t width;
	uint32_t height;
	uint16_t numberOfColorPlanes;
	uint16_t numberOfBitsPerPixel;
	uint32_t compressMethod;
	uint32_t sizeOfPixelArray;
	uint32_t horizontalResolution;
	uint32_t verticalResolution;
	uint32_t numberOfColors;
	uint32_t numberOfImportantColors;
};

struct PixelArray {
	char *rawByte;
	uint32_t rawByteSize;
	uint32_t lineSize;
	uint32_t paddingSize;
	Color **pixels;
};

struct BMP {
	Header header;
	DIB dib;
	PixelArray pixelArray;
};


bool BMP_Valid(BMP sample) {
	if (sample.header.sign[0] != 'B' || sample.header.sign[1] != 'M') {
		return false;
	}
	if (sample.dib.numberOfBitsPerPixel < 24) {
		return false;
	}
	return true;
}

bool readInput(int agrc, char **agrv, int &horizontalSlide, int &verticalSlide) {
	char temp[3], duplicate_check;
	if (agrc == 4) {
		strcpy(temp, agrv[2]);
		if (temp[0] == '-') {
			if (temp[1] == 'h') {
				horizontalSlide = atoi(agrv[3]);
			}
			else {
				if (temp[1] == 'w') {
					verticalSlide = atoi(agrv[3]);
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}
	else {
		if (agrc == 6) {
			strcpy(temp, agrv[2]);
			if (temp[0] == '-') {
				if (temp[1] == 'h') {
					duplicate_check = 'h';
					horizontalSlide = atoi(agrv[3]);
				}
				else {
					if (temp[1]=='w') {
						duplicate_check = 'w';
						verticalSlide = atoi(agrv[3]);
					}
					else {
						return false;
					}
				}
			}
			else {
				return false;
			}
			
			strcpy(temp, agrv[4]);
			if (temp[0] == '-') {
				if (temp[1] == 'h') {
					if (duplicate_check == temp[1]) return false;
					horizontalSlide = atoi(agrv[5]);
				}
				else {
					if (temp[1] == 'w') {
						if (duplicate_check == temp[1]) return false;
						verticalSlide = atoi(agrv[5]);
					}
					else {
						return false;
					}
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return true;
}

bool readBMPSource(char *imageSources, FILE *&f) {
	f = fopen(imageSources, "rb");
	if (!f) {
		cout << "Mo file BMP that bai!\n";
		return false;
	}
	return true;
}

void readHeader(BMP &sample, FILE *f) {
	fseek(f, 0, SEEK_SET);
	fread(&sample.header, sizeof(Header), 1, f);
}

void readDIB(BMP &sample, FILE *f) {
	fread(&sample.dib, sizeof(DIB), 1, f);
}

void initPixel(BMP &sample) {
	sample.pixelArray.pixels = new Color*[sample.dib.height];
	for (unsigned int i = 0; i < sample.dib.height; ++i) {
		sample.pixelArray.pixels[sample.dib.height - i - 1] = (Color *)(sample.pixelArray.rawByte + sample.pixelArray.lineSize*i);
	}
}


void readPixelArray(BMP &sample, FILE *f) {
	int widthSize = sample.dib.width*sample.dib.numberOfBitsPerPixel / 8;
	sample.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
	sample.pixelArray.lineSize = widthSize + sample.pixelArray.paddingSize;
	sample.pixelArray.rawByteSize = sample.pixelArray.lineSize*sample.dib.height;
	sample.pixelArray.rawByte = new char[sample.pixelArray.rawByteSize];

	fseek(f, sample.header.dataOffset, SEEK_SET);
	fread(sample.pixelArray.rawByte, sample.pixelArray.rawByteSize, 1, f);
	initPixel(sample);
}


void release(BMP &sample, FILE *f, char *imageName) {
	fclose(f);
	delete[]sample.pixelArray.rawByte;
	delete[]sample.pixelArray.pixels;
	delete[]imageName;
}

bool slideValidCheck(BMP sample, int horizontalSlide, int verticalSlide) {
	if ((sample.dib.height % horizontalSlide != 0) || (sample.dib.width%verticalSlide != 0)) {
		cout << "Khong the cat thanh cac phan bang nhau !\n";
		return false;
	}
	return true;
}

void nameEachPartGenerator(int index, char *imageNameEachPart, char* imageSources) {
	char buffer[4];
	strcpy(imageNameEachPart, imageSources);
	int i = strlen(imageNameEachPart) - 1;
	do {
		--i;
	} while (imageNameEachPart[i] != '.');
	imageNameEachPart[i] = '_';
	imageNameEachPart[++i] = 'p';
	imageNameEachPart[++i] = 'a';
	imageNameEachPart[++i] = 'r';
	imageNameEachPart[++i] = 't';
	imageNameEachPart[++i] = NULL;
	itoa(index, buffer, 10);
	strcat(imageNameEachPart, buffer);
	i = i + strlen(buffer);
	imageNameEachPart[i] = '.';
	imageNameEachPart[++i] = 'b';
	imageNameEachPart[++i] = 'm';
	imageNameEachPart[++i] = 'p';
	imageNameEachPart[++i] = NULL;
}

bool openFile(FILE *&fptr, char *imageNameEachPart) {
	fptr = fopen(imageNameEachPart, "wb+");
	if (!fptr) {
		cout << "Cat anh khong thanh cong\n";
		return false;
	}
	return true;
}

void createClone(FILE *f, BMP sample, FILE *fptr, BMP &cloning, int horizontalSlide, int verticalSlide) {
	strcpy(cloning.header.sign, sample.header.sign);
	cloning.header.specific1 = NULL;
	cloning.header.specific2 = NULL;
	cloning.header.dataOffset = 54;
	//cloning.header.sizeOnDisk =
	cloning.dib.DIBSize = 40;
	cloning.dib.height = sample.dib.height / horizontalSlide;
	cloning.dib.width = sample.dib.width / verticalSlide;
	cloning.dib.numberOfColorPlanes = sample.dib.numberOfColorPlanes;
	cloning.dib.numberOfBitsPerPixel = sample.dib.numberOfBitsPerPixel;
	cloning.dib.compressMethod = sample.dib.compressMethod;
	//cloning.dib.sizeOfPixelArray =
	cloning.dib.horizontalResolution = 0;//sample.dib.horizontalResolution;
	cloning.dib.verticalResolution = 0;//sample.dib.verticalResolution;
	cloning.dib.numberOfColors = sample.dib.numberOfColors;
	cloning.dib.numberOfImportantColors = sample.dib.numberOfImportantColors;
	
	int widthSize = cloning.dib.width*cloning.dib.numberOfBitsPerPixel / 8;
	cloning.pixelArray.paddingSize = (4 - (widthSize % 4)) % 4;
	cloning.pixelArray.lineSize = widthSize + cloning.pixelArray.paddingSize;
	cloning.pixelArray.rawByteSize = cloning.pixelArray.lineSize*cloning.dib.height;
	//cloning.pixelArray.rawByte = new char[cloning.pixelArray.rawByteSize];
	
	cloning.header.sizeOnDisk = 54 + cloning.pixelArray.rawByteSize;
	cloning.dib.sizeOfPixelArray = cloning.pixelArray.rawByteSize;
	//cloning.pixelArray.pixels = new Color *[cloning.dib.height];
	
}


void Slide(BMP sample, FILE *f, char *imageSources, char *imageNameEachPart, int horizontalSlide, int verticalSlide) {
	BMP cloning;
	FILE *fptr;
	char *buffer = NULL;
	int rowCount = sample.dib.height / horizontalSlide;
	//int colCount = sample.dib.width / verticalSlide;
	int u = 0, v = 0;
	for (int t = 0; t < horizontalSlide*verticalSlide; ++t) {
		nameEachPartGenerator(t + 1, imageNameEachPart, imageSources);
		if (u == verticalSlide) {
			u = 0; ++v;
		}
		if (openFile(fptr, imageNameEachPart)) {
			createClone(f, sample, fptr, cloning, horizontalSlide, verticalSlide);
			if (cloning.pixelArray.pixels) {
				fseek(fptr, 0, SEEK_SET);
				fwrite(&cloning.header, sizeof(Header), 1, fptr);
				fwrite(&cloning.dib, sizeof(DIB), 1, fptr);
				buffer = new char[cloning.pixelArray.lineSize];
				if (buffer) {
					for (unsigned int i = 0; i < cloning.dib.height; ++i) {
						fseek(f, 54  +(v*rowCount+i)*sample.pixelArray.lineSize + u*(cloning.pixelArray.lineSize), SEEK_SET);
						fread(buffer, cloning.pixelArray.lineSize - cloning.pixelArray.paddingSize, 1, f);
						for (unsigned int k = 0; k < cloning.pixelArray.paddingSize; ++k) {
							buffer[cloning.pixelArray.lineSize - cloning.pixelArray.paddingSize + k] = NULL;
						}
						fwrite(buffer, cloning.pixelArray.lineSize, 1, fptr);
					}
					++u;
					delete[]buffer;
					buffer = NULL;
				}
			}
		}
	}
}

int readBMP(BMP &sample, FILE *f, char *imageSources, char *imageNameEachPart, int horizontalSlide, int verticalSlide) {
	readHeader(sample, f);
	if (!BMP_Valid(sample)) {
		cout << "Day khong phai la file BMP hoac BMP co bit/pixel < 24\n";
		return 0;
	}
	readDIB(sample, f);
	readPixelArray(sample, f);
	if (slideValidCheck(sample, horizontalSlide, verticalSlide)) {
		Slide(sample, f, imageSources, imageNameEachPart, horizontalSlide, verticalSlide);
	}
	else {
		return 0;
	}
	release(sample, f, imageNameEachPart);
	return 1;
}

int main(int agrc, char **agrv)
{
	int horizontalSlide = 1, verticalSlide = 1;
	char *imageSources = strdup(agrv[1]), *imageNameEachPart=new char[strlen(imageSources)+10];
	BMP sample;
	FILE *fptr;
	if (!readInput(agrc,agrv,horizontalSlide,verticalSlide)) {
		cout << "Input khong hop le !\n";
	}
	else {
		if (!readBMPSource(imageSources, fptr)) {
			cout << "Khong the mo duoc anh BMP\n";
		}
		else {
			readBMP(sample, fptr, imageSources, imageNameEachPart, horizontalSlide, verticalSlide);
		}
	}
	return 0;
}

