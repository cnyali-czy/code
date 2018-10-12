#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#define int long long
using namespace std;

const int maxn = 5e5 + 10;

template <typename T> inline T read()
{
	T ans(0), p(1);
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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');

}

#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)

int m, n, k;
int a[maxn];

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

struct SMT
{
	int g[maxn << 2];

	void build(int p, int l, int r)
	{
		if (l == r) g[p] = a[l];
		else
		{
			build(lson);
			build(rson);
			g[p] = gcd(g[ls], g[rs]);
		}
	}

	void update(int p, int l, int r, int pos, int val)
	{
		if (l == pos && pos == r) g[p] += val;
		else
		{
			if (pos <= mid) update(lson, pos, val);
			else update(rson, pos, val);
			g[p] = gcd(g[ls], g[rs]);
		}
	}

	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return g[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return gcd(query(lson, L, R), query(rson, L, R));
		}
	}
}T;

struct fenwick
{
	int s[maxn];
	void add(int x, int y)
	{
		while (x <= n)
		{
			s[x] += y;
			x += x & -x;
		}
	}
	int get(int x)
	{
		int y = 0;
		while (x > 0)
		{
			y += s[x];
			x -= x & -x;
		}
		return y;
	}
}F;

signed main()
{
#ifdef CraZYali
	freopen("4302.in", "r", stdin);
	freopen("4302.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		scanf("%lld", a + i);
		F.add(i, a[i]);
		if (i < n) F.add(i + 1, -a[i]);
	}
	DREP(i, n, 1) a[i] -= a[i-1];
	T.build(1, 1, n);
	while (m --> 0)
	{
		char c;int l, r;

		c = getchar();
		while (c ^ 'Q' && c ^ 'C') c = getchar();

		scanf("%lld%lld", &l, &r);
		if (c == 'Q')
		{
			if (l == r) write(F.get(l));
			else write(gcd(F.get(l), llabs(T.query(1, 1, n, l + 1, r))));
			putchar(10);
		}
		else
		{
			register int val;
			scanf("%lld", &val);
			F.add(l, val);
			T.update(1, 1, n, l, val);
			if (r + 1 <= n)
			{
				T.update(1, 1, n, r + 1, -val);
				F.add(r + 1, -val);
			}
		}
	}
	return 0;
}
