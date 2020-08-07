/*
	Problem:	3329.cpp
	Time:		2020-08-07 10:51
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cassert>
#include <bitset>
#include <cstring>
#include <iostream>
#include <cstdio>
inline bool chkmin(int &x, int y) {if (x > y) {x = y;return 1;}return 0;}
inline bool chkmax(int &x, int y) {if (x < y) {x = y;return 1;}return 0;}
using namespace std;
const int maxn = 5e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
#ifndef CraZYali
#define getchar getchar_unlocked
#endif
inline int read()
{
	int ans = 0;
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

int n, q;

int siz[maxn], fa[maxn], top[maxn], hvy[maxn], dfn[maxn], dfs_clock;

void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}

namespace SMT
{
	struct node
	{
		int s, t, Min, Max;
		node() {s = Max = t = 0;Min = 1e9;}
	}t[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	
	void maintain(int p, int l, int r, int val)
	{
		t[p].t += val;
		t[p].Max += val;t[p].Min += val;
	}
	void pushdown(int p, int l, int r)
	{
		maintain(lson, t[p].t);
		maintain(rson, t[p].t);
		t[p].t = 0;
	}
	void pushup(int p)
	{
		t[p].Max = max(t[ls].Max, t[rs].Max);
		t[p].Min = min(t[ls].Min, t[rs].Min);
	}

	void update(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R) maintain(p, l, r, val);
		else
		{
			if (t[p].t) pushdown(p, l, r);
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			pushup(p);
		}
	}
	void insert(int p, int l, int r, int pos, int val)
	{
		t[p].s++;
		if (l == r)
		{
			t[p].Max = t[p].Min = val;
			return;
		}
		if (t[p].t) pushdown(p, l, r);
		if (pos <= mid)	insert(lson, pos, val);
		else			insert(rson, pos, val);
		pushup(p);
	}
	void remove(int p, int l, int r, int pos)
	{
		t[p].s--;
		if (l == r)
		{
			t[p].Max = 0;
			t[p].Min = 1e9;
			return;
		}
		if (t[p].t) pushdown(p, l, r);
		if (pos <= mid) remove(lson, pos);
		else			remove(rson, pos);
		pushup(p);
	}
	int dfs(int p, int l, int r, int k) // <= k
	{
		if (t[p].Min > k) return 0;
		if (t[p].Max <=k) return t[p].s;
		if (l == r) return 0;
		if (t[p].t) pushdown(p, l, r);
		return (t[ls].s ? dfs(lson, k) : 0) + (t[rs].s ? dfs(rson, k) : 0);
	}
#undef mid
}

int s[maxn];
inline void Add(int x, int y)
{
	while (x <= n)
	{
		s[x] += y;
		x += x & -x;
	}
}
inline int sum(int l, int r)
{
	l--;
	int res = 0;
	while (r > l) res += s[r], r &= (r - 1);
	while (l > r) res -= s[l], l &= (l - 1);
	return res;
}
int opt, ans, N;

int count(int x)
{
	if (x < 1) return 0;
	return SMT :: dfs(1, 1, n, x);
}
void orzdog(int mid)
{
	if (mid >= ans) return;
	int i = count(mid) + 1;
	int a = N - i + 1, b = mid;
	chkmin(ans, max(a, b));
}
int getans()
{
	int lst = ans;
	ans = n;
	if (opt == 2)
	{
		orzdog(max(0, lst - 1));
		orzdog(lst);
	}
	else
	{
		orzdog(lst);
		orzdog(min(n, lst + 1));
	}
	return ans;
}

void Insert(int x)
{
	N++;
	Add(dfn[x], 1);
	SMT :: insert(1, 1, n, dfn[x], sum(dfn[x], dfn[x] + siz[x] - 1));
	x = fa[x];
	while (x) SMT :: update(1, 1, n, dfn[top[x]], dfn[x], 1), x = fa[top[x]];
}
void Remove(int x)
{
	N--;
	Add(dfn[x], -1);
	SMT :: remove(1, 1, n, dfn[x]);
	x = fa[x];
	while (x) SMT :: update(1, 1, n, dfn[top[x]], dfn[x], -1), x = fa[top[x]];
}

int main()
{
#ifdef CraZYali
	file("3329");
#endif
	n = read();
	REP(i, 2, n)
	{
		int x = read(), y = read();
		add(x, y);add(y, x);
	}
	dfs1(1);dfs2(1, 1);
	q = read();
	REP(i, 1, q)
	{
		opt = read();
		if (opt == 1)	Insert(read());
		else			Remove(read());
		printf("%d\n", getans());
	}
	return 0;
}
