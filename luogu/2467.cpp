#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 4200 + 1;

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

int n, MOD, dp[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("2467.in", "r", stdin);
	freopen("2467.out", "w", stdout);
#endif
	cin >> n >> MOD;
	dp[1][0] = 1;
	REP(i, 2, n)
		REP(j, 0, i)
		{
			dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
			dp[i][j+1] = (dp[i][j+1] + (long long)dp[i-1][j] * (i - j - 1) % MOD) % MOD;
			if (j) dp[i][j-1] = (dp[i][j-1] + (long long)dp[i-1][j] * j % MOD) % MOD;
		}
	cout << dp[n][0] * 2 % MOD;
	return 0;
}
