/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2019.12.22 15:08
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = (1 << 20) + 10;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, fa[maxn], dep[maxn], dfn[maxn], dfs_clock, top[maxn], siz[maxn], hvy[maxn], back[maxn];

void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dep[to[i]] = dep[x] + 1;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	back[dfn[x] = ++dfs_clock] = x;
	top[x] = y;
	if (hvy[x])
	{
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ hvy[x])
			dfs2(to[i], to[i]);
	}
}
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
long long s[maxn << 2], pre[maxn << 2], tag[maxn << 2];

void build(int p, int l, int r)
{
	if (l == r) pre[p] = dep[back[l]] * 2 + 1;
	else
	{
		build(lson);
		build(rson);
		pre[p] = pre[ls] + pre[rs];
	}
}

void maintain(int p, int l, int r, int val)
{
	s[p] += pre[p] * val;
	tag[p] += val;
}
void pushdown(int p, int l, int r)
{
	if (!tag[p]) return;
	maintain(lson, tag[p]);
	maintain(rson, tag[p]);
	tag[p] = 0;
}

void update(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) maintain(p, l, r, 1);
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R);
		if (R >  mid) update(rson, L, R);
		s[p] = s[ls] + s[rs];
	}
}

long long query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return s[p];
	else
	{
		pushdown(p, l, r);
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}

void init(int x)
{
	while (1)
	{
		update(1, 1, n, dfn[top[x]], dfn[x]);
		if (top[x] == 1) return;
		x = fa[top[x]];
	}
}

long long solve(int x)
{
	long long res(0);
	while (1)
	{
		res += query(1, 1, n, dfn[top[x]], dfn[x]);
		if (top[x] == 1) return res;
		x = fa[top[x]];
	}
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n;
	REP(i, 2, n) add(fa[i] = read<int>(), i);
	dfs1(1);
	dfs2(1, 1);
	build(1, 1, n);
	REP(i, 1, n)
	{
		init(i);
		printf("%lld\n", solve(read<int>()));
	}
	return 0;
}
