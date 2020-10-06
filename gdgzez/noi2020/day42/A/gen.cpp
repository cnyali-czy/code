/*
	Problem:	gen.cpp
	Time:		2020-08-14 09:45
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
inline int randint(int l, int r)
{
	auto res = hh();
	if( res<0)res=-res;
	return res%(r-l+1)+l;
}
#include <ctime>
int main()
{
	freopen("A.in","w",stdout);	
	hh=mt19937(time(0));
	int n = 5000, l = randint(1, n * .2), r = randint(l, n);
	printf("%d %d %d\n", n, l, r);
	REP(i, 1, n)
		printf("%d%c", -1 + hh() % 3, i == end_i ? '\n' : ' ');
	return 0;
}
