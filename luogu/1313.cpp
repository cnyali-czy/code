#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %lld\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 1000 + 10, MOD = 10007;

long long m, n, k;

long long c[maxn][maxn];
void getc()
{
	c[0][0] = 1;
	REP(i, 1, 1001)
		REP(j, 1, i)
			c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
	REP(i, 1, 1001)
		REP(j, 1, i)
			c[i-1][j-1] = c[i][j];
}

long long power_pow(long long a, long long b)
{
	long long ans = 1, base = a;
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

long long a, b;

int main()
{
#ifdef CraZYali
	freopen("1313.in", "r", stdin);
	freopen("1313.out", "w", stdout);
#endif
	cin >> a >> b >> k >> n >> m;
	getc();
	
	a %= MOD;b %= MOD;

	cout << (MOD + (c[k][n] * power_pow(a, n) % MOD * c[k-n][m] % MOD * power_pow(b, m) % MOD)) % MOD;

	return 0;
}
