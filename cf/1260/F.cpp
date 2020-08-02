/*
	Problem:	F.cpp
	Time:		2020-08-02 08:19
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
#include <vector>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, MOD = 1e9 + 7;

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

int n, l[maxn], r[maxn], c[maxn];

int siz[maxn], hvy[maxn], dep[maxn], fa[maxn], top[maxn], dfn[maxn], dfs_clock;
void dfs1(int x)
{
	siz[x] = 1;
	dep[x] = dep[fa[x]] + 1;
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
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
int s[maxn << 2], tag[maxn << 2];

void maintain(int p, int l, int r, int val)
{
	s[p] = (s[p] + (r - l + 1ll) * val) % MOD;
	tag[p] = (tag[p] + val) % MOD;
}

void pushdown(int p, int l, int r)
{
	maintain(lson, tag[p]);
	maintain(rson, tag[p]);
	tag[p] = 0;
}

void update(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R) maintain(p, l, r, val);
	else
	{
		if (tag[p]) pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
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

vector <pair <int, int> > opt[maxn];
int ans;

int s1, s2, tot, invs[maxn], N;

void Insert(int x, int v)
{
	while (x)
	{
		update(1, 1, n, dfn[top[x]], dfn[x], v);
		x = fa[top[x]];
	}
}
int Query(int x)
{
	i64 res = 0;
	while (x)
	{
		res += query(1, 1, n, dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	return res % MOD;
}

void ins(int x)
{
	i64 tmp = 1ll * tot * invs[c[x]] % MOD;
	ans = (ans + tmp * (1ll * dep[x] * s1 % MOD + s2) - 2ll * invs[c[x]] % MOD * Query(x)) % MOD;
	s1 = (s1 + invs[c[x]]) % MOD;
	s2 = (s2 + 1ll * dep[x] * invs[c[x]]) % MOD;
	Insert(x, tmp);
}
void del(int x)
{
	i64 tmp = 1ll * tot * invs[c[x]] % MOD;
	Insert(x, MOD - tmp);
	s2 = (s2 - 1ll * dep[x] * invs[c[x]]) % MOD;
	s1 = (s1 - invs[c[x]]) % MOD;
	ans = (ans - tmp * (1ll * dep[x] * s1 % MOD + s2) + 2ll * invs[c[x]] % MOD * Query(x)) % MOD;
}

int main()
{
#ifdef CraZYali
	file("F");
#endif
	invs[0] = invs[1] = 1;
	REP(i, 2, 100000) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
	n = read<int>();tot = 1;
	REP(i, 1, n)
	{
		l[i] = read<int>(), r[i] = read<int>();
		opt[l[i]].emplace_back(i, 1);
		opt[r[i]].emplace_back(i, -1);
		tot = tot * (r[i] - l[i] + 1ll) % MOD;
		c[i] = r[i] - l[i] + 1;
	}
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	dfs1(1);dfs2(1, 1);
	i64 Ans = 0;
	REP(i, 1, 100000)
	{
		for (auto j : opt[i]) if (j.second > 0) ins(j.first);
		Ans += ans;
		for (auto j : opt[i]) if (j.second < 0) del(j.first);
	}
	cout << (Ans % MOD + MOD) % MOD << endl;
	return 0;
}
