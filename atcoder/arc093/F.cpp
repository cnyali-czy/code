#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int MOD = 1e9 + 7, maxn = 20, maxN = 1 << maxn;
int bin[maxn], fac[maxN], inv[maxN], Inv[maxN];
inline int C(int n, int m) {return n < m ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n-m] % MOD;}

int n, m;
long long ans;
int a[maxn], dp[maxn][maxN], cnt[maxN];

int power_pow(long long base, int b)
{
	long long ans(1);
	while(b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}

signed main()
{
#ifdef CraZYali
	freopen("F.in", "r", stdin);
	freopen("F.out", "w", stdout);
#endif
	cin >> n >> m;
	cnt[0] = fac[0] = bin[0] = Inv[0] = inv[0] = inv[1] = 1;
	REP(i, 1, n) bin[i] = bin[i-1]<<1;
	REP(i, 1, bin[n]) fac[i] = 1ll * fac[i-1] * i%MOD;
	Inv[bin[n]] = power_pow(fac[bin[n]], MOD - 2);
	DREP(i, bin[n]-1, 1) Inv[i] = 1ll * Inv[i+1] * (i+1) % MOD;
	REP(i, 1, bin[n]) inv[i] = 1ll * Inv[i] * fac[i-1] % MOD;
	REP(i, 1, bin[n]) cnt[i] = (i&1) ? MOD - cnt[i>>1]:cnt[i>>1];
	REP(i, 1, m) scanf("%d", a + i);
	sort(a + 1, a + 1 + m);
	dp[m+1][0] = 1;
	DREP(i, m, 1)
		REP(S, 0, bin[n]-1)
			if(dp[i+1][S])
			{
				(dp[i][S] += dp[i+1][S]) %= MOD;
				int p = bin[n] - S - 1;
				REP(j, 0, n)
					if(!(S & (1<<j)))
						(dp[i][S | (1<<j)] += 1ll * C(p - a[i] + 1, (1<<j) - 1) * dp[i+1][S] % MOD * fac[1<<j] % MOD) %= MOD;
			}
	REP(i, 0, bin[n]-1)
		(ans += 1ll * dp[1][i] * fac[bin[n]-1-i] % MOD * cnt[i] % MOD) % MOD;
	printf("%lld\n", (1ll * ans * bin[n] % MOD + MOD) % MOD);
	return 0;
}
