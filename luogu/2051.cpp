#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 100 + 5, maxm = 100 + 5, MOD = 9999973;

int power_pow(int a, int b)
{
	int ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, m;

int mod(int x)
{
	if (x < 0) return (x % MOD + MOD) % MOD;
	return x >= MOD ? x % MOD : x;
}
int C(int x) {return mod(mod(x * (x - 1)) * inv(2));}


int dp[maxn][maxm][maxn] = {1};

signed main()
{
#ifdef CraZYali
	freopen("2051.in", "r", stdin);
	freopen("2051.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
		REP(j, 0, m)
		REP(k, 0, m - j)
		{
			dp[i][j][k] = dp[i-1][j][k];
			if (k >= 1) dp[i][j][k] = mod(dp[i][j][k] + mod(dp[i-1][j+1][k-1] * (j+1)));
			if (j >= 1) dp[i][j][k] = mod(dp[i][j][k] + mod(dp[i-1][j-1][k] * (m-j-k+1)));
			if (k >= 2) dp[i][j][k] = mod(dp[i][j][k] + mod(dp[i-1][j+2][k-2] * C(j + 2)));
			if (k >= 1) dp[i][j][k] = mod(dp[i][j][k] + mod(dp[i-1][j][k-1] * j * (m-j-k+1)));
			if (j >= 2) dp[i][j][k] = mod(dp[i][j][k] + mod(dp[i-1][j-2][k] * C(m-j-k+2)));
		}
	int ans = 0;
	REP(i, 0, m)
		REP(j, 0, m) ans = mod(ans + dp[n][i][j]);
	cout << ans;
	return 0;
}
