/*
	Problem:	gen.cpp
	Time:		2020-08-13 10:23
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <random>
#include <iostream>
#include <cstdio>

using namespace std;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

mt19937 hh;
inline int randint(int l,int r)
{
	auto res=hh();
	if(res<0)res=-res;
	return res%(r-l+1)+l;
}

int main()
{
	freopen("A.in", "w", stdout);
	int n = 800, m = 1000, q = 1e5;
	cout << n << ' ' << m << ' ' << q << endl;
	REP(i,1,n)
	{
		REP(j,1,m)
		{
			if(hh()%150==0)putchar('1');
			else putchar('0');
		}
		puts("");
	}
	while(q--)
	{
		int x1=randint(1,n),y1=randint(1,m);
		int x2=randint(1,n),y2=randint(1,m);
		if(hh()%100==0)x2=x2,y2=y1;
		int lim=1000;
		chkmin(lim,min(x1, x2));
		chkmin(lim,min(y1, y2));
		printf("%d %d %d %d %d\n",x1,y1,x2,y2,randint(1,lim));
	}
	return 0;
}
