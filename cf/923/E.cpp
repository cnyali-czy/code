/*
	Problem:	E.cpp
	Time:		2020-08-10 21:45
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
const int maxk = 5000 + 10, MOD = 1e9 + 7, inv2 = MOD + 1 >> 1;

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

int n, k, str[maxk][maxk], invs[maxk];

int main()
{
#ifdef CraZYali
	file("E");
#endif
	cin >> n >> k;
	str[0][0] = 1;
	REP(i, 1, k) REP(j, 1, i) str[i][j] = (str[i - 1][j - 1] + 1ll * j * str[i - 1][j]) % MOD;
	invs[0] = invs[1] = 1;
	REP(i, 2, k) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
	i64 ans = 0, fac = 1, C = 1, bin2 = power_pow(2, n);
	REP(i, 1, k)
	{
		(fac *= i) %= MOD;
		C = C * (n - i + 1) % MOD * invs[i] % MOD;
		(bin2 *= inv2) %= MOD;
		ans += str[k][i] * fac % MOD * C % MOD * bin2 % MOD;
	}
	cout << ans % MOD << endl;
	return 0;
}
