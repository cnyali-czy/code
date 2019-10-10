#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprtinf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

	template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
	while (!isdigit(c))
	{
		flag |= (c == '-');
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

struct Frac
{
	int x, y;
	Frac(const int &x = 1, const int &y = 0) : x(x), y(y) {}
	inline bool operator < (const Frac &f) const
	{
		return 1ll * y * f.x < 1ll * f.y * x;
	}
	inline bool operator >= (const Frac &f) const
	{
		return 1ll * y * f.x >= 1ll * f.y * x;
	}
}maxv[maxn << 2];

int lenv[maxn << 2], Y[maxn << 2];

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int query(int p, int l, int r, Frac x)
{
	if (x >= maxv[p]) return 0;
	if (l == r) return 1;
	return maxv[ls] < x ? query(rson, x) : query(lson, x) + lenv[p] - lenv[ls];
}

void maintain(int p, int l, int r)
{
	if (l == r)
	{
		lenv[p] = 1;
		maxv[p] = Frac(l, Y[l]);
	}
	else
	{
		maxv[p] = max(maxv[ls], maxv[rs]);
		lenv[p] = lenv[ls] + query(rson, maxv[ls]);
	}
}

void modify(int p, int l, int r, int x, int y)
{
	if (l > x || r < x) return;
	if (l == r) Y[x] = y;
	else
	{
		modify(lson, x, y);
		modify(rson, x, y);
	}
	maintain(p, l, r);
}

void build(int p, int l, int r)
{
	maxv[p] = Frac(l, 0);
	lenv[p] = 1;
	if (l < r)
	{
		build(lson);
		build(rson);
	}
}

#define file(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
int n, m;

int main()
{
#ifdef CraZYali
	file("2957");
#endif
	cin >> n >> m;
	build(1, 1, n);
	while (m--)
	{
		register int x(read<int>()), y(read<int>());
		modify(1, 1, n, x, y);
		printf("%d\n", query(1, 1, n, Frac()));
	}
	return 0;
}
