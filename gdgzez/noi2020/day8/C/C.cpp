#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 6e5 + 10, MOD = 998244353;

inline void inc(int &x, int y) {x += y; if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y; if (x <    0) x += MOD;}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m, q, N;
vector <int> G[maxn], tG[maxn];

inline void Add(int x, int y, vector <int> G[] = ::G)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}
int dfn[maxn], dfs_clock, fa[maxn], gg[maxn];
void arrange(int x, int y)
{
	Add(x, N, tG);
	if (x == y) return;
	gg[x] = 1;
	arrange(fa[x], y);
}
void dfs0(int x, int from = 0)
{
	dfn[x] = ++dfs_clock;
	for (int y : G[x]) if (from ^ y)
	{
		if (!dfn[y])
		{
			fa[y] = x;
			dfs0(y, x);
			if (!gg[y]) Add(x, y, tG);
		}
		else if (dfn[y] < dfn[x])
		{
			++N;
			arrange(x, y);
		}
	}
}

int siz[maxn], hvy[maxn], dep[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int y : G[x]) if (!siz[y])
	{
		fa[y] = x;
		dep[y] = dep[x] + 1;
		dfs1(y);
		siz[x] += siz[y];
		if (siz[y] > siz[hvy[x]]) hvy[x] = y;
	}
}
int top[maxn];
void dfs2(int x, int y)
{
	top[x] = y;
	dfn[x] = ++dfs_clock;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int to : G[x]) if (to ^ fa[x] && to ^ hvy[x])
		dfs2(to, to);
}

int c[maxn], w[maxn];
void add(int x, int y)
{
	while (x <= N)
	{
		inc(c[x], y);
		x += x & -x;
	}
}
void add(int l, int r, int v)
{
	add(l, v);
	add(r + 1, MOD - v);
}
int sum(int x)
{
	int y = 0;
	while (x > 0)
	{
		inc(y, c[x]);
		x &= (x - 1);
	}
	return y;
}
void modify(int x, int y, int v)
{
	while (top[x] ^ top[y])
	{
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		add(dfn[top[x]], dfn[x], v);
		x = fa[top[x]];
	}
	if (dfn[x] > dfn[y]) swap(x, y);
	add(dfn[x], dfn[y], v);
	if (fa[x] > n) inc(w[x], v);
	else if (x > n) inc(w[fa[x]], v);
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	while (m--) Add(read<int>(), read<int>());
	N = n;
	dfs0(1);
//	for (int i = 1; i <= n ; i ++) printf("%d%c", dfn[i], i == n ? '\n' : ' ' );
//	for (int i = 1; i <= n ; i ++) printf("%d%c", gg[i], i == n ? '\n' : ' ' );
//	cout << N << endl;
	REP(i, 1, N) swap(G[i], tG[i]);
//	REP(x, 1, N) for (int y : G[x] )printf("%d %d\n", x, y);fflush(stdout);
	dfs1(1);
	dfs_clock = 0;
	dfs2(1, 1);
	while (q--)
	{
		int opt = read<int>(), x = read<int>();
		if (!opt)
		{
			int y = read<int>(), v = read<int>();
			modify(x, y, v);
		}
		else
		{
			int ans = w[x];
			if (fa[x] <= n)	inc(ans, sum(dfn[x]));
			else			inc(ans, sum(dfn[fa[x]]));
			cout << ans << '\n';
		}
	}
	return 0;
}
