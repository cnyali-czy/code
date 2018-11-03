#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, MOD, a[maxn];

int mod(int x)
{
	if (x < 0) return (x % MOD + MOD) % MOD;
	else return (x >= MOD ? x % MOD : x);
}
#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

struct SMT
{
	int s[maxn << 2], add[maxn << 2], mul[maxn << 2];
	void build(int p, int l, int r)
	{
		mul[p] = 1;
		if (l == r) s[p] = a[l];
		else
		{
			build(lson);
			build(rson);
			s[p] = mod(s[ls] + s[rs]);
		}
	}
	void pushdown(int p, int l, int r)
	{
		s[ls] = mod(s[ls] * mul[p] + add[p] * (mid - l + 1));
		s[rs] = mod(s[rs] * mul[p] + add[p] * (r - mid));
		add[ls] = mod(add[p] + mod(add[ls] * mul[p]));
		add[rs] = mod(add[p] + mod(add[rs] * mul[p]));
		mul[ls] = mod(mul[ls] * mul[p]);
		mul[rs] = mod(mul[rs] * mul[p]);
		add[p] = 0;mul[p] = 1;
	}

	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return s[p];
		else
		{
			if (add[p] || mul[p] != 1) pushdown(p, l, r);
			if (L >  mid) return query(rson, L, R);
			if (R <= mid) return query(lson, L, R);
			return mod(query(lson, L, R) + query(rson, L, R));
		}
	}
	void updatesum(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R)
		{
			s[p] = mod(s[p] + mod((r - l + 1) * val));
			add[p] = mod(add[p] + val);
		}
		else
		{
			if (add[p] || mul[p] != 1) pushdown(p, l, r);
			if (L <= mid) updatesum(lson, L, R, val);
			if (R >  mid) updatesum(rson, L, R, val);
			s[p] = mod(s[ls] + s[rs]);
		}
	}
	void updatemul(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R)
		{
			s[p] = mod(s[p] * val);
			add[p] = mod(add[p] * val);
			mul[p] = mod(mul[p] * val);
		}
		else
		{
			if (add[p] || mul[p] != 1) pushdown(p, l, r);
			if (L <= mid) updatemul(lson, L, R, val);
			if (R >  mid) updatemul(rson, L, R, val);
			s[p] = mod(s[ls] + s[rs]);
		}
	}
}T;

signed main()
{
#ifdef CraZYali
	freopen("3373.in", "r", stdin);
	freopen("3373.out", "w", stdout);
#endif
	cin >> n >> m >> MOD;
	REP(i, 1, n) a[i] = mod(read<int>());
	T.build(1, 1, n);
	while (m --> 0)
	{
		register int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 1) T.updatemul(1, 1, n, l, r, read<int>());
		else if (opt == 2) T.updatesum(1, 1, n, l, r, read<int>());
		else printf("%lld\n", (T.query(1, 1, n, l, r) + MOD) % MOD);
	}
	return 0;
}
