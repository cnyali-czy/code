/*
	Problem:	2268.cpp
	Time:		2021-05-12 21:33
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
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10, inf = 1e9;

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

int n;
char imp[maxn];
i64 ans;

int d[maxn], siz[maxn], mx[maxn], se[maxn];
void dfs1(int x, int fa = 0)
{
	if (imp[x] == '1') d[x] = 0, siz[x] = 1;
	else d[x] = inf;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs1(to[i], x);
		siz[x] += siz[to[i]];
		if (mx[to[i]] + 1 > mx[x])
		{
			se[x] = mx[x];
			mx[x] = mx[to[i]] + 1;
		}
		else se[x] = max(se[x], mx[to[i]] + 1);
		if (siz[to[i]]) d[x] = min(d[x], mx[to[i]] + 1);
	}
}
void dfs2(int x, int fa = 0)
{
	int R = min(se[x] + 1, mx[x] - 1);
	if (d[x] <= R) ans += R - d[x] + 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		int New = mx[x] + 1;
		if (mx[to[i]] + 1 == mx[x]) New = se[x] + 1;
		if (New > mx[to[i]])
		{
			se[to[i]] = mx[to[i]];
			mx[to[i]] = New;
		}
		else se[to[i]] = max(se[to[i]], New);
		if (siz[1] > siz[to[i]]) d[to[i]] = min(d[to[i]], New);
		dfs2(to[i], x);
	}
}
int main()
{
#ifdef CraZYali
	file("2268");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	scanf("%s", imp + 1);
	dfs1(1);
	dfs2(1);
	cout << ans + 1 << endl;
	return 0;
}
