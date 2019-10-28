//test
/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.27 23:38
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 500000 + 10;

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

int n, a[maxn];
long long s[maxn];
double ans[maxn][2][3], st[maxn][20];
int ok[maxn], b[maxn], id[maxn], tot;

inline double check(int l, int r, double mid, int opt)
{
	double ans(0), now(0);
	if (!opt)
		REP(i, l, r)
		{
			now += a[i] - mid;
			chkmax(ans, now);
		}
	else
		DREP(i, r, l)
		{
			now += a[i] - mid;
			chkmax(ans, now);
		}
	return ans;
}

const double eps = 1e-10;
inline double solve(int l1, int r1, int l2, int r2)
{
	double l = 0, r = 1e9;
	while (r - l > eps)
	{
		double mid = (l + r) / 2;
		if (check(l1, r1 - 1, mid, 1) + s[l2] - s[r1 - 1] - mid * (l2 - r1 + 1) + check(l2 + 1, r2, mid, 0) >= 0) l = mid;
		else r = mid;
	}
	return r;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n;
	REP(i, 1, n) s[i] = s[i-1] + (a[i] = read<int>());
	REP(i, 1, n)
	{
		scanf("%1d", &ok[i]);
		if (ok[i]) b[id[i] = ++tot] = i;
	}
	REP(i, 1, tot)
	{
		if (i <= tot - 1) ans[i][0][0] = solve(b[i], b[i], b[i + 1], b[i + 1]);
		if (i <= tot - 2)
		{
			ans[i][0][1] = solve(b[i], b[i], b[i + 1], b[i + 2]);
			ans[i][1][0] = solve(b[i], b[i + 1], b[i + 2], b[i + 2]);
		}
		if (i <= tot - 3)
		{
			ans[i][0][2] = solve(b[i], b[i], b[i + 1], b[i + 3]);
			ans[i][1][1] = solve(b[i], b[i + 1], b[i + 2], b[i + 3]);
		}
		if (i <= tot - 4)
		{
			ans[i][1][2] = solve(b[i], b[i + 1], b[i + 2], b[i + 4]);
			st[i][0] = ans[i][1][2];
		}
	}
	REP(j, 1, 19)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			st[i][j] = max(st[i][j-1], st[i + (1 << j-1)][j-1]);
	int q = read<int>();
	while (q--)
	{
		int l(id[read<int>()]), r(id[read<int>()]);
		double Ans(0);
		if (l <= r - 1)
		{
			chkmax(Ans, ans[l][0][0]);
			chkmax(Ans, ans[r - 1][0][0]);
		}
		if (l <= r - 2)
		{
			chkmax(Ans, ans[l][0][1]);
			chkmax(Ans, ans[l][1][0]);
			chkmax(Ans, ans[r - 2][0][1]);
			chkmax(Ans, ans[r - 2][1][0]);
		}
		if (l <= r - 3)
		{
			chkmax(Ans, ans[l][0][2]);
			chkmax(Ans, ans[l][1][1]);
			chkmax(Ans, ans[r - 3][0][2]);
			chkmax(Ans, ans[r - 3][1][1]);
		}
		if (l <= r - 4)
		{
			int len = (r - 4) - l + 1;
			DREP(o, 19, 0)
				if (len & (1 << o)) chkmax(Ans, st[l][o]), l += (1 << o);
		}
		printf("%.10lf\n", Ans);
	}
	return 0;
}
