/*
	Problem:	A.cpp
	Time:		2020-10-13 20:44
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 400 + 10;

int n, P;
i64 power_pow(i64 base, int b, const int MOD = P)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, P - 2)

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int f[maxn][maxn], g[maxn][maxn];
int F[maxn][maxn], G[maxn][maxn];
int sf[maxn][maxn], sg[maxn][maxn];

// [i个点][j个最远点][最远的距离为k]
int bin[maxn * maxn];
int fac[maxn], Inv[maxn], invs[maxn];
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[n - m] % P * Inv[m] % P;}
inline int C2(int x) {return x * (x - 1) / 2;}
inline i64 all(int x) {return bin[C2(x)];}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();P = read<int>();
	const int MOD = P;
	bin[0] = 1;
	REP(i, 1, n * n) bin[i] = 2 * bin[i - 1] % MOD;
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * invs[MOD % i] * (MOD - MOD / i) % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}

	f[1][1] = 1;
	i64 ans = 0;
	REP(k, 1, n - 1)
	{
		REP(i, 1, n) REP(j, 1, i)
		{
			F[i][j] = f[i][j];f[i][j] = 0;
			G[i][j] = g[i][j];g[i][j] = 0;
		}
		REP(i, 1, n) REP(j, 1, i)
		{
			REP(lstj, 1, i - j)
			{
				f[i][j] = (f[i][j] + 
				F[i - j][lstj] * power_pow(bin[lstj] - 1, j)
				)
				% MOD;
				g[i][j] = (g[i][j] + 
				G[i - j][lstj] * power_pow(bin[lstj] - 1, j)
				) % MOD;
			}
			f[i][j] = f[i][j] * C(i - 1, i - j - 1) % MOD * all(j) % MOD;
			g[i][j] = g[i][j] * C(i - 1, i - j - 1) % MOD * all(j) % MOD;
			g[i][j] = (g[i][j] + 1ll * k * j % MOD * f[i][j]) % MOD;
		}
		REP(j, 1, n) ans += g[n][j];
	}
	cout << ans % MOD * invs[n - 1] % MOD << endl;
	return 0;
}
