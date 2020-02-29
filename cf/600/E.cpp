/*
	Problem:	E.cpp
	Time:		2020-02-29 17:35
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <map>
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, c[maxn], cc[maxn];

int dfn[maxn], dfs_clock, siz[maxn], hvy[maxn], fa[maxn];

map <int, long long, greater <int> > all;
int cnt[maxn];
inline void ins(int x)
{
	if (cnt[x])
	{
		all[cnt[x]] -= x;
		if (!all[cnt[x]]) all.erase(cnt[x]);
	}
	all[++cnt[x]] += x;
}
inline void del(int x)
{
	all[cnt[x]] -= x;
	if (!all[cnt[x]]) all.erase(cnt[x]);
	if (--cnt[x]) all[cnt[x]] += x;
}

void dfs1(int x)
{
	cc[dfn[x] = ++dfs_clock] = c[x];
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if(siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
long long ans[maxn];
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
	{
		dfs(to[i]);
		REP(j, dfn[to[i]], dfn[to[i]] + siz[to[i]] - 1) del(cc[j]);
	}
	if (hvy[x]) dfs(hvy[x]);
	ins(c[x]);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
		REP(j, dfn[to[i]], dfn[to[i]] + siz[to[i]] - 1) ins(cc[j]);
	ans[x] = all.begin() -> second;
}

int main()
{
#ifdef CraZYali
	file("E");
	freopen("E.err", "w", stderr);
#endif
	n = read<int>();
	REP(i, 1, n) c[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	dfs1(1);
	dfs(1);
	REP(i, 1, n) cout << ans[i] << ' ' ;
	return 0;
}
