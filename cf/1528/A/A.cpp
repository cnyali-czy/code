/*
	Problem:	A.cpp
	Time:		2021-06-24 14:44
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
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, a[maxn][2], f[maxn][2];
void dfs(int x, int fa = 0)
{
	f[x][0] = f[x][1] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		f[x][0] += max(abs(a[x][0] - a[to[i]][0]) + f[to[i]][0], abs(a[x][0] - a[to[i]][1]) + f[to[i]][1]);
		f[x][1] += max(abs(a[x][1] - a[to[i]][0]) + f[to[i]][0], abs(a[x][1] - a[to[i]][1]) + f[to[i]][1]);
	}
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) a[i][0] = read<int>(), a[i][1] = read<int>();
		REP(i, 1, n) bg[i] = 0;e = 0;
		REP(i, 2, n)
		{
			int x = read<int>(), y = read<int>();
			add(x, y);add(y, x);
		}
		dfs(1);
		printf("%lld\n", max(f[1][0], f[1][1]));
	}
	return 0;
}
