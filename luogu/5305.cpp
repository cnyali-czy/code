/*
	Problem:	5305.cpp
	Time:		2020-07-30 19:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e4 + 10, maxq = 5e4 + 10, MOD = 998244353;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, q, k;
int fa[maxn], dep[maxn], siz[maxn], hvy[maxn], top[maxn], dfn[maxn], dfs_clock;
int w[maxn], back[maxn];

void dfs1(int x)
{
	dep[x] = dep[fa[x]] + 1;
	w[x] = power_pow(dep[x], k);
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	back[dfn[x] = ++dfs_clock] = x;
	top[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}

int ans[maxq];

struct Query
{
	int x, y, id;
	Query(int x = 0, int y = 0, int id = 0) : x(x), y(y), id(id) {}
	inline bool operator < (const Query &B) const {return x < B.x;}
}Q[maxn];

#define lson ls, l, mid
#define rson rs, mid + 1, r
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
namespace SMT
{
	int s[maxn << 2], tag[maxn << 2], sw[maxn << 2];
	void build(int p, int l, int r)
	{
		if (l == r) sw[p] = (MOD + w[back[l]] - w[fa[back[l]]]) % MOD;
		else
		{
			build(lson);
			build(rson);
			sw[p] = (sw[ls] + sw[rs]) % MOD;
		}
	}
	void maintain(int p, int l, int r, int val = 1)
	{
		tag[p] = (tag[p] + val) % MOD;
		s[p] = (s[p] + 1ll * sw[p] * val) % MOD;
	}
	void pushdown(int p, int l, int r)
	{
		maintain(lson, tag[p]);
		maintain(rson, tag[p]);
		tag[p] = 0;
	}
	void update(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) maintain(p, l, r);
		else
		{
			if (tag[p]) pushdown(p, l, r);
			if (L <= mid) update(lson, L, R);
			if (R >  mid) update(rson, L, R);
			s[p] = (s[ls] + s[rs]) % MOD;
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return s[p];
		else
		{
			if (tag[p]) pushdown(p, l, r);
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return (query(lson, L, R) + query(rson, L, R)) % MOD;
		}
	}
}

void insert(int x)
{
	while (x)
	{
		SMT :: update(1, 1, n, dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
}
int query(int x)
{
	i64 res = 0;
	while (x)
	{
		res += SMT :: query(1, 1, n, dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	return res % MOD;
}

int main()
{
#ifdef CraZYali
	file("5305");
#endif
	n = read<int>();q = read<int>();k = read<int>();
	REP(i, 2, n) add(fa[i] = read<int>(), i);
	dfs1(1);dfs2(1, 1);
	SMT :: build(1, 1, n);
	REP(i, 1, q)
	{
		int x = read<int>(), y = read<int>();
		Q[i] = Query(x, y, i);
	}
	sort(Q + 1, Q + 1 + q);
	int j = 1;
	REP(i, 1, n)
	{
		insert(i);
		while (j <= q && Q[j].x == i)
		{
			ans[Q[j].id] = query(Q[j].y);
			j++;
		}
	}
	REP(i, 1, q) printf("%d\n", ans[i]);
	return 0;
}
