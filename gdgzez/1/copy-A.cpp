#define  REP(i, s, e) for (int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 400 + 5;

int n, MOD;

int power_pow(long long base, int b, const int MOD = ::MOD)
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

long long fac[maxn], Inv[maxn], bin[maxn * maxn], p[maxn][maxn];
inline void init()
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = fac[i-1] * i % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n - 1, 0) Inv[i] = Inv[i+1] * (i+1) % MOD;
	bin[0] = 1;
	REP(i, 1, n * n) bin[i] = bin[i-1] * 2 % MOD;
	REP(k, 1, n)
		REP(j, 1, n)
		p[k][j] = power_pow(bin[k]-1, j);
}
inline int C(int n, int m) {return fac[n] * Inv[m] % MOD * Inv[n-m] % MOD;}
int f[maxn][maxn], g[maxn][maxn];

int main()
{
	freopen("A.in", "r", stdin);
	freopen("copy-A.out", "w", stdout);
	cin >> n >> MOD;n--;
	init();

	//考虑剩下的n-1个点怎么分配
	REP(i, 1, n)
		REP(j, 1, i)
		{
			if (i == j)
			{
				f[i][j] = bin[j * (j-1) >> 1] % MOD;
				g[i][j] = 1ll * f[i][j] * i % MOD;
				//随便连
			}
			REP(k, 1, n-i)
			{
				//再来一层，k个点
				long long o = p[k][j] * bin[k * (k-1) >> 1] % MOD * C(i + k, k) % MOD;
				f[i + k][k] = (f[i + k][k] + f[i][j] * o) % MOD;
				g[i + k][k] = (g[i + k][k] + g[i][j] * o + f[i][j] * o % MOD * (i + k)) % MOD;
			}
		}
	REP(i, 1, n) REP(j, 1, i) printf("%d%c", f[i][j], j == i ? '\n' : ' ');
	REP(i, 1, n) REP(j, 1, i) printf("%d%c", g[i][j], j == i ? '\n' : ' ');
	int ans(0);
	REP(i, 1, n) (ans += g[n][i]) %= MOD;
	cout << (1ll * ans * Inv[n] % MOD * fac[n-1] % MOD + MOD) % MOD << endl;
	return 0;
}
