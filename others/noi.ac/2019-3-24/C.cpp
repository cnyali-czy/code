#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 5000 + 10;
const int MOD = 998244353;

int n, P, T;

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

int dp[maxn][maxn][2], ans[200000 + 10][2];

namespace violence
{
	void work()
	{
		dp[0][0][0] = 1;
		REP(i, 1, n)
			REP(j, 0, i)
			{
				dp[i][j][0] = dp[i-1][j][0] * i % P;
				if (j) dp[i][j][0] = (dp[i][j][0] + dp[i-1][j-1][0]) % P;
			}
		REP(i, 0, n) ans[dp[n][i][0]][0]++;
		if (!T) cout << ans[0][0] << endl;
		else REP(i, 0, P - 1) printf("%lld\n", ans[i][0]);
	}
};

namespace cheat
{
	void work()
	{
		dp[0][0][0] = 1;
		REP(i, 1, P)
			REP(j, 0, i)
			{
				dp[i][j][0] = dp[i-1][j][0];
				if (j) dp[i][j][0] = (dp[i][j][0] + dp[i-1][j-1][0] * i) % P;
			}
		dp[0][0][1] = 1;
		REP(i, 1, P)
			REP(j, 0, i)
			{
				dp[i][j][1] = dp[i-1][j][1];
				if (j) dp[i][j][1] = (dp[i][j][1] + dp[i-1][j-1][1] * (P-1)) % P;
			}
		int s = 1, N = n;
		while (s <= N / P) s *= P;
		ans[1][0] = 1;
		while (s ^ 1)
		{
			int x = n / s; n %= s; s /= P;
			if (s == 1 && n == P - 1) {n = 0;++x;}
			REP(i, 0, P - 1)
				REP(j, 0, x)
				ans[dp[x][j][1] * i % P][1] = (ans[dp[x][j][1] * i % P][1] + ans[i][0]) % MOD;
			REP(i, 0, P - 1) ans[i][0] = ans[i][1], ans[i][1] = 0;
		}
		REP(i, 0, P - 1)
			if (ans[i][0])
				REP(j, 0, n)
					ans[dp[n][j][0] * i % P][1] = (ans[dp[n][j][0] * i % P][1] + ans[i][0]) % MOD;
		REP(i, 0, P - 1) ans[i][0] = ans[i][1], ans[i][1] = 0;
		ans[0][0] = (N + 1) % MOD;
		REP(i, 1, P - 1) ans[0][0] = (ans[0][0] - ans[i][0]) % MOD;
		if (!T) cout << (ans[0][0] + MOD) % MOD << endl;
		else REP(i, 0, P - 1) printf("%lld\n", (ans[i][0] + MOD) % MOD);
	}
}

signed main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> P >> T;
	if (n <= 5000) violence::work();
	else cheat::work();
	return 0;
}
