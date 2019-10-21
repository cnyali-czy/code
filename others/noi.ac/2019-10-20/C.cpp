/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.20 09:59
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

#define pos puts("POSSIBLE");
#define empty puts("........ ........")

int id[] =
{
	0,1,1,2,1,0,2,3,1,2,0,4,0,0,0,5,1,0,2,4,0,0,4,6,2,4,4,7,0,0,8,9,1,0,0,0,2,0,4,5,0,0,0,0,0,0,0,10,2,0,4,8,4,0,7,9,3,5,6,9,5,10,9,11,1,0,0,0,0,0,0,0,2,3,0,5,0,0,0,12,0,0,0,0,0,0,0,0,4,6,8,9,0,0,13,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,0,0,0,0,0,0,0,0,5,16,17,18,19,20,21,22,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,3,5,0,0,5,16,4,8,6,9,0,0,17,18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,6,17,8,0,9,18,6,17,23,24,17,25,24,26,2,0,0,0,0,0,0,0,4,5,0,10,0,0,0,15,4,0,5,10,0,0,19,20,7,9,9,11,0,0,21,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,27,8,0,17,25,13,0,21,28,9,18,24,26,21,28,29,30,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,3,0,5,12,0,0,0,0,0,0,0,15,4,0,8,13,6,0,9,14,5,19,17,21,16,20,18,22,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,0,10,20,25,28,20,32,28,33,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,5,19,0,0,10,20,8,13,17,21,0,0,25,28,4,0,0,0,5,0,10,15,0,0,0,0,0,0,0,27,7,0,9,21,9,0,11,22,9,21,24,29,18,28,26,30,3,0,0,0,0,0,0,0,5,12,0,15,0,0,0,31,6,0,16,20,0,0,20,32,9,14,18,22,0,0,28,33,5,0,0,0,12,0,15,31,10,15,0,27,15,31,27,34,9,0,18,28,14,0,22,33,11,22,26,30,22,33,30,35
};
int back[] = 
{
	0,1,3,7,11,15,23,27,30,31,47,63,79,94,95,111,121,122,123,124,125,126,127,186,187,189,191,239,247,254,255,367,381,383,495,511
};

int get_ccc(char a[3][3])
{
	int ccc(0);
	REP(i, 0, 2)
		REP(j, 0, 2)
		ccc |= (a[i][j] << (i * 3 + j));
	return ccc;
}

char a[3][3], b[3][3];

char output[8][8];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	int T;
	scanf("%d\n", &T);
	while (T--)
	{
		REP(i, 0, 2)
		{
			scanf("%s %s\n", a[i], b[i]);
			REP(j, 0, 2)
			{
				a[i][j] = (a[i][j] == '@');
				b[i][j] = (b[i][j] == '@');
			}
		}
		int ida = id[get_ccc(a)], backa = back[ida];
		int idb = id[get_ccc(b)], backb = back[idb];
		REP(i, 0, 7) REP(j, 0, 7) output[i][j] = 0;
		REP(i, 0, 2)
			REP(j, 0, 2)
			{
				a[i][j] = !!(backa & (1 << (i * 3 + j)));
				b[i][j] = !!(backb & (1 << (i * 3 + j)));
			}
		if (__builtin_popcount(backa) == 1)
		{
			pos;
			int cnt(0);
			REP(i, 0, 2)
			{
				REP(j, 0, 2)
					if (b[i][j]) printf("%d", ++cnt);
					else putchar('.');
				REP(j, 3, 7) putchar('.');
				putchar(' ');
				REP(j, 0, 2) putchar(b[i][j] ? '1' : '.');
				REP(j, 3, 7) putchar('.');
				putchar(10);
			}
			REP(i, 3, 7) empty;
		}
		else if (__builtin_popcount(backb) == 1)
		{
			pos;
			int cnt(0);
			REP(i, 0, 2)
			{
				REP(j, 0, 2) putchar(a[i][j] ? '1' : '.');
				REP(j, 3, 7) putchar('.');
				putchar(' ');
				REP(j, 0, 2)
					if (a[i][j]) printf("%d", ++cnt);
					else putchar('.');
				REP(j, 3, 7) putchar('.');
				putchar(10);
			}
			REP(i, 3, 7) empty;
		}
		else if (ida == 2)
		{
			if (idb == 3)
			{
				pos;
				puts("123..... 111.....");
				puts("123..... 222.....");
				REP(i, 3, 8) empty;
			}
			else if (idb == 4)
			{
				pos;
				puts("123..... 112.....");
				puts("123..... 122.....");
				REP(i, 3, 8) empty;
			}
			else if (idb == 5)
			{
				pos;
				puts("122..... 111.....");
				puts("1....... 1.......");
				puts("3....... 2.......");
				puts("344..... 222.....");
				REP(i, 5, 8) empty;
			}
			else if (idb == 6)
			{
				pos;
				puts("1122.... 1112....");
				puts("3344.... 4122....");
				puts("5566.... 4432....");
				puts("7788.... 4333....");
				REP(i, 5, 8) empty;
			}
			else if (idb == 7)
			{
				pos;
				puts("11...... 11......");
				puts("22...... 11......");
				REP(i, 3, 8) empty;
			}
			else if (idb == 8)
			{
				pos;
				puts(".11..... .11.....");
				puts("22...... 11......");
				REP(i, 3, 8) empty;
			}
			else if (idb == 9)
			{
				pos;
				puts("12345... 11122...");
				puts("12345... 11222...");
				REP(i, 3, 8) empty;
			}
			else if (idb == 10)
			{
				pos;
				puts("1.2..... 1.1.....");
				puts("132..... 111.....");
				puts("435..... 222.....");
				puts("4.5..... 2.2.....");
				REP(i, 5, 8) empty;
			}
			else if (idb == 11)
			{
				pos;
				puts("123..... 111.....");
				puts("123..... 111.....");
				REP(i, 3, 8) empty;
			}
			else if (idb == 12)
			{
				pos;
				puts("112233.. 111222..");
				puts("4....5.. 1....2..");
				puts("4....5.. 1....2..");
				REP(i, 4, 8) empty;
			}
			else if (idb == 13)
			{
				pos;
				puts(".2334... .1122...");
				puts("12..45.. 11..22..");
				puts("1....5.. 1....2..");
				REP(i, 4, 8) empty;
			}
			else if (idb == 14)
			{
				pos;
				puts("112233.. 111222..");
				puts("44..55.. 11..22..");
				puts("6....7.. 1....2..");
				REP(i, 4, 8) empty;
			}
			else if (idb == 15)
			{
				pos;
				puts("112..... 111.....");
				puts("3.2..... 1.1.....");
				puts("3....... 1.......");
				REP(i, 4, 8) empty;
			}
		}
		else puts("IMPOSSIBLE");
	}
	return 0;
}
