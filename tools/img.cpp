#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;

typedef struct tagBITMAPINFOHEADER{
	DWORD biSize;
	long biWidth;
	long biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	long biXPelsPerMeter;
	long biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;

int ReadBmp(const char* szFileName);
int GetDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b);

BITMAPINFOHEADER bih;

BYTE *Buffer = NULL;

long LineByteWidth;
int main(void)
{
	int x, y;
	BYTE r, g, b;
	int n;
	char szfilename[255] = "122.bmp";
	if (ReadBmp(szfilename) == 0)
	{
		printf("failure to read file %s", szfilename);
		return 1;
	}
	printf("Width: %ld\n", bih.biWidth);
	printf("Height: %ld\n", bih.biHeight);
	printf("BitCount: %d\n\n", (int)bih.biBitCount);
	for(int i=0;i<bih.biWidth;i++){
		for(int j=0;j<bih.biHeight;j++){
			if (GetDIBColor(i, j, &r, &g, &b) == 1){
				int rgb = (((int)r/43)+(((int)g/43)*6)+(((int)b/43)*36) + 16);
				printf("%d,", rgb);
			}
			else{
				printf("input error.\n");
			}
		}
		printf("\n");
	}

	free(Buffer);
	return 0;
}

int ReadBmp(const char* szFileName)
{
	FILE *file;
	WORD bfh[7];
	long dpixeladd;
	if (NULL == (file = fopen(szFileName, "rb")))
	{
		return 0;
	}
	printf("%s\n", szFileName);
	fread(&bfh, sizeof(WORD), 7, file);
	if (bfh[0] != (WORD)(((WORD)'B')|('M'<<8)))
	{
		fclose(file);
		return 0;
	}
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);
	if (bih.biBitCount < 24)
	{
		fclose(file);
		return 0;
	}
	dpixeladd = bih.biBitCount / 8;
	LineByteWidth = bih.biWidth * (dpixeladd);
	if ((LineByteWidth % 4) != 0)
		LineByteWidth += 4 - (LineByteWidth % 4);
	if ((Buffer = (BYTE*)malloc(sizeof(BYTE)* LineByteWidth * bih.biHeight)) != NULL)
	{
		fread(Buffer, LineByteWidth * bih.biHeight, 1, file);
		fclose(file);
		return 1;
	}
	fclose(file);
	return 0;
}

int GetDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b)
{
	int dpixeladd;
	BYTE *ptr;
	if (X < 0 || X >= bih.biWidth || Y < 0 || Y >= bih.biHeight)
	{
		return 0;
	}
	dpixeladd = bih.biBitCount / 8;
	ptr = Buffer + X * dpixeladd + (bih.biHeight - 1 - Y) * LineByteWidth;
	*b = *ptr;
	*g = *(ptr + 1);
	*r = *(ptr + 2);
	return 1;
}