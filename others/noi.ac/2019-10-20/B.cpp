/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Year		:	2019.10.20 14:26
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e6 + 10, MOD = 998244353;

int power_pow(long long base, int b)
{
	long long ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

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

int fac[maxn], Inv[maxn];
inline void init(const int n = 1e6)
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * fac[i-1] * i % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n - 1, 0) Inv[i] = 1ll * Inv[i+1] * (i + 1) % MOD;
}

int n, m, k, p;
inline int C(int n, int m) {return n < m || n < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
inline int f(int qaq)
{
	switch (qaq)
	{
		case 0:
			return C(n - 1, m - 1);
		case 1:
			return 1ll * m * (1ll * C(n - p, m - 2) * (p - 1) % MOD + C(n - p, m - 1)) % MOD;
		case 2:
			return 1ll * m * (C(n - p, m - 1) + C(n - p + 1, m - 1)) % MOD;
		case 3:
			return m == 3 ? 1ll * Inv[2] * p % MOD * (p - 1) % MOD : 0ll;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	init();
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		p = (n + 1) / 2;
		m = read<int>();
		k = read<int>();
		if (k > 3)
		{
			puts("0");
			continue;
		}
		int ans(0);
		REP(i, k, 3)
			(ans += 1ll * C(i, k) * f(i) % MOD * (1ll - (i - k) % 2 * 2) % MOD) %= MOD;
		cout << (1ll * ans * Inv[m] % MOD * fac[m-1] % MOD * n % MOD + MOD) % MOD << endl;
	}
	return 0;
}
