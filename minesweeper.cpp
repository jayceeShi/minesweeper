#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <cstring>
#include <fstream>
using namespace std;
string  tmp[20][20], choose;
int seed, flag1 = 0, flag2 = 0;
int boom[1000][100];
char state[30][30];
int  numberboom = 0, number[30][30] = { 0 }, num = 0, row = 0, col = 0, flagb = 0, flag[30][30], choice, flagboom[30][30] = { 0 }, flagt = 0;
int flaga = 0, flagc = 0, flagd = 0, flagts = 0, time1 = 0, numbertry = 0, haveatry[8];
int day, day1, hour, minute, second, hour1, minute1, second1, totaltime, boomnumber, flagti = 0, flagsave = 0, situation[30][30] = { 0 };
int flagclose = 0;
char ch;
int check(int a, int b)
{
	if (a < 0 || b < 0 || a >= row || b >= col)
	{
		return 1;
	}
	else if (state[a][b] == '*' && flag[a][b] == 2)
		return 1;
	else if (state[a][b] != '*')
	{
		return 1;
	}
	else
		return 0;
}
void try1(int a, int b)
{
	haveatry[0] = check(a, b + 1);
	haveatry[1] = check(a, b - 1);
	haveatry[2] = check(a + 1, b + 1);
	haveatry[3] = check(a - 1, b + 1);
	haveatry[4] = check(a + 1, b - 1);
	haveatry[5] = check(a - 1, b - 1);
	haveatry[6] = check(a + 1, b);
	haveatry[7] = check(a - 1, b);
	for (int i = 0; i < 8; i++)
		numbertry += haveatry[i];
}

void prepare()                                                       //��ʼ����
{
	initgraph(500, 640);
	IMAGE img;
	loadimage(&img, "background.jpg");
	putimage(0, 0, &img);
}
void help()                                                         //��Ϸ����˵������
{
	IMAGE img;
	loadimage(&img, "help.jpg");
	putimage(0, 0, &img);
	MOUSEMSG m;
	int flagl = 0;
	while (!_kbhit())
	{
		m = GetMouseMsg();
		int a = m.x;
		int b = m.y;
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			if (b >= 580 && b <= 610 && a >= 390 && a <= 460)
			{
				prepare();
				flagl = 1;
			}
		}break;
		}
		if (flagl == 1)
			break;
	}
}
void mouse1()                                                    //��ȡ��ʼ�����ϵ���궯��
{
	MOUSEMSG m;
	flagt = 0;
	while (!_kbhit())
	{
		m = GetMouseMsg();
		int flagh = 0;
		int a = m.x;
		int b = m.y;
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			if (b >= 170 && b <= 210 && a >= 200 && a <= 270)             //choice����ѡ���ģʽ���ֱ��Ӧeasy,medium,hard���Զ��塢����
			{
				choice = 1;
				flagh = 1;
			}
			else if (b >= 240 && b <= 270 && a >= 175 && a <= 300 )
			{
				choice = 2;	flagh = 1;
			}
			else if (b >= 310 && b <= 340 && a >= 200 && a <= 270)
			{
				flagh = 1; choice = 3;
			}
			else if (b >= 370 && b <= 410 && a >= 145 && a <= 355)
			{
				flagh = 1; choice = 4;
			}
			else if (b >= 430 && b <= 460 && a >= 135 && a <= 360)
			{
				flagh = 1; choice = 5;
			}
			else if (b > 500 && b <= 540 && a >= 200 && a <= 290)
				help();
		}break;
		}
		if (flagh == 1)
		{
			flagclose = 1;
			break;
		}
	}
}
void open(int a, int b)                                               //����ÿ��������δ�����ĸ��ӣ��������ж�����
{
	if (flag[a][b] == 0 && a < row && b < col && a >= 0 && b >= 0)    //�ж��Ƿ�Խ��
	{
		flag[a][b] = 1;                                               //flag���ڱ���Ƿ񷭿�
		num++;
		if (state[a][b] == '*')                                        //�ǵ��ף���Ϸ������lose��flagb=1�������˵���
		{
			flagb = 1;
			IMAGE img;
			loadimage(&img, "boom.jpg");
			putimage((b + 1) * 35, (a + 1) * 35, &img);
		}
		else
		{
			if (state[a][b] == ' ')                                    //�ǿո񣬷�����Χ8�����ӣ��ǵ����򲻷�����
			{
				IMAGE img;
				loadimage(&img, "fore.jpg");
				putimage((b + 1) * 35, (a + 1) * 35, &img);
				if (a > 0 && state[a-1][b] != '*')
					open(a - 1, b);
				if (a > 0 && b > 0 && state[a-1][b-1] != '*')
						open(a - 1, b - 1);
				if (a > 0 && b < col - 1&& state[a-1][b+1] != '*')
					open(a - 1, b + 1);
				if (a < row - 1 && state[a + 1][b] != '*')
					open(a + 1, b);
				if (a < row - 1 && b < col - 1 && state[a + 1][b + 1] != '*')
					open(a + 1, b + 1);
				if (b > 0 && state[a][b - 1] != '*')
					open(a, b - 1);
				if (a < row - 1 && b > 0 && state[a + 1][b - 1] != '*')
					open(a + 1, b - 1);
				if (b < col - 1 && state[a][b + 1] != '*')
					open(a, b + 1);
			}
			else
			{
				switch (number[a][b])                                 //��������ֱ�����
				{
				case 1:
				{
					IMAGE img;
					loadimage(&img, "1.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}break;
				case 2:
				{
					IMAGE img;
					loadimage(&img, "2.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}break;
				case 3:
				{
					IMAGE img;
					loadimage(&img, "3.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}break;
				case 4:
				{
					IMAGE img;
					loadimage(&img, "4.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}break;
				case 5:
				{
					IMAGE img;
					loadimage(&img, "5.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}break;
				case 6:
				{
					IMAGE img;
					loadimage(&img, "6.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}break;
				case 7:
				{
					IMAGE img;
					loadimage(&img, "7.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}break;
				case 8:
				{
					IMAGE img;
					loadimage(&img, "8.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}break;
				default:break;
				}
			}
		}
	}
}
void appear(int & row, int & col, int & numberboom, int c)                       //���ڸ���ѡ���ģʽ��������Ϸҳ��
{
	string row1, col1, numberboom1;
	system("cls");
	switch (c)
	{
	case 1: row = 9, col = 9, numberboom = 10, boomnumber = numberboom; break;
	case 2: row = 16, col = 16, numberboom = 40, boomnumber = numberboom; break;
	case 3: row = 16, col = 30, numberboom = 99, boomnumber = numberboom; break;
	case 4: {
		initgraph(500, 640);
		IMAGE img;
		loadimage(&img, "userdefine.jpg");
		putimage(0, 0, &img);
		IMAGE imgA;
		loadimage(&imgA, "ROW.jpg");
		putimage(95, 450, &imgA);
		IMAGE imgB;
		loadimage(&imgB, "COL.jpg");
		putimage(200, 450, &imgB);
		IMAGE imgC;
		loadimage(&imgC, "MINE.jpg");
		putimage(300, 450, &imgC);
		int flag = 0, numb = 120, numbe = 0, nu = 0, flagprint = 0;
		while (1)
		{
			if (flag == 3)
				break;
			if (_kbhit())
			{
				char ch = _getch();
				int cha = ch - '0';
				if (ch - '0' >= 0 && ch - '0' <= 9)
				{
					if ((flag < 2 && nu < 2) || (flag == 2 && nu < 3))        //nu�����ж��Ƿ��������λ��Ҫ��
					{
						flagprint = 1;
						numbe = numbe * 10 + cha;
						nu++;
						numb += 15;
						switch (cha)                                 //��������ֱ�����
						{
						case 1:
						{
							IMAGE img;
							loadimage(&img, "1.1.jpg");
							putimage(numb, 450, &img);
						}break;
						case 2:
						{
							IMAGE img;
							loadimage(&img, "1.2.jpg");
							putimage(numb, 450, &img);
						}break;
						case 3:
						{
							IMAGE img;
							loadimage(&img, "1.3.jpg");
							putimage(numb, 450, &img);
						}break;
						case 4:
						{
							IMAGE img;
							loadimage(&img, "1.4.jpg");
							putimage(numb, 450, &img);
						}break;
						case 5:
						{
							IMAGE img;
							loadimage(&img, "1.5.jpg");
							putimage(numb, 450, &img);
						}break;
						case 6:
						{
							IMAGE img;
							loadimage(&img, "1.6.jpg");
							putimage(numb, 450, &img);
						}break;
						case 7:
						{
							IMAGE img;
							loadimage(&img, "1.7.jpg");
							putimage(numb, 450, &img);
						}break;
						case 8:
						{
							IMAGE img;
							loadimage(&img, "1.8.jpg");
							putimage(numb, 450, &img);
						}break; 
						case 9:
						{
							IMAGE img;
							loadimage(&img, "1.9.jpg");
							putimage(numb, 450, &img);
						}break; 
						case 0:
						{
							IMAGE img;
							loadimage(&img, "1.0.jpg");
							putimage(numb, 450, &img);
						}break;
						default:break;
						}
					}
				}
				if (ch == '\b' && nu > 0)                         //ɾ���Ѿ���������ݵ�Ҫ��
				{
					nu--;
					IMAGE img;
					loadimage(&img, "backspace.jpg");
					putimage(numb, 450, &img);
					numbe = numbe / 10;
					numb -= 15;
				}
				if (ch == ' ' || ch == '\r' && nu > 0)               //�س����߿ո��ȡ
				{
					flagprint = 0;
					nu = 0;
					flag++;
					numb += 85;
					if (flag == 1)
					{
						row = numbe;
						numbe = 0;
					}
					else if (flag == 2)
					{
						col = numbe;
						numbe = 0;
					}
					else if (flag == 3)
					{
						numberboom = numbe;
						boomnumber = numberboom;
						numbe = 0;
					}
				}
			}
		}
		if (row < 5 || col < 5 || row > 20 || col > 30 || numberboom >= col * row)
		{
			IMAGE img;
			loadimage(&img, "selfdefine.jpg");
			putimage(0, 0, &img);
			Sleep(3000);
			prepare();
			mouse1();    
			appear(row, col, numberboom, choice);     //ѡ���Ѷ�
			if (flagclose == 1)
				closegraph();
		}
	}break;
	case 5:                                                  //����״̬
	{
		ifstream data("minesweeper.txt");
		if (!data)                                            //����ʧ�ܴ���δ�д浵
		{
			initgraph(500, 640);
			IMAGE img;
			loadimage(&img, "error.jpg");
			putimage(0, 0, &img);
			Sleep(3000);
			prepare();
			mouse1();                                       //����ѡ��
			if (flagclose == 1)
				closegraph();
			appear(row, col, numberboom, choice);
		}
		else
		{
			data >> row >> col >> numberboom >> boomnumber >> time1 >> flagti;
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)            //��ȡ����״̬
				{
					data >> flag[i][j] >> state[i][j] >> number[i][j];
					situation[i][j] = flag[i][j];        //��ֹչ��ʱ������ͻ��situation��¼�Ƿ�չ����flagȫ����0
					flag[i][j] = 0;
				}
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
				{
					flag[i][j] = 0;
					if (state[i][j] == '&')            //&����հ�
						state[i][j] = ' ';
				}
			SYSTEMTIME ti;                             //����ģʽ�Ӷ�ȡ��ʼ��ʱ�����ȴ����
			GetLocalTime(&ti);
			day = ti.wDay;
			hour = ti.wHour;
			minute = ti.wMinute;
			second = ti.wSecond;
			flagts = 1;
			data.close();
		}
	}break;
	}
}
void define()                                                                  //�ڲ��ŵ���֮��������ÿһ���������״̬
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (state[i][j] != '*')
			{
				if (i == 0)
				{
					if (j != col - 1 && j != 0)
					{
						number[i][j] = (state[i + 1][j] == '*') + (state[i + 1][j + 1] == '*') + (state[i + 1][j - 1] == '*') + (state[i][j + 1] == '*') + (state[i][j - 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
					if (j == 0)
					{
						number[i][j] = (state[i + 1][j] == '*') + (state[i + 1][j + 1] == '*') + (state[i][j + 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
					if (j == col - 1)
					{
						number[i][j] = (state[i + 1][j] == '*') + (state[i + 1][j - 1] == '*') + (state[i][j - 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
				}
				else if (i == row - 1)
				{
					if (j != col - 1 && j != 0)
					{
						number[i][j] = (state[i - 1][j] == '*') + (state[i - 1][j + 1] == '*') + (state[i - 1][j - 1] == '*') + (state[i][j + 1] == '*') + (state[i][j - 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
					if (j == 0)
					{
						number[i][j] = (state[i - 1][j] == '*') + (state[i - 1][j + 1] == '*') + (state[i][j + 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
					if (j == col - 1)
					{
						number[i][j] = (state[i - 1][j] == '*') + (state[i - 1][j - 1] == '*') + (state[i][j - 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
				}
				else
				{
					if (j != col - 1 && j != 0)
					{
						number[i][j] = (state[i + 1][j - 1] == '*') + (state[i + 1][j + 1] == '*') + (state[i + 1][j] == '*') + (state[i - 1][j] == '*') + (state[i - 1][j + 1] == '*') + (state[i - 1][j - 1] == '*') + (state[i][j + 1] == '*') + (state[i][j - 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
					if (j == 0)
					{
						number[i][j] = (state[i + 1][j] == '*') + (state[i + 1][j + 1] == '*') + (state[i - 1][j] == '*') + (state[i - 1][j + 1] == '*') + (state[i][j + 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
					if (j == col - 1)
					{
						number[i][j] = (state[i + 1][j] == '*') + (state[i + 1][j - 1] == '*') + (state[i - 1][j] == '*') + (state[i - 1][j - 1] == '*') + (state[i][j - 1] == '*');
						if (number[i][j] == 0)
							state[i][j] = ' ';
						else
							state[i][j] = number[i][j] + '0';
					}
				}
			}
		}
	}
}                      //���ڳ�ʼ������
void mouse()                                                                //��Ϸ�����ϵ�������
{
	setbkcolor(RGB(60, 38, 30));
	setcolor(WHITE);
	outtextxy(((col + 2) * 35 - 190) / 2, 10, "you have used    ");         //�����ʼʱ����Ϸʱ��
	outtextxy(((col + 2) * 35 - 190) / 2 + 95, 10, "         seconds");
	char time2[100000];
	sprintf_s(time2, "%d", time1);                                         
	setbkcolor(RGB(60, 38, 30));
		setcolor(WHITE);
		outtextxy(((col + 2) * 35 - 190) / 2 + 107, 10, time2);
	SYSTEMTIME ti;
	MOUSEMSG m;
	flagt = 0;
	while (!_kbhit())
	{
		if (flagts == 1)                                                  //�����Ƿ�������������������Ϸʱ���Ա�֤ÿ��仯
		{
			while (!MouseHit())
			{
				GetLocalTime(&ti);
				day1 = ti.wDay;
				hour1 = ti.wHour;
				minute1 = ti.wMinute;
				second1 = ti.wSecond;
				totaltime = (day1 - day) * 86400 + (hour1 - hour) * 3600 + (minute1 - minute) * 60 + second1 - second + time1;
				char time2[100000];
				sprintf_s(time2, "%d", totaltime);
				if (totaltime < 0)
				{
					setbkcolor(RGB(60, 38, 30));
					setcolor(WHITE);
					outtextxy(((col + 2) * 35 - 190) / 2 + 1, 10, "time out          ");           //��ʱ�ж�
					break;
				}
				else
				{
					setbkcolor(RGB(60, 38, 30));
					setcolor(WHITE);
					outtextxy(((col + 2) * 35 - 190) / 2 + 107, 10, time2);
				}
			}
		}
		if (flagts == 1)                                                                //����Ѿ���ʼ��ʱ���õ�ǰ��ʱ���ȥ��ʼʱ��ʱ�����ж��õ�ʱ��
		{
			GetLocalTime(&ti);
			hour1 = ti.wHour;
			minute1 = ti.wMinute;
			second1 = ti.wSecond;
			day1 = ti.wDay;
			totaltime = (day1 - day) * 86400 + (hour1 - hour) * 3600 + (minute1 - minute) * 60 + second1 - second + time1;
			char time2[100000];
			sprintf_s(time2, "%d", totaltime);
			if (totaltime < 0)
			{
				outtextxy(1, 10, "time out");
				break;
			}
			else
				outtextxy(((col + 2) * 35 - 190) / 2 + 107, 10, time2);       //�ڹ̶������������ʱ��
		}
		m = GetMouseMsg();                                                    //�ж����
		int b = m.x / 35 - 1;
		int a = m.y / 35 - 1;
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			if (a >= 0 && a < row && b >= 0 && b < col)                      //�ж�����Ƿ�Խ��
			{
				if (flagts == 0)                                             //����ǵ�һ���������ʼ��ʱ
				{
					GetLocalTime(&ti);
					day = ti.wDay;
					hour = ti.wHour;
					minute = ti.wMinute;
					second = ti.wSecond;
					flagts = 1;
				}
				if (flagti == 0)                                            //����ǵ�һ������������ʼ�ж��׵�λ��
				{
					int flagm = 0;
					if (state[a][b] == '*')                                  //��֤��һ�ε���ĵط�������
					{
						for (int i = 0; i < row; i++)
						{
							for (int j = 0; j < col; j++)
							{
								if (state[i][j] == ' ')
								{
									state[i][j] = '*';
									flagm = 1;
									break;
								}
							}
							if (flagm == 1)
								break;
						}
						state[a][b] = ' ';
					}
					define();                                             //������ײ��ֵ�״̬
					flagti = 1;
				}
				if ((flag[a][b] == 0) && a >= 0 && a < row && b >= 0 && b < col)    //�ڲ�Խ��ʱ���������Ӳ��ж�
					open(a, b);
			}
			else if (m.x >= (col + 1) * 35 + 10 && m.x < (col + 1) * 35 + 30 && m.y >= ((row + 2) * 35 - 135) / 2 && m.y < ((row + 2) * 35 - 135) / 2 + 135)
			{
				ofstream data("minesweeper.txt");                      //���ѡ����̲��˳�
				while (!data)
				{
					ofstream data("minesweeper.txt");
				}
				time1 = totaltime;                                     //��¼����ʱ�䡢����״̬
				data << row << endl;
				data << col << endl;
				data << numberboom << endl;
				data << boomnumber << endl;
				data << time1 << endl;
				data << flagti << endl;
				for (int i = 0; i < row; i++)                          //�������Ĵ��󣬿հ�����ת����&��¼
					for (int j = 0; j < col; j++)
					{
						if (state[i][j] == ' ')
							state[i][j] = '&';
					}
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
					{
						data << flag[i][j] << endl;
						data << state[i][j] << endl;
						data << number[i][j] << endl;
					}
				data.close();
				flagt = 1;                                                    //flagt�����˳�mouse����
				flaga = 2;                                                    
				flagsave = 1;                                                  //�����Ѿ����д��̲���
			}
		}break;
		case WM_MBUTTONDOWN:
		{
			flagt = 1;                                                       //���¹��ִ���Ͷ��
		}break;
		case WM_LBUTTONDBLCLK:
		{
			if (flag[a][b] == 1)
			{
				try1(a, b);
				if (numbertry == 8)                                  //˫��������Դ���Χ�ĸ��ӣ����ȫ�������׻����׵ı��������죬���
				{
					numbertry = 0;
					open(a, b + 1);
					open(a, b - 1);
					open(a - 1, b);
					open(a - 1, b - 1);
					open(a - 1, b + 1);
					open(a + 1, b);
					open(a + 1, b - 1);
					open(a + 1, b + 1);
				}
				numbertry = 0;
			}
		}break;
		case WM_RBUTTONDOWN:
		{
			char boo[100];
			if (flag[a][b] == 0 && a >= 0 && a < row && b >= 0 && b < col)   //�һ���ǻ��߽�����
			{
				flag[a][b] = 2;
				IMAGE img;
				loadimage(&img, "flag.jpg");
				putimage((b + 1) * 35, (a + 1) * 35, &img);
				boomnumber--;
			}
			else if (flag[a][b] == 2)
			{
				flag[a][b] = 0;
				IMAGE img;
				loadimage(&img, "back.jpg");
				putimage((b + 1) * 35, (a + 1) * 35, &img);
				boomnumber++;
			}
			sprintf_s(boo, "%d", boomnumber);                                  //ÿ�ε�������ʣ������
			setbkcolor(RGB(60, 38, 30));
			setcolor(WHITE);
			outtextxy(6, ((row + 2) * 35 - 135) / 2 + 100, "     ");
			outtextxy(10, ((row + 2) * 35 - 135) / 2 + 100, boo);
			if (boomnumber < 0)
			{
				outtextxy(6, ((row + 2) * 35 - 135) / 2 + 100, "     ");
				outtextxy(10, ((row + 2) * 35 - 135) / 2 + 100, "??");
			}
		}break;
		}
		if (flagt == 1)
		{
			flagd = 0;
			break;
		}
		if (flagb == 1)                                                   //������׵�״��
		{
			IMAGE img;
			loadimage(&img, "lose.jpg");
			putimage((col * 35 - 100) / 2, (row + 1) * 35, &img);
			flagd = 1;                                                    //flagd�������˻�Ӯ���˳�
			break;
		}
		if (num == row * col - numberboom)                               //������ȫ��չ������ʤ
		{
			IMAGE img;
			loadimage(&img, "win.jpg");
			putimage((col * 35 - 75) / 2, (row + 1) * 35, &img);
			flagd = 1;
			break;
		}
		if (_kbhit())                                                     //��ֹ��������Ӱ��
		{
			char ch = _getch();
			break;
		}
	}
}
void again()                                                     //�ж��Ƿ�������һ��
{
	MOUSEMSG n;
	IMAGE img;
	loadimage(&img, "again.jpg");
	putimage(200, 100, &img);
	IMAGE i;
	loadimage(&i, "yes.jpg");
	putimage(200, 200, &i);
	IMAGE im;
	loadimage(&im, "no.jpg");
	putimage(200, 300, &im);
	IMAGE m;
	loadimage(&m, "menu.jpg");
	putimage(200, 400, &m);
	while (flaga == 0)                                          //��ȡ������
	{
		n = GetMouseMsg();
		int b = n.x;
		int a = n.y;
		if (n.uMsg == WM_LBUTTONDOWN)
		{
			if (b >= 200 && b <= 315 && a >= 200 && a <= 230)
			{
				flaga = 1;                                     //flaga�������������ֱ��Ӧ���������������ص����˵�

			}
			else if (b >= 200 && b <= 315 && a >= 300 && a <= 330)
			{
				flaga = 2;
			}
			else if (b >= 200 && b <= 315 && a >= 400 && a <= 430)
			{
				flaga = 3;
			}
		}
	}
}
void welcome()                                                    //��ӭҳ��
{
	initgraph(500, 640);
	IMAGE img;
	loadimage(&img, "welcome.jpg");
	putimage(0, 0, &img);
}
int main()
{
	welcome();
	Sleep(3000);                                                      //�ڻ�ӭҳ���ӳ�
	closegraph();
	while (flagc == 0)
	{
		prepare();
		mouse1();                                                     //ѡ���Ѷ�
		if (flagclose == 1)
			closegraph();
		flagsave = 0;
		for (int i = 0; i < 20; i++)                                  //��ʼ������״̬��ȫ��Ϊ�հף�             
			for (int j = 0; j < 30; j++)
				state[i][j] = ' ';
		appear(row, col, numberboom, choice);                         //����ģʽȷ��������С
		while (1)
		{
			for (int i = 0; i < 20; i++)                              //��ʼ��ÿ�����ӵ�״̬��δչ����
				for (int j = 0; j < 30; j++)
				{
						flag[i][j] = 0;
				}
			initgraph((col + 3) * 35, (row + 3) * 35);                //����ͼ�ν���
			for (int b = 0; b < col; b++)
			{
				for (int a = 0; a < row; a++)
				{
					IMAGE img;
					loadimage(&img, "back.jpg");
					putimage((b + 1) * 35, (a + 1) * 35, &img);
				}
			}
			for (int i = (row + 1) * 35; i <= (row + 3) * 35; i++)
			{
				setcolor(RGB(60,38,30));
				line(000, i, (col + 2) * 35, i);
			}
			for (int i = (row + 1) * 35; i <= (row + 3) * 35; i++)
			{
				setcolor(RGB(60, 38, 30));
				line(000, i, (col + 3) * 35, i);
			}
			for (int i = 0; i <= 35; i++)
			{
				setcolor(RGB(60,38,30));
				line(i, 000, i, (row + 2) * 35);
			}
			for (int i = 0; i <= 35; i++)
			{
				setcolor(RGB(60, 38, 30));
				line(i, 000, i, (row + 3) * 35);
			}
			for (int i = (col + 1) * 35; i <= (col + 3) * 35; i++)
			{
				setcolor(RGB(60,38,30));
				line(i, 000, i, (row + 2) * 35);
			}
			for (int i = (col + 1) * 35; i <= (col + 3) * 35; i++)
			{
				setcolor(RGB(60, 38, 30));
				line(i, 000, i, (row + 3) * 35);
			}
			for (int i = 0; i <= 35; i++)
			{
				setcolor(RGB(60,38,30));
				line(000, i, (col + 2) * 35, i);
			}
			for (int i = 0; i <= 35; i++)
			{
				setcolor(RGB(60, 38, 30));
				line(000, i, (col + 3) * 35, i);
			}
			
			setbkcolor(RGB(60,38,30));
			setcolor(WHITE);
			outtextxy(10, ((row + 2) * 35 - 135) / 2, "M");
			outtextxy(10, ((row + 2) * 35 - 135) / 2 + 20, "I");
			outtextxy(10, ((row + 2) * 35 - 135) / 2 + 40, "N");
			outtextxy(10, ((row + 2) * 35 - 135) / 2 + 60, "E");
			outtextxy(10, ((row + 2) * 35 - 135) / 2 + 80, " : ");
			char boo[100];
			sprintf_s(boo, "%d", boomnumber);
			setbkcolor(RGB(60, 38, 30));
			setcolor(WHITE);
			outtextxy(9, ((row + 2) * 35 - 135) / 2 + 100, boo);
			for (int i = (col + 1) * 35; i >= 0; i = i - 70)
			{
				IMAGE imga;
				loadimage(&imga, "pic2.jpg");
				putimage(i, (row + 1)*35, &imga);
			}
			for (int i = (row + 1) * 35; i >= 0; i = i - 70)
			{
				IMAGE imga;
				loadimage(&imga, "pic1.jpg");
				putimage((col + 1)*35, i, &imga);
			}
			IMAGE imga;
			loadimage(&imga, "pic.jpg");
			putimage((col + 1) * 35, (row + 1)*35, &imga);
			for (int i = 0; i < row; i++)                             //���������ϷΪ����״̬������situation�ж�ԭ�ȵĸ����Ƿ��Ѿ�չ�������±�ʾ״̬
				for (int j = 0; j < col; j++)
				{
					if (situation[i][j] == 1)
						open(i, j);
					else if (situation[i][j] == 2)
					{
						flag[i][j] = 2;
						IMAGE img;
						loadimage(&img, "flag.jpg");
						putimage((j + 1) * 35, (i + 1) * 35, &img);
					}
				}
			IMAGE img;
			loadimage(&img, "save and quit.jpg");
			putimage((col + 1) * 35 + 10, ((row + 2) * 35 - 135) / 2, &img);
			srand((unsigned int)time(0));
			for (int i = 0; i < numberboom; i++)
			{
				while (1)
				{
					seed = rand();                                   //���������
					int p = seed % row;
					seed = rand();
					int q = seed % col;
					boom[i][0] = p; boom[i][1] = q;
					int j;
					for (j = 0; j < i; j++)
					{
						if ((boom[j][0] == boom[i][0] && boom[j][1] == boom[i][1]))
							break;
					}
					if (j >= i)
					{
						state[p][q] = '*';
						break;
					}

				}
			}
			mouse();
			Sleep(600);
			if (flagsave == 1)                                           //��ѡ��浵�����˳���ֱ���˳���flagc�����Ƿ��˳���
			{
				flagc = 1;
				break;
			}
			if (flagd == 1)                                              //flagd��������������Ϸ����ʱչ����������
			{
				for (int b = 0; b < col; b++)
				{
					for (int a = 0; a < row; a++)
					{
						if (state[a][b] == '*' && flag[a][b] != 1)
						{
							IMAGE img;
							loadimage(&img, "boom.jpg");
							putimage((b + 1) * 35, (a + 1) * 35, &img);
							if (numberboom >= 100)
								Sleep(5);
							else
								Sleep(30);
						}
					}
				}
				Sleep(2000);
				flagti = 0;
			}
			else if (flagt == 1)                                                //Ͷ��״̬��ͬ��չ���������ӳ�ʱ��ı�
			{
				for (int b = 0; b < col; b++)
				{
					for (int a = 0; a < row; a++)
					{
						if (state[a][b] == '*' && flag[a][b] != 1)
						{
							IMAGE img;
							loadimage(&img, "boom.jpg");
							putimage((b + 1) * 35, (a + 1) * 35, &img);
							Sleep(10);
						}
					}
				}
				Sleep(1000);
				flagti = 0;                                                       //��ʼ�������Ƿ��һ�ε�������ı���
				initgraph(500, 650);
				IMAGE img;
				loadimage(&img, "resign.jpg");
				putimage(0, 0, &img);
			}
			for (int i = 0; i < 30; i++)
				for (int j = 0; j < 30; j++)
				{
					situation[i][j] = 0;
					state[i][j] = ' ';
				}
			time1 = 0;                                                            //��ʼ����������Զ���״̬������Ϸ��
			flagts = 0;
			boomnumber = numberboom;
			if (flagb == 1)                                                   //������׵�״��
			{
				initgraph(500, 650);
				IMAGE img;
				loadimage(&img, "lose1.jpg");
				putimage(0,0, &img);
			}
			else if (num == row * col - numberboom)                               //������ȫ��չ������ʤ
			{
				initgraph(500, 650);
				IMAGE img;
				loadimage(&img, "win1.jpg");
				putimage(0, 0, &img);
			}
			Sleep(1000);
			again();
			if (flaga == 2)                                                       //ѡ�������Ϸ
			{
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						situation[i][j] = 0;
				flagc = 1;
				break;
			}
			if (flaga == 3)                                                       //ѡ��ص����˵�
			{
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						situation[i][j] = 0;
				break;
			}
			flagsave = 0;                                                        //ѡ������һ�ֵ��ߵ��˴�����ʼ�����������жϵı���
			flagts = 0;
			flaga = 0;
			flagb = 0;
			num = 0;
			flagd = 0;
			flagti = 0;
		}
		flaga = 0;                                                              //��ʼ�����������жϵı���
		flagb = 0;
		num = 0;
		flagd = 0;
		flagti = 0;
		closegraph();
	}
	initgraph(500, 600);
	IMAGE img;
	loadimage(&img, "goodbye.jpg");                                            //�رս���ǰ���������
	putimage(0, 0, &img);
	Sleep(3000);
	closegraph();
	return 0;

}