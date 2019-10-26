/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.20 17:06
 * Email	:	yms-chenziyang@outlook.com
 */
//speed test
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstring>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 300 + 5, MOD = 998244353;

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int n, bin[maxn * maxn];

int fac[maxn], Inv[maxn];
inline void init(const int n = 300)
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * fac[i-1] * i % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n - 1, 0) Inv[i] = 1ll * Inv[i+1] * (i + 1) % MOD;
	bin[0] = 1;
	REP(i, 1, n * n) bin[i] = 2ll * bin[i-1] % MOD;
}
inline int C(int n, int m) {return 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
const int inv2 = inv(2), inv16 = inv(16);

int none()
{
	int res(0);
	REP(i, 0, n)
		REP(j, 0, n)
		{
			int x = (n - i) * (n - j) + (i && j ? 1 : i + j);
			res += ((i + j) & 1 ? -1ll : 1ll) * C(n, i) * C(n, j) % MOD * bin[x] % MOD;
		}
	return res;
}

int dp[2][maxn][maxn];
const int siz = sizeof(dp[0]);

int single()
{
	dp[0][0][0] = 2;
	int cur(0);
	REP(i, 0, n - 1)
	{
		cur = !cur;
		memset(dp[cur], 0, siz);
		REP(j, 0, i)
			REP(k, 0, i)
			{
				(dp[cur][j][k] += 1ll * dp[!cur][j][k] * inv2 % MOD) %= MOD;
				(dp[cur][j + 1][k] -= dp[!cur][j][k]) %= MOD;
				(dp[cur][j][k + 1] -= dp[!cur][j][k]) %= MOD;
				(dp[cur][j + 1][k + 1] += dp[!cur][j][k]) %= MOD;
			}
	}
	int res(0);
	REP(i, 0, n)
		REP(j, 0, n)
		(res += 1ll * dp[cur][i][j] * bin[(n - i) * (n - j)] % MOD) %= MOD;
	return res;
};
int both()
{
	memset(dp, 0, siz + siz);
	if (n & 1)
	{
		dp[0][0][0] = 1;
		dp[0][0][1] = dp[0][1][0] = -2;
		dp[0][1][1] = 2;
	}
	else dp[0][0][0] = 2;
	int cur(0);
	for (register int i(n & 1); i ^ n; i += 2)
	{
		cur = !cur;
		memset(dp[cur], 0, siz);
		REP(j, 0, i)
			REP(k, 0, i)
			{
				int tmp = dp[!cur][j][k];
				(dp[cur][j][k] += 1ll * inv16 * tmp % MOD) %= MOD;
				(dp[cur][j + 1][k] -= 1ll * inv2 * tmp % MOD) %= MOD;
				(dp[cur][j + 2][k] += tmp) %= MOD;
				(dp[cur][j][k + 1] -= 1ll * inv2 * tmp % MOD) %= MOD;
				(dp[cur][j + 1][k + 1] += 2ll * tmp % MOD) %= MOD;
				(dp[cur][j + 2][k + 1] -= 2ll * tmp % MOD) %= MOD;
				(dp[cur][j][k + 2] += tmp) %= MOD;
				(dp[cur][j + 1][k + 2] -= 2ll * tmp % MOD) %= MOD;
				(dp[cur][j + 2][k + 2] += tmp) %= MOD;
			}
	}
	int res(0);
	REP(i, 0, n)
		REP(j, 0, n)
		if (!i && !j && !(n & 1)) (res += bin[n * n - n * 2 + 2]) %= MOD;
		else (res += 1ll * dp[cur][i][j] * bin[(n - i) * (n - j)] % MOD) %= MOD;
	return res;
};

signed main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n;
	init();
	cout << (MOD + (0ll + none() - single() - single() + both()) % MOD) % MOD << endl;
	return 0;
}
