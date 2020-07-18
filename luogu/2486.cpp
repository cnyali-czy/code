/*
	Problem:	2486.cpp
	Time:		2020-07-18 23:15
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
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
int a[maxn], aa[maxn], c[maxn << 2], t[maxn << 2], s[maxn << 2], R[maxn << 2], L[maxn << 2];

void pushup(int p)
{
	L[p] = L[ls];
	R[p] = R[rs];
	s[p] = s[ls] + s[rs] - (R[ls] == L[rs]);
}

void build(int p, int l, int r)
{
	if (l == r) L[p] = R[p] = c[p] = aa[l], s[p] = 1;
	else
	{
		build(lson);
		build(rson);
		pushup(p);
	}
}

void maintain(int p, int col)
{
	s[p] = 1;
	L[p] = R[p] = t[p] = c[p] = col;
}
void pushdown(int p)
{
	maintain(ls, t[p]);
	maintain(rs, t[p]);
	t[p] = 0;
}
void update(int p, int l, int r, int L, int R, int col)
{
	if (L <= l && r <= R) maintain(p, col);
	else
	{
		if (t[p]) pushdown(p);
		if (L <= mid) update(lson, L, R, col);
		if (R >  mid) update(rson, L, R, col);
		pushup(p);
	}
}
int query_c(int p, int l, int r, int pos)
{
	if (l == r) return c[p];
	else
	{
		if (t[p]) pushdown(p);
		if (pos <= mid) return query_c(lson, pos);
		else			return query_c(rson, pos);
	}
}
int query_s(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return s[p];
	else
	{
		if (t[p]) pushdown(p);
		if (R <= mid) return query_s(lson, L, R);
		if (L >  mid) return query_s(rson, L, R);
		return query_s(lson, L, R) + query_s(rson, L, R) - (::R[ls] == ::L[rs]);
	}
}

int n, m;
int fa[maxn], dfn[maxn], top[maxn], siz[maxn], hvy[maxn], dep[maxn], dfs_clock;

void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dep[to[i]] = dep[x] + 1;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	top[x] = y;
	dfn[x] = ++dfs_clock;
	aa[dfn[x]] = a[x];
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}
int query(int x, int y)
{
	int ans = 0;
	while (top[x] ^ top[y])
	{
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		ans += query_s(1, 1, n, dfn[top[x]], dfn[x]) - (query_c(1, 1, n, dfn[top[x]]) == query_c(1, 1, n, dfn[fa[top[x]]]));
		x = fa[top[x]];
	}
	if (dfn[x] > dfn[y]) swap(x, y);
	return ans + query_s(1, 1, n, dfn[x], dfn[y]);
}
void update(int x, int y, int col)
{
	while (top[x] ^ top[y])
	{
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		update(1, 1, n, dfn[top[x]], dfn[x], col);
		x = fa[top[x]];
	}
	if (dfn[x] > dfn[y]) swap(x, y);
	update(1, 1, n, dfn[x], dfn[y], col);
}
int main()
{
#ifdef CraZYali
	file("2486");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dfs1(1);dfs2(1, 1);
	build(1, 1, n);
	while (m--)
	{
		register int c = getchar();
		while (!isalpha(c)) c = getchar();
		int x = read<int>(), y = read<int>();
		if (c == 'Q') printf("%d\n", query(x, y));
		else update(x, y, read<int>());
	}
	return 0;
}
