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
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;

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

int m, n, T;
int ch[maxn][2], v[maxn], fa[maxn], flag;
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (rs(fa[x]) == x)
void dfs(int x, int y)
{
	if (x == T) {flag = 1;return;}
	if (y == v[x]) return;
	if (!x) return;
	dfs(ch[x][y >= v[x]], y);
}

namespace bf
{
	void work()
	{
		while (m--)
		{
			int opt = read<int>(), x = read<int>();
			if (opt == 1) v[x] = read<int>();
			else if (opt == 2) swap(ls(x), rs(x));
			else
			{
				T = x;
				flag = 0;
				dfs(1, v[x]);
				puts(flag ? "YES" : "NO");
			}
		}
	}
}
namespace cheat
{
	int dfn[maxn], dfs_clock, siz[maxn], dep[maxn], hvy[maxn], top[maxn];
	void dfs1(int x)
	{
		siz[x] = 1;
		REP(j, 0, 1) if (ch[x][j])
		{
			int y = ch[x][j];
			dep[y] = dep[x] + 1;
			dfs1(y);
			siz[x] += siz[y];
			if (siz[y] > siz[hvy[x]]) hvy[x] = y;
		}
	}
	void dfs2(int x, int y)
	{
		top[x] = y;
		dfn[x] = ++dfs_clock;
		if (!hvy[x]) return;
		dfs2(hvy[x], y);
		REP(j, 0, 1) if (ch[x][j] && ch[x][j] != hvy[x])
			dfs2(ch[x][j], ch[x][j]);
	}

	struct fenwick
	{
		int c[maxn];
		fenwick() {memset(c, 0, sizeof c);}
		void add(int x, int y)
		{
			while (x <= n)
			{
				c[x] += y;
				x += x & -x;
			}
		}
		void add(int l, int r, int v)
		{
			add(l, v);
			add(r + 1, -v);
		}
		int sum(int x)
		{
			int y = 0;
			while (x > 0)
			{
				y += c[x];
				x &= (x - 1);
			}
			return y;
		}
		int sum(int l, int r)
		{
			l--;
			int y = 0;
			while (r > l) y += c[r], r &= (r - 1);
			while (l > r) y -= c[l], l &= (l - 1);
			return y;
		}
	}good, gg;

	const int maxN = 2e7;

#define Lson Ls[p], l, mid
#define Rson Rs[p], mid + 1, r
#define mid (l + r >> 1)
	int Ls[maxN], Rs[maxN], s[maxN], cur, rt[maxn * 2];
	void insert(int &p, int l, int r, int pos, int val = 1)
	{
		if (!p) p = ++cur;
		s[p] += val;
		if (l == r) return;
		if (pos <= mid)	insert(Lson, pos, val);
		else			insert(Rson, pos, val);
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (!s[p]) return 0;
		if (L <= l && r <= R) return s[p];
		else
		{
			if (R <= mid) return query(Lson, L, R);
			if (L >  mid) return query(Rson, L, R);
			return query(Lson, L, R) + query(Rson, L, R);
		}
	}
	unordered_map <int, int> Id;int id_cur;
	bool gged[maxn], gooded[maxn];
	int cnt(int x)
	{
		int v = Id[::v[x]];
		int res = 0;
		while (top[x] ^ 1)
		{
			res += query(rt[v], 1, n, dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		return res + query(rt[v], 1, n, dfn[1], dfn[x]);
	}
	int cnt(int x, fenwick& f)
	{
		int res = 0;
		while (top[x] ^ 1)
		{
			res += f.sum(dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		return res + f.sum(dfn[1], dfn[x]);
	}
	void maintain1(int i)
	{
		bool flag;
		if (get(i)) flag = v[i] > v[fa[i]];
		else		flag = v[i] < v[fa[i]];
		if (flag)
		{
			good.add(dfn[i], 1);
			gooded[i] = 1;
		}
	}
	void maintain2(int i)
	{
		if (cnt(i) > 1)
		{
			gg.add(dfn[i], 1);
			gged[i] = 1;
		}
	}
	void work()
	{
		dfs1(1);dfs2(1, 1);
		REP(i, 2, n) maintain1(i);
		REP(i, 1, n)
		{
			if (!Id[v[i]]) Id[v[i]] = ++id_cur;
			insert(rt[Id[v[i]]], 1, n, dfn[i]);
		}
		REP(i, 1, n) maintain2(i);
		while (m--)
		{
			int opt = read<int>(), x = read<int>();
			if (opt == 1)
			{
				if (gooded[x]) good.add(dfn[x], -1);
				if (gged[x]) gg.add(dfn[x], -1);
				gged[x] = gooded[x] = 0;
				insert(rt[Id[v[x]]], 1, n, dfn[x], -1);
				v[x] = read<int>();
				if (!Id[v[x]]) Id[v[x]] = ++id_cur;
				insert(rt[Id[v[x]]], 1, n, dfn[x]);
				if (x != 1) maintain1(x);
				maintain2(x);
				if (ls(x)) maintain1(ls(x));
				if (rs(x)) maintain1(rs(x));
			}
			else
			{
				int qaqgood = cnt(x, good);
				int qaqgg = cnt(x, gg);
				if (qaqgood != dep[x] || qaqgg) puts("NO");
				else puts("YES");
			}
		}
#ifdef CraZYali
		DEBUG;
#endif
	}
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		v[i] = read<int>(), ls(i) = read<int>(), rs(i) = read<int>();
		if (ls(i)) fa[ls(i)] = i;
		if (rs(i)) fa[rs(i)] = i;
	}
	if (0 && n <= 5000 && m <= 5000) bf :: work();
	else cheat :: work();
	return 0;
}
