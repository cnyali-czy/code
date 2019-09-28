#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 400 + 5, MOD = 998244353;

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

int power_pow(int a, int b)
{
	int ans(1), base(a);
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int n, dp[maxn][maxn][2];

signed main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n;
	bool cur = 0;
	dp[0][0][1] = 1;
	int lim = (1ll << 1 + (int)(log2(n)));
	REP(i, 1, n)
	{
		REP(j, 0, lim) REP(k, 0, lim) dp[j][k][cur] = 0;
		int t = read<int>();
		REP(j, 0, lim)
			REP(k, 0, lim)
			{
				dp[j][k][cur] = (dp[j][k][cur] + dp[j][k][cur ^ 1]) % MOD;
				dp[j][k][cur] = (dp[j][k][cur] + dp[j ^ t][k][cur ^ 1]) % MOD;
				dp[j][k][cur] = (dp[j][k][cur] + dp[j][k ^ t][cur ^ 1]) % MOD;
			}
		cur ^= 1;
	}
	cur ^= 1;
	int ans = 0;
	REP(i, 0, lim)
		REP(j, i + 1, lim)
		ans = (ans + dp[i][j][cur]) % MOD;
	cout << (ans + MOD) % MOD;
	return 0;
}
