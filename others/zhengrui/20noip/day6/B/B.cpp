#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <iostream>
#include <cmath>
#include <cstdio>
#define i64 long long

using namespace std;
const int MOD = 10000019;

i64 power_pow(i64 base, i64 b)
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

int fac[MOD], invs[MOD], Inv[MOD];
struct __init__
{
	__init__()
	{
		fac[0] = invs[0] = Inv[0] = 1;
		fac[1] = invs[1] = Inv[1] = 1;
		REP(i, 2, MOD - 1)
		{
			fac[i] = 1ll * i * fac[i - 1] % MOD;
			invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
			Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
		}
	}
}__INIT__;

i64 C(i64 n, i64 m)
{
	if (n < m || m < 0) return 0;
	if (n < MOD && m < MOD) return 1ll * fac[n] * Inv[n - m] % MOD * Inv[m] % MOD;
	return C(n % MOD, m % MOD) * C(n / MOD, m / MOD) % MOD;
}

i64 n, q, m;

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> q;
	i64 ard = 0, even = 0, odd = 0;
	/*
	REP(i, 1, n) if (i & 1)
	{
		i64 len = floor(log2(n / i)) + 1;
		ard += len / 2;
		if (len & 1) odd++;
		else even++;
	}
	*/
	static i64 f[70];
	REP(i, 0, 60)
		f[i] = ceil(1. * (n >> i) / 2);
	REP(i, 1, 60)
	{
		i64 cur = f[i - 1] - f[i];
		ard += cur * (i / 2);
		if (i & 1) odd += cur;
		else even += cur;
	}

	i64 b2 = power_pow(2, even);
	while (q--)
	{
		m = read<i64>();
		if (m < ard) puts("0");
		else printf("%lld\n", b2 * C(odd, m - ard) % MOD);
	}
	return 0;
}
