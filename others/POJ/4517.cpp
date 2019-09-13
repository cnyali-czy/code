/*
 * File Name:	4517.cpp
 * Author	:	CraZYali
 * Year		:	2019.09.13 21:01
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long
using namespace std;
const int maxn = 1000000 + 10, MOD = 1e9 + 7;
template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int power_pow(int base, int b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int fac[maxn], Inv[maxn], D[maxn];
inline void init(const int n = 1000000)
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = fac[i-1] * i % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n - 1, 0) Inv[i] = Inv[i+1] * (i+1) % MOD;
	int o(-1);
	D[0] = 1;
	REP(i, 1, n) D[i] = (i * D[i-1] + o) % MOD, o = -o;
}
inline int C(int n, int m) {return fac[n] * Inv[m] % MOD * Inv[n-m] % MOD;}

signed main()
{
#ifdef CraZYali
	file("4517");
#endif
	init();
	DREP(hhakioi, read<int>(), 1)
	{
		int n(read<int>()), m(read<int>());
		printf("%lld\n", (C(n, m) * D[n-m] % MOD + MOD) % MOD);
	}
	return 0;
}
