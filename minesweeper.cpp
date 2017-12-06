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

void prepare()                                                       //开始界面
{
	initgraph(500, 640);
	IMAGE img;
	loadimage(&img, "background.jpg");
	putimage(0, 0, &img);
}
void help()                                                         //游戏操作说明界面
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
void mouse1()                                                    //获取开始界面上的鼠标动作
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
			if (b >= 170 && b <= 210 && a >= 200 && a <= 270)             //choice代表选择的模式，分别对应easy,medium,hard和自定义、读盘
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
void open(int a, int b)                                               //对于每次鼠标左击未翻开的格子，翻开并判断内容
{
	if (flag[a][b] == 0 && a < row && b < col && a >= 0 && b >= 0)    //判断是否越界
	{
		flag[a][b] = 1;                                               //flag用于标记是否翻开
		num++;
		if (state[a][b] == '*')                                        //是地雷，游戏结束，lose。flagb=1代表翻到了地雷
		{
			flagb = 1;
			IMAGE img;
			loadimage(&img, "boom.jpg");
			putimage((b + 1) * 35, (a + 1) * 35, &img);
		}
		else
		{
			if (state[a][b] == ' ')                                    //是空格，翻开周围8个格子（是地雷则不翻开）
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
				switch (number[a][b])                                 //是数字则直接输出
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
void appear(int & row, int & col, int & numberboom, int c)                       //用于根据选择的模式来设置游戏页面
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
					if ((flag < 2 && nu < 2) || (flag == 2 && nu < 3))        //nu用来判断是否输出超出位数要求
					{
						flagprint = 1;
						numbe = numbe * 10 + cha;
						nu++;
						numb += 15;
						switch (cha)                                 //是数字则直接输出
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
				if (ch == '\b' && nu > 0)                         //删除已经输入的内容的要求
				{
					nu--;
					IMAGE img;
					loadimage(&img, "backspace.jpg");
					putimage(numb, 450, &img);
					numbe = numbe / 10;
					numb -= 15;
				}
				if (ch == ' ' || ch == '\r' && nu > 0)               //回车或者空格读取
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
			appear(row, col, numberboom, choice);     //选择难度
			if (flagclose == 1)
				closegraph();
		}
	}break;
	case 5:                                                  //读盘状态
	{
		ifstream data("minesweeper.txt");
		if (!data)                                            //读盘失败代表还未有存档
		{
			initgraph(500, 640);
			IMAGE img;
			loadimage(&img, "error.jpg");
			putimage(0, 0, &img);
			Sleep(3000);
			prepare();
			mouse1();                                       //重新选择
			if (flagclose == 1)
				closegraph();
			appear(row, col, numberboom, choice);
		}
		else
		{
			data >> row >> col >> numberboom >> boomnumber >> time1 >> flagti;
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)            //读取雷区状态
				{
					data >> flag[i][j] >> state[i][j] >> number[i][j];
					situation[i][j] = flag[i][j];        //防止展开时发生冲突，situation记录是否展开，flag全部清0
					flag[i][j] = 0;
				}
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++)
				{
					flag[i][j] = 0;
					if (state[i][j] == '&')            //&代表空白
						state[i][j] = ' ';
				}
			SYSTEMTIME ti;                             //读盘模式从读取开始计时，不等待左击
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
void define()                                                                  //在布号地雷之后用来给每一个格子添加状态
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
}                      //用于初始化界面
void mouse()                                                                //游戏界面上的鼠标操作
{
	setbkcolor(RGB(60, 38, 30));
	setcolor(WHITE);
	outtextxy(((col + 2) * 35 - 190) / 2, 10, "you have used    ");         //输出开始时的游戏时间
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
		if (flagts == 1)                                                  //不管是否有鼠标点击，不断输出游戏时间以保证每秒变化
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
					outtextxy(((col + 2) * 35 - 190) / 2 + 1, 10, "time out          ");           //超时判断
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
		if (flagts == 1)                                                                //如果已经开始计时，用当前的时间减去开始时的时间来判断用的时间
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
				outtextxy(((col + 2) * 35 - 190) / 2 + 107, 10, time2);       //在固定的坐标上输出时间
		}
		m = GetMouseMsg();                                                    //判断鼠标活动
		int b = m.x / 35 - 1;
		int a = m.y / 35 - 1;
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			if (a >= 0 && a < row && b >= 0 && b < col)                      //判断左击是否越界
			{
				if (flagts == 0)                                             //如果是第一次左击，开始计时
				{
					GetLocalTime(&ti);
					day = ti.wDay;
					hour = ti.wHour;
					minute = ti.wMinute;
					second = ti.wSecond;
					flagts = 1;
				}
				if (flagti == 0)                                            //如果是第一次左击，左击后开始判断雷的位置
				{
					int flagm = 0;
					if (state[a][b] == '*')                                  //保证第一次点击的地方不是雷
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
					define();                                             //计算非雷部分的状态
					flagti = 1;
				}
				if ((flag[a][b] == 0) && a >= 0 && a < row && b >= 0 && b < col)    //在不越界时，翻开格子并判断
					open(a, b);
			}
			else if (m.x >= (col + 1) * 35 + 10 && m.x < (col + 1) * 35 + 30 && m.y >= ((row + 2) * 35 - 135) / 2 && m.y < ((row + 2) * 35 - 135) / 2 + 135)
			{
				ofstream data("minesweeper.txt");                      //如果选择存盘并退出
				while (!data)
				{
					ofstream data("minesweeper.txt");
				}
				time1 = totaltime;                                     //记录所用时间、雷区状态
				data << row << endl;
				data << col << endl;
				data << numberboom << endl;
				data << boomnumber << endl;
				data << time1 << endl;
				data << flagti << endl;
				for (int i = 0; i < row; i++)                          //避免读入的错误，空白雷区转化成&记录
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
				flagt = 1;                                                    //flagt代表退出mouse部分
				flaga = 2;                                                    
				flagsave = 1;                                                  //代表已经进行存盘操作
			}
		}break;
		case WM_MBUTTONDOWN:
		{
			flagt = 1;                                                       //按下滚轮代表投降
		}break;
		case WM_LBUTTONDBLCLK:
		{
			if (flag[a][b] == 1)
			{
				try1(a, b);
				if (numbertry == 8)                                  //双击左键尝试打开周围的格子，如果全都不是雷或是雷的被插上了旗，则打开
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
			if (flag[a][b] == 0 && a >= 0 && a < row && b >= 0 && b < col)   //右击标记或者解除标记
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
			sprintf_s(boo, "%d", boomnumber);                                  //每次点击后更改剩余雷数
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
		if (flagb == 1)                                                   //点击到雷的状况
		{
			IMAGE img;
			loadimage(&img, "lose.jpg");
			putimage((col * 35 - 100) / 2, (row + 1) * 35, &img);
			flagd = 1;                                                    //flagd代表输了或赢了退出
			break;
		}
		if (num == row * col - numberboom)                               //非雷区全部展开，获胜
		{
			IMAGE img;
			loadimage(&img, "win.jpg");
			putimage((col * 35 - 75) / 2, (row + 1) * 35, &img);
			flagd = 1;
			break;
		}
		if (_kbhit())                                                     //防止键盘输入影响
		{
			char ch = _getch();
			break;
		}
	}
}
void again()                                                     //判断是否重新来一局
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
	while (flaga == 0)                                          //获取鼠标操作
	{
		n = GetMouseMsg();
		int b = n.x;
		int a = n.y;
		if (n.uMsg == WM_LBUTTONDOWN)
		{
			if (b >= 200 && b <= 315 && a >= 200 && a <= 230)
			{
				flaga = 1;                                     //flaga代表鼠标操作，分别对应：再来，放弃，回到主菜单

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
void welcome()                                                    //欢迎页面
{
	initgraph(500, 640);
	IMAGE img;
	loadimage(&img, "welcome.jpg");
	putimage(0, 0, &img);
}
int main()
{
	welcome();
	Sleep(3000);                                                      //在欢迎页面延迟
	closegraph();
	while (flagc == 0)
	{
		prepare();
		mouse1();                                                     //选择难度
		if (flagclose == 1)
			closegraph();
		flagsave = 0;
		for (int i = 0; i < 20; i++)                                  //初始化区域状态（全部为空白）             
			for (int j = 0; j < 30; j++)
				state[i][j] = ' ';
		appear(row, col, numberboom, choice);                         //根据模式确定雷区大小
		while (1)
		{
			for (int i = 0; i < 20; i++)                              //初始化每个格子的状态（未展开）
				for (int j = 0; j < 30; j++)
				{
						flag[i][j] = 0;
				}
			initgraph((col + 3) * 35, (row + 3) * 35);                //绘制图形界面
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
			for (int i = 0; i < row; i++)                             //如果本次游戏为读盘状态，根据situation判断原先的格子是否已经展开并重新表示状态
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
					seed = rand();                                   //随机生成雷
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
			if (flagsave == 1)                                           //当选择存档并且退出，直接退出（flagc代表是否退出）
			{
				flagc = 1;
				break;
			}
			if (flagd == 1)                                              //flagd代表正常结束游戏，此时展开所有雷区
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
			else if (flagt == 1)                                                //投降状态，同样展开雷区，延迟时间改变
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
				flagti = 0;                                                       //初始化代表是否第一次点击雷区的变量
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
			time1 = 0;                                                            //初始化变量（针对读盘状态结束游戏）
			flagts = 0;
			boomnumber = numberboom;
			if (flagb == 1)                                                   //点击到雷的状况
			{
				initgraph(500, 650);
				IMAGE img;
				loadimage(&img, "lose1.jpg");
				putimage(0,0, &img);
			}
			else if (num == row * col - numberboom)                               //非雷区全部展开，获胜
			{
				initgraph(500, 650);
				IMAGE img;
				loadimage(&img, "win1.jpg");
				putimage(0, 0, &img);
			}
			Sleep(1000);
			again();
			if (flaga == 2)                                                       //选择结束游戏
			{
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						situation[i][j] = 0;
				flagc = 1;
				break;
			}
			if (flaga == 3)                                                       //选择回到主菜单
			{
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						situation[i][j] = 0;
				break;
			}
			flagsave = 0;                                                        //选择再玩一局的走到此处，初始化所有用于判断的变量
			flagts = 0;
			flaga = 0;
			flagb = 0;
			num = 0;
			flagd = 0;
			flagti = 0;
		}
		flaga = 0;                                                              //初始化所有用于判断的变量
		flagb = 0;
		num = 0;
		flagd = 0;
		flagti = 0;
		closegraph();
	}
	initgraph(500, 600);
	IMAGE img;
	loadimage(&img, "goodbye.jpg");                                            //关闭界面前输出结束语
	putimage(0, 0, &img);
	Sleep(3000);
	closegraph();
	return 0;

}