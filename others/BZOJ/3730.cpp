/*
	Problem:	3730.cpp
	Time:		2020-02-16 17:48
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxN = 1.8e7;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add(int x, int y)
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

int n, m, v[maxn], ls[maxN], rs[maxN], s[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

void insert(int &p, int l, int r, int pos, int val)
{
	if (!p) p = ++cur;
	s[p] += val;
	if (l == r) return;
	if (pos <= mid) insert(lson, pos, val);
	else			insert(rson, pos, val);
}
int query(int p, int l, int r, int L, int R)
{
	if (!p) return 0;
	if (L <= l && r <= R) return s[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}
namespace lca
{
	int lg[maxn << 1];
	int dfs_clock, dep[maxn], fir[maxn], Min[maxn << 1][19], Pos[maxn << 1][19];
	void dfs(int x, int fa = 0)
	{
		fir[x] = ++dfs_clock;
		dep[x] = dep[fa] + 1;
		Min[dfs_clock][0] = dep[x];Pos[dfs_clock][0] = x;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs(to[i], x);
			++dfs_clock;
			Min[dfs_clock][0] = dep[x];Pos[dfs_clock][0] = x;
		}
	}
	void init()
	{
		REP(i, 2, n + n) lg[i] = lg[i >> 1] + 1;
		dfs(1);
		DEP(i, n + n, 1)
			for (int j = 1; i + (1 << j) - 1 <= n + n; j++)
				if (dep[Pos[i][j-1]] < dep[Pos[i + (1 << j - 1)][j-1]])
					Pos[i][j] = Pos[i][j - 1];
				else
					Pos[i][j] = Pos[i + (1 << j - 1)][j - 1];
	}
	inline int lca(int x, int y)
	{
		int l = fir[x], r = fir[y];if (l > r) swap(l, r);
		int k = lg[r - l + 1];
		int pos1 = Pos[l][k], pos2 = Pos[r - (1 << k) + 1][k];
		return dep[pos1] < dep[pos2] ? pos1 : pos2;
	}
	inline int dist(int x, int y) {return dep[x] + dep[y] - 2 * dep[lca(x, y)];}
}
int dep[maxn];

namespace cd
{
	int siz[maxn], Max[maxn], allnode, rt;
	bool vis[maxn];

	void findrt(int x, int fa = 0)
	{
		siz[x] = 1;Max[x] = 0;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
		{
			findrt(to[i], x);
			siz[x] += siz[to[i]];
			chkmax(Max[x], siz[to[i]]);
		}
		chkmax(Max[x], allnode - siz[x]);
		if (Max[x] < Max[rt] || !rt) rt = x;
	}

	int tfa[maxn], drt[maxn], crt[maxn], now;
	void DFS(int x, int d, int fa = 0)
	{
		insert(crt[now], 0, n, d, v[x]);
		for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
			DFS(to[i], d + 1, x);
	}
	void DFS2(int x, int d, int fa = 0)
	{
		insert(drt[now], 0, n, d, v[x]);
		for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
			DFS2(to[i], d + 1, x);
	}
	void dfs(int x)
	{
		now = x;
		DFS2(x, 0);

		vis[x] = 1;
		for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
		{
			allnode = siz[to[i]];
			rt = 0;
			dep[to[i]] = dep[x] + 1;
			findrt(to[i]);
			tfa[rt] = x;
			now = rt;
			DFS(to[i], 1);
			dfs(rt);
		}
	}

	void init()
	{
		allnode = 0;
		findrt(1);
		dfs(rt);
	}

	int query(int x, int y)
	{
		int res = ::query(drt[x], 0, n, 0, y);
		int nww = 0;
		for (int i = x; tfa[i]; i = tfa[i])
		{
			nww = lca::dist(x, tfa[i]);
			res += ::query(drt[tfa[i]], 0, n, 0, y - nww);
			res -= ::query(crt[i], 0, n, 0, y - nww);
		}
		return res;
	}
	void update(int x, int y)
	{
		int nww = 0;
		insert(drt[x], 0, n, 0, y - v[x]);
		for (int i = x; tfa[i]; i = tfa[i])
		{
			nww = lca::dist(x, tfa[i]);
			insert(drt[tfa[i]], 0, n, nww, y - v[x]);
			insert(crt[i], 0, n, nww, y - v[x]);
		}
		v[x] = y;
	}
}

int main()
{
#ifdef CraZYali
	file("3730");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) v[i] = read<int>();
	REP(i, 2, n) {int x(read<int>()), y(read<int>());add(x, y);add(y, x);}
	lca::init();
	cd::init();
	int lastans = 0;
	while (m--)
	{
//		lastans = 0;
		int opt = read<int>(), x(lastans ^ read<int>()), y(lastans ^ read<int>());
		if (opt == 0) printf("%d\n", lastans = cd::query(x, y));
		else cd::update(x, y);
	}
//	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
