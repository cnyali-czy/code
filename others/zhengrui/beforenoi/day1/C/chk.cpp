/*
	Problem:	chk.cpp
	Time:		2021-07-13 12:28
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int main()
{
	FILE *ans = fopen("std.out", "r");
	FILE *out = fopen("C.out", "r");
	double x = 0, y = 0;
	while (fscanf(ans, "%lf", &x) != EOF)
	{
		fscanf(out, "%lf", &y);
		static int dfn = 0;++dfn;
		if (abs(x - y) / x > 1e-4)
		{
			printf("%d %.8lf\n", dfn, abs(x-y)/x);
			return 0;
		}
	}
	return 0;
}
