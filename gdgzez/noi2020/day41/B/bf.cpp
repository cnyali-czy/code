/*
	Problem:	B.cpp
	Time:		2020-08-13 08:24
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 2.5e5 + 10, MOD = 998244353;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int fac[maxn], Inv[maxn], bin[maxn];
inline void init(int n)
{
	fac[0] = 1;bin[0] = 1;
	REP(i, 1, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		bin[i] = 2ll * bin[i - 1] % MOD;
	}
	Inv[n] = inv(fac[n]);
	DEP(i, n - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
}
inline i64 C(int n, int m) {return 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int n;
char str[maxn];

int main()
{
#ifdef CraZYali
	file("B");
#endif
	scanf("%s", str + 1);
	n = strlen(str + 1);
	init(n);
	i64 ans = 0;
	REP(i, 1, n) REP(j, i + 1, n) if (str[i] == str[j])
		ans += 1ll * bin[j - i - 1] * C(i - 1 + n - j, i - 1) % MOD;
	cout << ans % MOD << endl;
	return 0;
}
