/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.30 08:52
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20000 + 10, maxm = 2000 + 10, inf = 1e8;

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

int n, m, a[maxn], c[maxn];

int dp[maxn][maxm];
long long ans[maxn];
int q[286000], head, tail;

int cur, temp[maxm];
#define mid (l + r >> 1)

void solve(int p, int l, int r)
{
	if (l == r)
		REP(i, 0, m - 1) ans[l] += (dp[p][i] == inf ? -1 : dp[p][i]);
	else
	{
		int ls, rs;
		ls = (head < tail ? q[head++] : ++cur);
		copy(dp[p], dp[p] + m, dp[ls]);
		REP(i, mid + 1, r)
		{
			copy(dp[ls], dp[ls] + m, temp);
			REP(j, 0, m - 1)
				chkmin(dp[ls][(j + a[i]) % m], temp[j] + c[i]);
		}
		solve(ls, l, mid);
		rs = (head < tail ? q[head++] : ++cur);
		copy(dp[p], dp[p] + m, dp[rs]);
		REP(i, l, mid)
		{
			copy(dp[rs], dp[rs] + m, temp);
			REP(j, 0, m - 1)
				chkmin(dp[rs][(j + a[i]) % m], temp[j] + c[i]);
		}
		q[++tail] = p;
		solve(rs, mid + 1, r);
	}
}
int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>(), c[i] = read<int>();
	REP(i, 1, m - 1) dp[1][i] = inf;
	solve(++cur, 1, n);
	REP(i, 1, n) printf("%lld\n", ans[i]);
	return 0;
}
