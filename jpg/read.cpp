#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>

#include"read_save.h"

using namespace std;

//unsigned int out_r[2000][2000];
//unsigned int out_g[2000][2000];
//unsigned int out_b[2000][2000];
unsigned int **out_r;
unsigned int **out_g;
unsigned int **out_b;

void doIt()
{

	char readPath[] = "caozong.bmp";
	readBmp(readPath);
	// �������ͼ����Ϣ
	cout << "\nwidth=" << bmpWidth << "\nheight=" << bmpHeight << "\nbiBitCount=" << biBitCount << endl;
	// ͼ����ֽ���
	int linebyte1 = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	int n = 0, m = 0, count_xiang_su = 0;
	int i ;
	out_r = new unsigned int *[bmpHeight];        //����ָ������
	for (i= 0; i<bmpHeight; i++)
		out_r[i] = new unsigned int[bmpWidth];

	out_g = new unsigned int *[bmpHeight];        //����ָ������
	for (i = 0; i<bmpHeight; i++)
		out_g[i] = new unsigned int[bmpWidth];

	out_b = new unsigned int *[bmpHeight];        //����ָ������
	for (i = 0; i<bmpHeight; i++)
		out_b[i] = new unsigned int[bmpWidth];


	//��ʼ��ԭʼ���ص����顣

	if (biBitCount == 8)
	{
		for (int i = 0; i<bmpHeight / 2; i++)
		{
			for (int j = 0; j<bmpWidth / 2; i++)
				*(pBmpBuf + i*linebyte1 + j) = 0;
		}
	}

	if (biBitCount == 24)
	{
		for (int i = 0; i<bmpHeight; i++)
		{
			for (int j = 0; j<bmpWidth; j++)
			{
				for (int k = 0; k<3; k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
				{
					m = *(pBmpBuf + i*linebyte1 + j * 3 + k);
					count_xiang_su++;
				}
				n++;
			}
		}
		cout << "�ܵ����ظ���Ϊ:" << n << endl;
		cout << "----------------------------------------------------" << endl;
	}


	if (biBitCount == 24)
	{
		for (int i = 0; i<bmpHeight; i++)
		{
			for (int j = 0; j<bmpWidth; j++)
			{
				out_r[bmpHeight - 1 - i][j] = pBmpBuf[j * 3 + 2 + bmpWidth*i * 3];
				out_g[bmpHeight - 1 - i][j] = pBmpBuf[j * 3 + 1 + bmpWidth *i * 3];
				out_b[bmpHeight - 1 - i][j] = pBmpBuf[j * 3 + bmpWidth *i * 3];
			}
		}
	}

	//---------------------------------------------------------------------------------------
	//���������ݴ���TXT�ļ���
	ofstream outfile;
	char out_rgb[100] ;
  int ai,ji;
	outfile.open("rrbmp.txt", ios::in | ios::trunc);
	if(!outfile) cout << "error" << endl;
	for (ai = 0; ai<bmpHeight; ai++)
	{

        for (ji = 0; ji<bmpWidth; ji++)
        {
 //           sprintf(out_rgb,"0x%x,0x%x,0x%x,",out_r[ai][ji],out_g[ai][ji],out_b[ai][ji]);

            int a = 16 + out_r[ai][ji]/43 + 6* (out_g[ai][ji]/43) + 36* (out_b[ai][ji]/43) ;
            //outfile << out_r[ai][ji] ;
            //outfile << out_g[ai][ji] ;
            //outfile << out_b[ai][ji] << "  ";
            outfile << a << ",\t";
        }
        outfile << endl ;
        //outfile << "\n";
	}
	outfile.close();

	// jiang tuxiang shuju cunpan . 466560   864 540
	char writePath[] = "slm-1.bmp";
	saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);

	//�����������pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
	delete[]pBmpBuf;
	if (biBitCount == 8)
		delete[]pColorTable;

}

//
int main()
{
	doIt();
	system("pause");
	return 0;
}
