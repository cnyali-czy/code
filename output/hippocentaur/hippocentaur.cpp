/*
	Problem:	hippocentaur.cpp
	Time:		2020-09-30 09:27
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
const int maxn = 2e7 + 10, MOD = 998244353;

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

int n;

int main()
{
	file("hippocentaur");
	n = read<int>();
	int fac = 1;
	i64 ans = 1;
	REP(i, 1, n + n)
	{
		fac = 1ll * i * fac % MOD;
		if (i == n)
		{
			const int I = inv(fac);
			(ans *= I) %= MOD;
			(ans *= I) %= MOD;
		}
	}
	(ans *= fac) %= MOD;

	ans = 8 * ans - 3ll * n % MOD * n - 2 * n - 7;
	ans = (ans % MOD + MOD) % MOD;
	cout << ans << endl;
	return 0;
}
