/*
	Problem:	2293.cpp
	Time:		2021-05-14 09:32
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

int n;
int a[maxn], ban[maxn];
void dfs(int x, int fa = 0)
{
	int t = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		t |= (ban[x] & ban[to[i]]);
		ban[x] |= ban[to[i]];
	}
	int k = t ? 32 - __builtin_clz((unsigned)t) : 0;
	a[x] = __builtin_ctz((ban[x] | ((1 << k) - 1)) + 1);
	ban[x] = (ban[x] >> a[x] | 1) << a[x];
}
int main()
{
#ifdef CraZYali
	file("2293");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dfs(1);
	int ans = 0;
	REP(i, 1, n) ans = max(ans, a[i]);
	cout << ans << endl;
	return 0;
}
