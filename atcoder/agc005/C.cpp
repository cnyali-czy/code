/*
	Problem:	2061.cpp
	Time:		2021-04-28 10:51
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
const int maxn = 100 + 5;

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

int n, a[maxn], c[maxn];

int main()
{
#ifdef CraZYali
	file("2061");
#endif
	n = read<int>();int mx = 0;
	REP(i, 1, n) c[a[i] = read<int>()]++, mx = max(mx, a[i]);
	REP(i, 1, mx - 1 >> 1) if (c[i])
	{
		puts("Impossible");
		return 0;
	}
	if (mx & 1)
	{
		REP(i, mx + 1 >> 1, mx) if (c[i] <= 1)
		{
			puts("Impossible");
			return 0;
		}
		if (c[mx + 1 >> 1] != 2)
		{
			puts("Impossible");
			return 0;
		}
	}
	else
	{
		REP(i, (mx >> 1) + 1, mx) if (c[i] <= 1)
		{
			puts("Impossible");
			return 0;
		}
		if (c[mx >> 1] != 1)
		{
			puts("Impossible");
			return 0;
		}
	}
	puts("Possible");
	return 0;
}
