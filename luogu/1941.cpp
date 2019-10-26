/*
 * File Name:	1941.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.24 21:09
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 10000 + 10, maxm = 1000 + 10;

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

int n, m, k, x[maxn], y[maxn], l[maxn], h[maxn];
int dp[maxn][maxm], tmp[maxm];

int main()
{
#ifdef CraZYali
	file("1941");
#endif
	cin >> n >> m >> k;
	REP(i, 0, n - 1) x[i] = read<int>(), y[i] = read<int>();
	REP(i, 1, k)
	{
		int p = read<int>();
		l[p] = read<int>();
		h[p] = read<int>();
	}
	memset(dp, 0x3f, sizeof dp);
	const int inf = dp[0][0];
	REP(i, 1, m) dp[0][i] = 0;
	REP(i, 0, n - 1)
	{
		if (h[i])
		{
			REP(j, 0, l[i]) dp[i][j] = inf;
			REP(j, h[i], m) dp[i][j] = inf;
		}
		
		copy(dp[i], dp[i] + m + 1, tmp);
		REP(j, 1, m) 
		{
			int newx = min(m, j + x[i]);
			/*if (!h[i] || l[i] < newx && newx < h[i])*/ chkmin(tmp[newx], tmp[j] + 1);
			if (!h[i+1] || l[i+1] < newx && newx < h[i+1]) chkmin(dp[i+1][newx], tmp[j] + 1);
		}
		REP(j, y[i] + 1, m) chkmin(dp[i+1][j - y[i]], dp[i][j]);
	}
//	REP(i, 0, n)
//		REP(j, 1, m) printf("%2d%c", dp[i][j] < inf ? dp[i][j] : -1, j == end_j ? '\n' : ' ');
	int cnt(0);
	REP(i, 1, n) if (h[i] || i == n)
	{
		int need(inf);
		REP(j, l[i] + 1, (h[i] ? h[i] - 1 : m)) chkmin(need, dp[i][j]);
		if (need == inf)
		{
			printf("0\n%d\n", cnt);
			return 0;
		}
		++cnt;
		if (i == n) printf("1\n%d\n", need);
	}
	return 0;
}
