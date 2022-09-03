// COPY.cpp : Defines the entry point for the console application.
//

#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100*1024
#define MAX_CHARACTER_LENGTH_FILE_NAME 1023


void HelpNote() {
	printf("\n--------------------------------------------------------------------------------\nHelp Note:\n\n");
	printf("A) Luu y:\n\n");
	printf("1) Neu trong nay ki hieu: <something>, thi khi nhap tham so, ban chi can nhap: something\n");
	printf("2) Khi nhap tham so, giua <something> va <something>, <something> va dau +, hay dau + va <something>, co 1 dau cach\n\n"); 
	printf("B) Chuong trinh nay co 3 chuc nang:\n\n");
	printf("1) Neu ban muon copy 1 file, va ghi de noi dung len 1 file khac, hay nhap:\n\n");
	printf("\t<Duong dan file goc> <Duong dan file dich>\n\n");
	printf("2) Neu ban muon copy 1 file vao 1 folder (file moi se co ten giong file goc), hay nhap:\n\n");
	printf("\t<Duong dan file goc> <Duong dan cua folder>\\\n\n");
	printf("3) Khi ban muon noi noi dung file thu 1 voi file thu 2, roi luu ket qua sau khi noi vao 1 file thu 3, hay nhap:\n\n");
	printf("\t<Duong dan file 1> + <Duong dan file 2> <Duong dan file 3>\n");
	printf("\n--------------------------------------------------------------------------------\n");
}

void COPY(FILE *InFile, FILE *OutFile) {
	char *buffer = new char[MAX_BUFFER_SIZE];
	int count;
	do {
		count = fread(buffer, 1, MAX_BUFFER_SIZE, InFile);
		fwrite(buffer, 1, count, OutFile);
	} while (count == MAX_BUFFER_SIZE);
	delete[]buffer;
}

void SourceFileName(char **agrv, char fileName[]) {
	int i = 0, sourceLength = strlen(agrv[1]) - 1;
	char tempChar;

	//Tim ra ten source file (Bi dao nguoc)

	do {
		fileName[i] = agrv[1][sourceLength - i];
		++i;
	} while ((agrv[1][sourceLength - i] != '\\') && (agrv[1][sourceLength - i] != '/'));
	fileName[i] = NULL;
	--i;

	//Dao nguoc lai ten source file

	for (int j = 0; j<=int(i / 2); ++j) {
		tempChar = fileName[i - j];
		fileName[i - j] = fileName[j];
		fileName[j] = tempChar;
	}
	fileName[++i] = NULL;
}

bool CloneCheck(char **agrv, FILE *InFile) {
	
	//Neu ki tu cuoi cung cua Tham So 2 la '\' => Co kha nang la COPY <file nguon> <folder dich>
	if (agrv[2][strlen(agrv[2]) - 1] == '\\') {
		char fileName[MAX_CHARACTER_LENGTH_FILE_NAME];
		char agrv2_temp[MAX_CHARACTER_LENGTH_FILE_NAME];
		SourceFileName(agrv, fileName);
		strcpy(agrv2_temp, agrv[2]);
		strcat(agrv2_temp, fileName);
		FILE *ptr2 = fopen(agrv2_temp, "wb+");

	//Neu dia chi cua folder khong dung (Tham so khong dung yeu cau)

		if (!ptr2) {
			return false;
		}
		else {

	//Neu dia chi cua folder dung yeu cau: => Thuc hien TH2

			COPY(InFile, ptr2);
			fclose(ptr2);
			return true;
		}
	}

	//Neu ki tu cuoi cung cua Tham so 2 khong phai '\'

	return false;
}

int TypeDecision(int agrc, char **agrv) {

	//Neu chi co 2 tham so => Nhieu kha nang la Help

	if (agrc == 2) {
		if ((agrv[1][0] == '/') && (agrv[1][1] == '?')) {
			HelpNote();
			return 0;
		}
	}
	else {

	//Neu co 3 tham so, kiem tra xem, la:
	//	TH0: Tham so khong dung yeu cau :
	//	TH1: COPY <file nguon> <file dich>
	//	TH2: COPY <file nguon> <folder dich>\


		if (agrc == 3) {
			FILE *fptr1 = fopen(agrv[1], "rb");

			//TH0: File nguon khong dung tham so:
			//Neu khong mo duoc file 1 => tham so khong hop le
			if (!fptr1) {
				return -1;
			}
			else {

			//TH1:
			// Neu tham so 2 khong phai la 1 folder

				if (CloneCheck(agrv,fptr1) == false) {

			// Thu mo file tham so 2

					FILE *fptr2 = fopen(agrv[2], "wb+");

			// Neu mo khong duoc file 2 => tham so khong hop le

					if (!fptr2) {
						fclose(fptr1);
						return -1;
					}

			// Neu mo duoc file 2 => chinh la TH1 (Da duoc xu li trong ham CloneCheck)

					else {
						COPY(fptr1, fptr2);
						fclose(fptr1);
						fclose(fptr2);
						return 1;
					}
				}
				else {

			//TH2: CloneCheck==True thi thuc hien check + execute TH2 trong ham CloneCheck.

						return 2;
					
				}
			}
		}
		else {

	//Neu co 4 tham so, kiem tra:
	//	TH0: Tham so khong dung yeu cau :
	//	TH3: COPY <file 1> + <file 2> <file dich>

			if (agrc == 5) {

			//Neu khong mo duoc 1 trong 3 file => TH0: Tham so khong dung yeu cau

				FILE *fptr1 = fopen(agrv[1], "rb");
				if (!fptr1) return -1;
				if (agrv[2][0] != '+') { 
					return -1; 
				}
				FILE *fptr2 = fopen(agrv[3], "rb");
				if (!fptr2) { 
					fclose(fptr1);
					return -1; 
				}
				FILE *fptr3 = fopen(agrv[4], "wb+");
				if (!fptr3) {
					fclose(fptr1);
					fclose(fptr2);
					return -1;
				}
				else {

			//TH3:
					COPY(fptr1, fptr3);
					COPY(fptr2, fptr3);
					fclose(fptr1);
					fclose(fptr2);
					fclose(fptr3);
					return 3;
				}
			}
			else {

	//Neu khong thoa man bat ki truong hop nao ke tren:
	//=>   TH0: Tham so khong dung yeu cau

				return -1;
			}
		}
	}
}

int main(int agrc, char **agrv)
{
	int type = -1;
	printf("Ban co the dung ki tu \"/?\" de mo Help Note\n");
	type=TypeDecision(agrc, agrv);
	if (type == -1) {
		printf("Tham so khong hop le! ");
	}
	else {
		printf("Da thuc hien xong !\n");
	}
	return 0;
}

