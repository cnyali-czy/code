#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int MOD = 998244353, maxn = 1000 + 10, maxm = 1000 + 10;

int n, m, x, y;

int power_pow(int a, int b)
{
	int ans = 1, base = a % MOD;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int dp[maxn][maxn], a[maxn], b[maxn];

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m >> x >> y;
	if (m == 1) {cout << (n - x) * 2ll % MOD;return 0;}
	int inv2 = power_pow(2, MOD - 2);
	DREP(i, n - 1, x)
	{
		a[1] = MOD - inv2;
		b[1] = (dp[i+1][1] + 3) * inv2 % MOD;
		REP(j, 2, m-1)
		{
			a[j] = MOD - 1;
			b[j] = (dp[i+1][j] + b[j-1] + 4) % MOD;
			a[j] = a[j] * inv(a[j-1] + 3) % MOD;
			b[j] = b[j] * inv(a[j-1] + 3) % MOD;
		}
		dp[i][m] = (3ll + dp[i+1][m] + b[m-1]) * inv(a[m-1] + 2) % MOD;
		DREP(j, m - 1, 1)
			dp[i][j] = (b[j] - a[j] * dp[i][j+1] % MOD) % MOD;
	}
	cout << (dp[x][y] + MOD) % MOD;
	return 0;
}
