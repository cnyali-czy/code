/*
	Problem:	C.cpp
	Time:		2020-12-30 15:37
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
const int maxn = 1e6 + 10, maxq = 1e6 + 10, MOD = 1e9 + 7;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	if (!base && b == MOD - 2) return 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, x, y, p;
int f[3005][3005];
//f[i][j] 过了i轮了，1号猫还在且还剩下了j只猫的概率

int fac[maxn], Inv[maxn], invs[maxn], binp[maxn], bin1p[maxn];
void init(int n)
{
	fac[0] = Inv[0] = invs[0] = 1;
	fac[1] = Inv[1] = invs[1] = 1;
	binp[0] = bin1p[0] = 1;
	binp[1] = p;bin1p[1] = MOD + 1 - p;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * invs[MOD % i] * (MOD - MOD / i) % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
		binp[i] = 1ll * p * binp[i - 1] % MOD;
		bin1p[i] = (MOD + 1ll - p) * bin1p[i - 1] % MOD;
	}
}
i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();x = read<int>();y = read<int>();
	p = x * inv(y) % MOD;
	init(n);
	f[0][n] = 1;
	REP(i, 0, n - 1)
		REP(j, 1, n - i) if (f[i][j])
		{
			REP(k, 0, j - 2) // 箱子带走几个
			{
				i64 res = f[i][j] * (MOD + 1ll - invs[j]) % MOD * bin1p[k] % MOD * binp[j - 1 - k] % MOD * C(j - 2, k) % MOD;
				(f[i + 1][j - k - 1] += res) %= MOD;
			}
		}
	int q = read<int>();
	while (q--)
	{
		int t = read<int>();
		i64 ans = 0;
		REP(j, 0, n)
			(ans += f[t - 1][j] * inv(j)) %= MOD;
		ans += MOD;
		printf("%lld\n", ans % MOD);
	}
	return 0;
}
