#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100000 + 10;

#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r

typedef long long ll;
ll m, n, k;

struct SegTree
{
	ll sum[maxn << 2], lazy[maxn << 2];;
	inline void build(ll p, ll l, ll r)
	{
		if (l == r) scanf("%lld", sum + p);
		else
		{
			build(lson);
			build(rson);
			sum[p] = sum[ls] + sum[rs];
		}
	}
	inline ll pushdown(ll x, ll p, ll l, ll r)
	{
		sum[p] += (r - l + 1) * x;
		lazy[p] += x;
	}
	inline ll query(ll p, ll l, ll r, ll L, ll R)
	{
		if (L <= l && r <= R) return sum[p];
		else
		{
			if (lazy[p])
			{
				pushdown(lazy[p], lson);
				pushdown(lazy[p], rson);
				lazy[p] = 0;
			}
			ll temp = 0;
			if (L <= mid) temp += query(lson, L, R);
			if (R >  mid) temp += query(rson, L, R);
			return temp;
		}
	}
	inline void update(ll p, ll l, ll r, ll L, ll R, ll x)
	{
		if (L <= l && r <= R)
		{
			sum[p] += (r - l + 1) * x;
			lazy[p] += x;
		}
		else
		{
			if (lazy[p])
			{
				pushdown(lazy[p], lson);
				pushdown(lazy[p], rson);
				lazy[p] = 0;
			}
			if (L <= mid) update(lson, L, R, x);
			if (R >  mid) update(rson, L, R, x);
			sum[p] = sum[ls] + sum[rs];
		}
	}
}T;


int main()
{
#ifdef CraZYali
	freopen("3372.in", "r", stdin);
	freopen("3372.out", "w", stdout);
#endif
	cin >> n >> m;
	T.build(1, 1, n);
	while (m --> 0)
	{
		ll opt, x, y;
		scanf("%lld%lld%lld", &opt, &x, &y);
		if (opt == 1) {scanf("%lld", &k);; T.update(1, 1, n, x, y, k);}
		if (opt == 2) printf("%lld\n", T.query(1, 1, n, x, y));
	}
	return 0;
}
