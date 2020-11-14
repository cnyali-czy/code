/*
	Problem:	427.cpp
	Time:		2020-11-14 16:48
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
const int maxn = 7.5e6 + 10, MOD = 1e9 + 9;

i64 power_pow(i64 base, int b)
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

int n, fac[maxn], Inv[maxn], invs[maxn];

void init(int n)
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}
}
inline i64 C(int n, int m)
{
	return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;
}
i64 g(int m, int a, int b, int c)
{
	if (m < 0) return 0;
	i64 res = 0;
	static int bina[maxn], binb[maxn], ard;
	if (!ard)
	{
		ard = 1;
		bina[0] = binb[0] = 1;
		REP(k, 1, m / c)
		{
			bina[k] = 1ll * bina[k - 1] * a % MOD;
			binb[k] = 1ll * binb[k - 1] * b % MOD;
		}
	}
	REP(k, 0, m / c)
	{
		int i = m - c * k;
		if (i < k) continue;
		res = (res + C(i, k) * binb[k] % MOD * bina[i - k]) % MOD;
	}
	return res;
}
i64 f(int m)
{
	i64 res = 0;
	res += g(n, n, MOD + 1 - n, m);
	res -= g(n - 1, n, MOD + 1 - n, m);
	res += MOD;
	res = res * n % MOD * invs[n - 1] % MOD;
	return res;
}

int main()
{
#ifdef CraZYali
	file("427");
#endif
	n = read<int>();
	init(n);
	i64 ans = 0;
	REP(i, 1, n - 1) ans += MOD - f(i);
	ans = (ans + 1ll * n * f(n)) % MOD;
	cout << ans << endl;
	return 0;
}
