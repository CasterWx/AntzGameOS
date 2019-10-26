#include<fstream>
#include<windows.h>
#include<iostream>

using namespace std;
 
 
unsigned char *pBmpBuf;//读入图像数据的指针
int bmpWidth;//图像的宽
int bmpHeight;//图像的高
RGBQUAD *pColorTable;//颜色表指针
int biBitCount;//图像类型，每像素位数
 
 
 
//显示位图文件头信息   
void showBmpHead(BITMAPFILEHEADER pBmpHead){
	cout << "\n位图文件头:" << endl;
	cout << "文件大小:" << pBmpHead.bfSize << endl; 
	cout << "保留字_1:" << pBmpHead.bfReserved1 << endl;
	cout << "保留字_2:" << pBmpHead.bfReserved2 << endl;
	cout << "实际位图数据的偏移字节数:" << pBmpHead.bfOffBits << endl << endl;
}
//显示位图信息头信息  
void showBmpInforHead(BITMAPINFOHEADER pBmpInforHead){
	cout << "\n位图信息头:" << endl;
	cout << "结构体的长度:" << pBmpInforHead.biSize << endl;
	cout << "位图宽:" << pBmpInforHead.biWidth << endl;
	cout << "位图高:" << pBmpInforHead.biHeight << endl;
	cout << "biPlanes平面数:" << pBmpInforHead.biPlanes << endl;
	cout << "biBitCount采用颜色位数:" << pBmpInforHead.biBitCount << endl;
	cout << "压缩方式:" << pBmpInforHead.biCompression << endl;
	cout << "biSizeImage实际位图数据占用的字节数:" << pBmpInforHead.biSizeImage << endl;
	cout << "X方向分辨率:" << pBmpInforHead.biXPelsPerMeter << endl;
	cout << "Y方向分辨率:" << pBmpInforHead.biYPelsPerMeter << endl;
	cout << "使用的颜色数:" << pBmpInforHead.biClrUsed << endl;
	cout << "重要颜色数:" << pBmpInforHead.biClrImportant << endl;
}
//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool readBmp(char *bmpName)
{
	FILE *fp = fopen(bmpName, "rb");//二进制读方式打开指定的图像文件
	if (fp == 0)
		return 0;
 
	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	/*
	BITMAPFILEHEADER filehead;
	fread(&filehead, 1, sizeof(BITMAPFILEHEADER), fp);
	showBmpHead(filehead);//显示文件头   
*/
 
	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER infohead;
	fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp); //获取图像宽、高、每像素所占位数等信息
	bmpWidth = infohead.biWidth;
	bmpHeight = infohead.biHeight;
	biBitCount = infohead.biBitCount;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	showBmpInforHead(infohead);//显示信息头 
 
 
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;//灰度图像有颜色表，且颜色表表项为256
	if (biBitCount == 8)
	{
		//申请颜色表所需要的空间，读颜色表进内存
		pColorTable = new RGBQUAD[256];
		fread(pColorTable, sizeof(RGBQUAD), 256, fp);
	}
 
	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
	fclose(fp);//关闭文件
	return 1;//读取文件成功
}
 
 
 
//保存图片
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{
 
	//如果位图数据指针为0，则没有数据传入，函数返回
	if (!imgBuf)
		return 0;
	//颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0
	int colorTablesize = 0;
	if (biBitCount == 8)
		colorTablesize = 1024;
 
	//待存储图像数据每行字节数为4的倍数
	int lineByte = (width * biBitCount / 8 + 3) / 4 * 4;
 
	//以二进制写的方式打开文件
	FILE *fp = fopen(bmpName, "wb");
 
	if (fp == 0)
		return 0;
//------------------------------------------------------------------------------------------------------------------
	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;//bmp类型
 
	//bfSize是图像文件4个组成部分之和
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
 
	//bfOffBits是图像文件前3个部分所需空间之和
	fileHead.bfOffBits = 54 + colorTablesize;
//--------------------------------------------------------------------------------------------------------------------
	//写文件头进文件
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
 
	//申请位图信息头结构变量，填写信息头信息
	BITMAPINFOHEADER infohead;
	infohead.biBitCount = biBitCount;
	infohead.biClrImportant = 0;
	infohead.biClrUsed = 0;
	infohead.biCompression = 0;
	infohead.biHeight = height;
	infohead.biPlanes = 1;
	infohead.biSize = 40;
	infohead.biSizeImage = lineByte*height;
	infohead.biWidth = width;
	infohead.biXPelsPerMeter = 0;
	infohead.biYPelsPerMeter = 0;
 
	//写位图信息头进内存
	fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
//----------------------------------------------------------------------------------------------------------------------
	//如果灰度图像，有颜色表，写入文件 
	if (biBitCount == 8)
		fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
 
	//写位图数据进文件
	fwrite(imgBuf, height*lineByte, 1, fp);
 
	//关闭文件
	fclose(fp);
	return 1;
 
}
