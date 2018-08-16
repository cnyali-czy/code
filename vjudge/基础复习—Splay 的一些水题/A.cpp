#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const long long maxn = 100010;

#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r

struct SMT
{
	long long sum[maxn << 2], tag[maxn << 2];
	void build(long long p, long long l, long long r)
	{
		if (l == r) scanf("%lld", sum + p);
		else
		{
			build(lson);
			build(rson);
			sum[p] = sum[ls] + sum[rs];
		}
	}

	inline void mark(long long x, long long p, long long l, long long r)
	{
		sum[p] += (r - l + 1) * x;
		tag[p] += x;
	}
	
	void add(long long p, long long l, long long r, long long L, long long R, long long val)
	{
		if (L <= l && r <= R) mark(val, p, l, r);
		else
		{
			if (tag[p])
			{
				mark(tag[p], lson);
				mark(tag[p], rson);
				tag[p] = 0;
			}
			if (L <= mid) add(lson, L, R, val);
			if (R >  mid) add(rson, L, R, val);
			sum[p] = sum[ls] + sum[rs];				
		}
	}

	long long query(long long p, long long l, long long r, long long L, long long R)
	{
		if (L <= l && r <= R) return sum[p];
		else
		{
			if (tag[p])
			{
				mark(tag[p], lson);
				mark(tag[p], rson);
				tag[p] = 0;
			}
			register long long temp = 0;
			if (L <= mid) temp += query(lson, L, R);
			if (R >  mid) temp += query(rson, L, R);
			return temp;
		}
	}
}T;


long long m, n, k;

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	T.build(1, 1, n);
	while (m --> 0)
	{
		register long long x, y, z;
		register char opt = getchar();
		while (opt ^ 'C' && opt ^ 'Q') opt = getchar();
		scanf("%lld%lld", &x, &y);
		if (opt == 'C')
		{
			scanf("%lld", &z);
			T.add(1, 1, n, x, y, z);
		}
		else printf("%lld\n", T.query(1, 1, n, x, y));
	}

	return 0;
}
