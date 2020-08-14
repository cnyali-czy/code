/*
	Problem:	5431.cpp
	Time:		2020-08-13 21:24
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
const int maxn = 5e6 + 10;

i64 power_pow(i64 base, int b, const int MOD)
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

int n, k;
int a[maxn], bin[maxn], fac[maxn], Inv[maxn];

int main()
{
#ifdef CraZYali
	file("5431");
#endif
	n = read<int>();
	const int MOD = read<int>();
	k = read<int>();
	fac[0] = bin[0] = 1;
	REP(i, 1, n)
	{
		a[i] = read<int>();
		fac[i] = 1ll * a[i] * fac[i - 1] % MOD;
		bin[i] = 1ll * k * bin[i - 1] % MOD;
	}
	Inv[n] = power_pow(fac[n], MOD - 2, MOD);
	DEP(i, n - 1, 1)
		Inv[i] = 1ll * a[i + 1] * Inv[i + 1] % MOD;
	i64 ans = 0;
	REP(i, 1, n) ans += 1ll * Inv[i] * fac[i - 1] % MOD * bin[i] % MOD;
	cout << ans % MOD << endl;
	return 0;
}
