#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 3e7 + 10, MOD = 998244353;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int read()
{
	int res = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) res = res * 10 + c - 48, c = getchar();
	return res;
}

int invs[maxn], fac[maxn], Inv[maxn];
void init(int n)
{
	invs[0] = fac[0] = Inv[0] = 1;
	invs[1] = fac[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}
}
i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

i64 calc(int n, int m, int s) // n * (-m), sum = s
{
	int len = s + n * m + n;
	return C(len, n) * invs[len] % MOD * s % MOD;
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	init(3e7);
	register int T = read();
	while (T--)
	{
		int n = read(), m = read(), sa = read(), sb = read();
		int len = n * (m + 1) + sa + sb;
		i64 ans = C(len, n) * (sa + sb) % MOD * invs[len] % MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
