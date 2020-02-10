/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.08 21:00
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;

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

namespace run
{
	const int maxn = 2000 + 10;
	const double inf = 1e9;
	int n,Q;
	double dp[maxn][maxn], f[maxn], x;
	struct Query
	{
		int l, r;
		double k, b;
		inline bool operator < (const Query &B) const {return k > B.k;}
	}A[maxn];
	void update(int x, double y)
	{
		DEP(i, maxn - 1, x) chkmin(f[i], f[i - x] + y);
	}
	void solve(int l, int r)
	{
		double f1[maxn];
		if (l == r)
		{
			int k = A[l].r - A[l].l - 1;
			for (int i = 1; i <= k; i <<= 1)
			{
				update(i, A[l].k * i);
				k -= i;
			}
			if (k) update(k, A[l].k * k);
			REP(i, 0, A[l].l - 1)
				dp[l][i] = inf;
			REP(i, A[l].l, maxn - 1)
				dp[l][i] = f[i - A[l].l] + A[l].b;
			return;
		}
		int mid = l + r >> 1;
		copy(f, f + maxn, f1);
		REP(i, l, mid) update(A[i].l, A[i].b);
		solve(mid + 1, r);
		copy(f1, f1 + maxn, f);
		REP(i, mid + 1, r) update(A[i].r, A[i].b + A[i].k * (A[i].r - A[i].l));
		solve(l, mid);
	}
	int main()
	{
		n = read<int>();
		Q = read<int>();
		REP(i, 1, n)
		{
			int l(read<int>()), r(read<int>());
			double k, b;scanf("%lf%lf", &k, &b);
			A[i] = Query{l, r, k, b};
		}
		REP(i, 1, maxn - 1) f[i] = inf;
		sort(A + 1, A + 1 + n);
		solve(1, n);
		while (Q--)
		{
			double ans = inf, x;
			scanf("%lf", &x);
			int y = (int)x;
			x -= y;
			REP(i, 1, n)
				chkmin(ans, dp[i][y] + x * A[i].k);
			printf("%.10lf\n", ans);
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	return run::main();
}
