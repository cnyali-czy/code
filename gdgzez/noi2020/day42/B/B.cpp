/*
	Problem:	B.cpp
	Time:		2020-08-14 16:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20;

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

int n, a[maxn];

namespace bf
{
	int g[1 << maxn], lg[1 << maxn];
	bool sg[1 << maxn];
	double f[1 << maxn];
	void work()
	{
		REP(i, 1, n - 1) lg[1 << i]  = i;
		REP(i, 1, (1 << n) - 1) sg[i] = 0;
		const int lim = (1 << n) - 1;
		REP(i, 1, (1 << n) - 1)
		{
			g[i] = __gcd(g[i & (i - 1)], a[lg[i & -i]]);
		}
		sg[0] = 1;
		REP(i, 0, (1 << n) - 1)
		{
//			if (g[lim ^ i] == 1) {sg[i] = 1;continue;}
			for (int j = i & (i - 1); j; j = (j - 1) & i)
				if (!sg[j] || g[lim ^ j] == 1)
				{
					sg[i] = 1;
					break;
				}
		}
		REP(i,0,lim)printf("%d%c",sg[i],i==end_i?'\n': ' ');
//		printf("%d ", sg[lim]);
	}
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	REP(Case, 1, read<int>())
	{
		n = read<int>();
		REP(i, 0, n - 1) a[i] = read<int>();
		bf :: work();
	}
	return 0;
}
