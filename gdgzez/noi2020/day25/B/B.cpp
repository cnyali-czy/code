/*
	Problem:	B.cpp
	Time:		2020-07-12 23:39
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
const int maxn = (5e6 + 10) * 2, MOD = 1e9 + 7;

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

int fac[maxn], Inv[maxn];
inline i64 C(int n, int m) {return m < 0 || n < m ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	fac[0] = 1;
	REP(i, 1, maxn - 1) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[maxn - 1] = inv(fac[maxn - 1]);
	DEP(i, maxn - 2, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
	int n = read<int>(), m = read<int>();
	n -= m;
	i64 ans = 0;
	REP(i, 0, n) ans += C(i + i + m - 1, i);
	cout << ans % MOD * inv(m - 1) % MOD * C(m + m - 4, m - 2) % MOD << endl;
	return 0;
}
