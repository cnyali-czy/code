/*
	Problem:	5903.cpp
	Time:		2020-08-13 21:35
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
const int maxn = 5e5 + 10;

int bg[maxn], ne[maxn], to[maxn], e;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, q, rt, fa[maxn], lstans;
long long ans;

namespace gen
{
#define ui unsigned int
	ui s;

	inline ui get(ui x)
	{
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		return s = x; 
	}
}
using namespace gen;

namespace bf1
{
	int siz[maxn], hvy[maxn], dep[maxn], top[maxn];
	void dfs1(int x)
	{
		dep[x] = dep[fa[x]] + 1;
		siz[x] = 1;
		for (int i = bg[x]; i; i = ne[i])
		{
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
	}
	int dfn[maxn], back[maxn], dfs_clock;
	void dfs2(int x, int y)
	{
		back[dfn[x] = ++dfs_clock] = x;
		top[x] = y;
		if (!hvy[x]) return;
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ hvy[x])
			dfs2(to[i], to[i]);
	}
	int ask(int x, int k)
	{
		int y = x;
		while (1)
			if (dep[x] - dep[top[y]] < k) y = fa[top[y]];
			else return back[dfn[top[y]] + dep[x] - dep[top[y]] - k];
	}
	int main()
	{
		dfs1(rt);dfs2(rt, rt);
		REP(i, 1, q)
		{
			int x = (get(s) ^ lstans) % n + 1;
			int k = (get(s) ^ lstans) % dep[x];
			lstans = ask(x, k);
			ans ^= 1ll * i * lstans;
		}
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("5903");
#endif
	cin >> n >> q >> s;
	REP(i, 1, n)
	{
		fa[i] = read<int>();
		if (!fa[i]) rt = i;
		else add(fa[i], i);
	}
	return bf1 :: main();
}
