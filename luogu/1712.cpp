/*
	Problem:	1712.cpp
	Time:		2021-06-25 21:00
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, b[maxn << 1], k;
pair <int, int> a[maxn];

#define fi first
#define se second
namespace SMT
{
	int mx[(maxn * 2) << 2], t[(maxn * 2) << 2];
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1
	inline void maintain(int p, int val) {mx[p] += val;t[p] += val;}
	void update(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R) maintain(p, val);
		else
		{
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			mx[p] = max(mx[ls], mx[rs]) + t[p];
		}
	}
	int query(int p, int l, int r, int L, int R, int ard = 0)
	{
		if (L <= l && r <= R) return mx[p] + ard;
		else
		{
			ard += t[p];
			if (R <= mid) return query(lson, L, R, ard);
			if (L >  mid) return query(rson, L, R, ard);
			return max(query(lson, L, R, ard), query(rson, L, R, ard));
		}
	}
}
int main()
{
#ifdef CraZYali
	file("1712");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		int l = read<int>(), r = read<int>();
		a[i] = make_pair(l, r);
		b[++k] = l;b[++k] = r;
	}
	sort(a + 1, a + 1 + n, [&](pair <int, int> x, pair <int, int> y) {return x.se - x.fi < y.se - y.fi;});
	sort(b + 1, b + 1 + k);k = unique(b + 1, b + 1 + k) - b - 1;
	REP(i, 1, n)
	{
		a[i].fi = lower_bound(b + 1, b + 1 + k, a[i].fi) - b;
		a[i].se = lower_bound(b + 1, b + 1 + k, a[i].se) - b;
	}
	const int inf = 2e9;
	int l = 1, ans = inf;
	REP(r, 1, n)
	{
		SMT :: update(1, 1, k, a[r].fi, a[r].se, 1);
		while (l < r)
		{
			SMT :: update(1, 1, k, a[l].fi, a[l].se, -1);
			if (SMT :: mx[1] >= m) l++;
			else {SMT :: update(1, 1, k, a[l].fi, a[l].se, 1);break;}
		}
		if (SMT :: mx[1] >= m) ans = min(ans, (b[a[r].se] - b[a[r].fi]) - (b[a[l].se] - b[a[l].fi]));
	}
	printf("%d\n", ans == inf ? -1 : ans);
	return 0;
}
