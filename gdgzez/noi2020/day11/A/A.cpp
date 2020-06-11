/*
	Problem:	A.cpp
	Time:		2020-06-11 15:18
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

using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353, inv2 = MOD + 1 >> 1;
#define i64 long long
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

int n, a[maxn], m, s[maxn][31][2];

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		REP(j, 0, 30) s[i][j][a[i] >> j & 1]++;
	}
	REP(i, 1, n) REP(j, 0, 30) s[i][j][0] += s[i - 1][j][0], s[i][j][1] += s[i - 1][j][1];
	while (m--)
	{
		int l = read<int>(), r = read<int>(), x = read<int>();
		i64 ans = 0;
		REP(j, 0, 30)
		{
			int s0 = s[r][j][0] - s[l - 1][j][0], s1 = s[r][j][1] - s[l - 1][j][1];
			i64 res = power_pow(x + 1, s0) * (power_pow(x + 1, s1) - power_pow(1 + MOD - x, s1) + MOD) % MOD;
			(ans += res << j) %= MOD;
		}
		cout << ans * inv2 % MOD << '\n';
	}
	return 0;
}
