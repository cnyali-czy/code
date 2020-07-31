/*
	Problem:	A.cpp
	Time:		2020-07-31 08:13
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 2e5 + 10;

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
#define inv(x) power_pow(x, MOD - 2, MOD)

	template <typename T>
inline T read()
{
	T f = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		f = f * 10 + c - 48;
		c = getchar();
	}
	return f * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, f[maxn];


int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	const int MOD = read<int>();
	f[0] = f[1] = 1;
	REP(i, 2, 200000)
	{
		i64 tmp = (10ll * i * i + 2 * i - 3) % MOD * f[i - 1] % MOD - 9ll * (i - 1) * (i - 1) % MOD * f[i - 2] % MOD;
		f[i] = inv(i + 2) * inv(i + 2) % MOD * tmp % MOD;
	}
	while (T--) printf("%d\n", (f[read<int>()] + MOD) % MOD);
	return 0;
}
