/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.12 20:10
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long

using namespace std;
const int S = 1 << 11, maxn = 4e5 + 10;

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

int ans, n, m;
int good[maxn][11];
int dp[2][S][11];
char s[10];

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m;
	REP(i, 1, n - 1)
		REP(j, 0, m - 1)
		{
			scanf("%s", s);
			REP(k, 0, m - 1) good[i][j] |= (s[k] - '0' << k);
		}
	int cur(0);
	const int lim = (1 << m) - 1;
	REP(S, 0, lim)
		REP(j, m - __builtin_popcount(S), m) dp[cur][S][j] = 1;
	REP(r, 2, n)
	{
		cur ^= 1;
		memset(dp[cur], 0, sizeof dp[cur]);
		REP(S, 0, lim)
		{
			int T = 0;
			REP(i, 0, m - 1)
				if (S & (1 << i)) T |= good[r-1][i];
			REP(x, 0, m) chkmax(dp[cur][T][x], dp[cur ^ 1][S][x]);
		}
		chkmax(dp[cur][lim][0], r);
		REP(i, 0, m - 1)
			REP(S, 0, lim) if (S & (1 << i))
			REP(x, 0, m) chkmax(dp[cur][S ^ (1 << i)][x + 1], dp[cur][S][x]);
		REP(i, 1, m)
			ans += 1ll * i * (min(r - 1, dp[cur][0][i]) - min(r - 1, dp[cur][0][i-1]));
	}
	cout << ans << endl;
	return 0;
}
