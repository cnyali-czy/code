/*
	Problem:	2056.cpp
	Time:		2020-02-18 17:39
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <set>
#include <ext/pb_ds/priority_queue.hpp>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
#ifndef CraZYali
#define getchar getchar_unlocked
#endif
	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

struct Multiset
{
	priority_queue <int> real, del;
	inline void push(int val) {real.push(val);}
	inline void erase(int val) {del.push(val);}
	inline int size() {return real.size() - del.size();}
	inline int top()
	{
		while (!del.empty() && real.top() == del.top()) del.pop(), real.pop();
		return real.top();
	}
	inline void pop()
	{
		while (!del.empty() && real.top() == del.top()) del.pop(), real.pop();
		real.pop();
	}
	inline void clear() {while (!real.empty()) real.pop();while (!del.empty()) del.pop();}
	inline int top2()
	{
		int x = top();pop();
		int res = top();
		push(x);
		return res;
	}
	inline int tot()
	{
		int x = top();pop();
		int res = x + top();
		push(x);
		return res;
	}
}g[maxn], f[maxn], ans;

bool vis[maxn];
int Max[maxn], siz[maxn], allnode, rt;
void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
	{
		findrt(to[i], x);
		chkmax(Max[x], siz[to[i]]);
		siz[x] += siz[to[i]];
	}
	chkmax(Max[x], allnode - siz[x]);
	if (!rt || Max[x] < Max[rt]) rt = x;
}

int par[maxn], now;

void dfs2(int x, int d = 1, int fa = 0)
{
	g[rt].push(d);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
		dfs2(to[i], d + 1, x);
}

void dfs(int x)
{
	vis[x] = 1;
	now = x;
	f[x].push(0);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		allnode = siz[to[i]];
		rt = 0;
		findrt(to[i]);
		par[rt] = x;
		dfs2(to[i]);
		f[x].push(g[rt].top());
		dfs(rt);
	}
	if (f[x].size() >= 2) ans.push(f[x].tot());
	else ans.push(f[x].tot());
}

int n, m;
inline int min(int x, int y) {if (x < y) return x;return y;}

namespace lca
{
	int st[maxn << 1][18], fir[maxn << 1], dfn, dep[maxn], lg[maxn << 1];
	void dfs(int x, int fa)
	{
		fir[x] = ++dfn;
		st[dfn][0] = dep[x];
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dep[to[i]] = dep[x] + 1;
			dfs(to[i], x);
			st[++dfn][0] = dep[x];
		}
	}
	inline int query(int l, int r)
	{
		l = fir[l];r = fir[r];if (l > r) swap(l, r);
		int k = lg[r - l + 1];
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	}
	void init()
	{
		dfs(1, 0);
		REP(i, 2, dfn) lg[i] = lg[i >> 1] + 1;
		DEP(i, dfn, 1)
			for (int j = 1; i + (1 << j) - 1 <= dfn; j++)
				st[i][j] = min(st[i][j-1], st[i + (1 << j-1)][j-1]);
	}
	inline int dist(int x, int y) {return dep[x] + dep[y] - 2 * query(x, y);}
}
using lca::dist;
bool col[maxn];
int main()
{
#ifdef CraZYali
	file("2056");
#endif
	ans.push(-1);
	n = read<int>();
	REP(i, 2, n) {int x(read<int>()), y(read<int>());add(x, y);add(y, x);}
	allnode = n;
	lca::init();
	findrt(1);dfs(rt);
	int m = read<int>();
	while (m--)
	{
		char c = getchar();
		while (!isalpha(c)) c = getchar();
		if (c == 'G') cout << ans.top() << '\n';
		else
		{
			int x = read<int>();
			if (!col[x])
			{
				if (f[x].size() >= 2) ans.erase(f[x].tot());
				f[x].erase(0);
				if (f[x].size() >= 2) ans.push(f[x].tot());
				for (int i = x; par[i]; i = par[i])
				{
					if (f[par[i]].size() >= 2) ans.erase(f[par[i]].tot());
					f[par[i]].erase(g[i].top());
					g[i].erase(dist(x, par[i]));
					if (g[i].size()) f[par[i]].push(g[i].top());
					if (f[par[i]].size() >= 2) ans.push(f[par[i]].tot());
				}
			}
			else
			{
				if (f[x].size() >= 2) ans.erase(f[x].tot());
				f[x].push(0);
				if (f[x].size() >= 2) ans.push(f[x].tot());
				for (int i = x; par[i]; i = par[i])
				{
					if (f[par[i]].size() >= 2) ans.erase(f[par[i]].tot());
					if (g[i].size()) f[par[i]].erase(g[i].top());
					g[i].push(dist(x, par[i]));
					f[par[i]].push(g[i].top());
					if (f[par[i]].size() >= 2) ans.push(f[par[i]].tot());
				}
			}
			col[x] ^= 1;
		}
	}
	return 0;
}
