/*
	Problem:	A.cpp
	Time:		2020-06-09 19:15
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxN = 1.45e7;
#define i64 unsigned int
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

int n, m, t, a[maxn];
vector <pair <int, int> > E[maxn];

namespace kru
{
	const int maxn = ::maxn << 1;
	int bg[maxn], ne[maxn], to[maxn], e;
	inline void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	int fa[maxn], v[maxn];
	int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
	int N, anc[maxn][19], dfn[maxn], siz[maxn], dfs_clock;
	void dfs(int x)
	{
		dfn[x] = ++dfs_clock;
		siz[x] = 1;
		for (int i = bg[x]; i; i = ne[i])
		{
			dfs(to[i]);
			siz[x] += siz[to[i]];
		}
	}
	void build()
	{
		REP(i, 1, n + n) fa[i] = i;
		N = n;
		DEP(w, 100000, 1)
			for (auto e : E[w])
			{
				int x = find(e.first), y = find(e.second);
				anc[x][0] = anc[y][0] = ++N;
				fa[x] = fa[y] = N;
				add(N, x);add(N, y);
				v[N] = w;
			}
		REP(j, 1, 18)
			DEP(i, N, 1) anc[i][j] = anc[anc[i][j - 1]][j - 1];
		dfs(N);
	}
	int find(int x, int d)
	{
		DEP(i, 18, 0) if (anc[x][i] && v[anc[x][i]] >= d) x = anc[x][i];
		return x;
	}
}
int dfn[maxn], dfs_clock, siz[maxn];
void dfs(int x, int fa = 0)
{
	siz[x] = 1;
	dfn[x] = ++dfs_clock;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		siz[x] += siz[to[i]];
	}
}
int rt[maxn];
int ls[maxN], rs[maxN], cur;
i64 s[maxN], tag[maxN];

#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

inline void maintain(int &p, int l, int r, i64 v)
{
	if (!p) p = ++cur;
	tag[p] += v;
	s[p] += v * (r - l + 1);
}
inline void pushdown(int p, int l, int r)
{
	maintain(lson, tag[p]);
	maintain(rson, tag[p]);
	tag[p] = 0;
}
void update(int &p, int l, int r, int L, int R, int v)
{
	if (!p) p = ++cur;
	if (L <= l && r <= R) maintain(p, l, r, v);
	else
	{
		if (tag[p]) pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, v);
		if (R >  mid) update(rson, L, R, v);
		s[p] = s[ls[p]] + s[rs[p]];
	}
}
i64 query(int p, int l, int r, int pos)
{
	if (l == r) return s[p];
	if (tag[p]) pushdown(p, l, r);
	if (pos <= mid) return query(lson, pos);
	else			return query(rson, pos);
}

void update(int l, int r, int L, int R, int v)
{
	r++;
	while (l <= n)
	{
		update(rt[l], 1, kru :: N, L, R, v);
		l += l & -l;
	}
	while (r <= n)
	{
		update(rt[r], 1, kru :: N, L, R, -v);
		r += r & -r;
	}
}
i64 query(int x)
{
	i64 res = 0;
	int p = dfn[x];
	while (p > 0)
	{
		res += query(rt[p], 1, kru :: N, kru :: dfn[x]);
		p &= (p - 1);
	}
	return res;
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();t = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y);add(y, x);
		E[z].emplace_back(x, y);
	}
	dfs(1);
	kru :: build();
	i64 lastans = 0;
	while (m--)
	{
		int opt = read<int>();
		if (opt == 1)
		{
			int x = read<int>();
			if (t) x = (x + lastans) % n + 1;
			printf("%u\n", lastans = (a[x] + query(x)));
		}
		else
		{
			int v = read<int>(), d = read<int>(), x = read<int>();
			if (t) x = (x + lastans) % n + 1;
			int Anc = kru :: find(x, d);
			update(dfn[x], dfn[x] + siz[x] - 1, kru :: dfn[Anc], kru :: dfn[Anc] + kru :: siz[Anc] - 1, v);
		}
	}
	return 0;
}
