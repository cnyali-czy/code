#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 100000 + 10;

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
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, k;

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int sum[maxn << 2], tag[maxn << 2];
void build(int p, int l, int r)
{
	if (l == r) sum[p] = read<int>();
	else
	{
		build(lson);
		build(rson);
		sum[p] = sum[ls] + sum[rs];
	}
}
void add(int p, int l, int r, int val)
{
	tag[p] += val;
	sum[p] += val * (r - l + 1);
}
void pushdown(int p, int l, int r)
{
	if (!tag[p]) return ;
	add(lson, tag[p]);
	add(rson, tag[p]);
	tag[p] = 0;
}
void update(int p, int l, int r, int L, int R, int val)
{
	if (L <= l && r <= R) add(p, l, r, val);
	else
	{
		pushdown(p, l, r);
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
		sum[p] = sum[ls] + sum[rs];
	}
}
int query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return sum[p];
	else
	{
		pushdown(p, l, r);
		if (L >  mid) return query(rson, L, R);
		if (R <= mid) return query(lson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}


signed main()
{
#ifdef CraZYali
	freopen("3486.in", "r", stdin);
	freopen("3486.out", "w", stdout);
#endif
	cin >> n >> m;
	build(1, 1, n);
	while (m --> 0)
	{
		register char c = getchar();
		while (c ^ 'Q' && c ^ 'C') c = getchar();
		register int l = read<int>(), r = read<int>();
		if (c == 'Q') printf("%lld\n", query(1, 1, n, l, r));
		else update(1, 1, n, l, r, read<int>());
	}
	return 0;
}
