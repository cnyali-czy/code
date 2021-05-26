/*
	Problem:	4996.cpp
	Time:		2021-01-29 08:47
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
const int maxn = 18, MOD = 998244353, inv2 = MOD + 1 >> 1;

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

int n, p[1 << maxn], N;
void fwt(int a[], int flag)
{
	for (int i = 1; i < N; i <<= 1)
		for (int k = 0; k < N; k += (i << 1))
			REP(l, 0, i - 1)
			{
				int x = a[k + l], y = a[k + l + i];
				if (flag == -1)
				{
					x = 1ll * x * inv2 % MOD;
					y = 1ll * y * inv2 % MOD;
				}
				a[k + l] = (x + y) % MOD;
				a[k + l + i] = (x + MOD - y) % MOD;
			}
}

signed main()
{
#ifdef CraZYali
	file("4996");
#endif
	n = read<int>();N = 1 << n;
	i64 sp = 0;
	REP(i, 0, N - 1) sp += (p[i] = read<int>());
	sp = inv(sp % MOD);
	REP(i, 0, N - 1) p[i] = p[i] * sp % MOD;
	static int f[1 << maxn], g[1 << maxn], I[1 << maxn];
	REP(i, 0, N - 1) g[i] = (!i) + MOD - p[i];
	REP(i, 0, N - 1) I[i] = 1;
	fwt(g, 1);fwt(I, 1);
	REP(i, 0, N - 1) f[i] = (MOD + I[i] - N) * inv(g[i]) % MOD;
	fwt(f, -1);
	int e0 = f[0];
	REP(i, 0, N - 1) printf("%d\n", (MOD + f[i] - e0) % MOD) ;
	return 0;
}
