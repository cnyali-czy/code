/*
	Problem:	C.cpp
	Time:		2021-01-19 17:29
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
const int maxn = 1e6 + 10, MOD = 998244353;

const int w = 1e5;
int b1[maxn], b2[maxn];
struct __init__
{
	__init__()
	{
		b1[0] = 1;
		REP(i, 1, w) b1[i] = b1[i - 1] * 3ll % MOD;
		b2[0] = 1;
		REP(i, 1, w) b2[i] = 1ll * b2[i - 1] * b1[w] % MOD;
	}
}__INIT__;
i64 power_pow(i64 base, i64 b)
{
	b %= (MOD - 1);b += MOD - 1;
	if (base == 3) return 1ll * b1[b % w] * b2[b / w] % MOD;
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

int n, fac[maxn], Inv[maxn];
void init(int n)
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[n] = inv(fac[n]);
	DEP(i, n - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
}
i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

inline i64 f(int i, int j)
{
	if (!j) return power_pow(3, i + 1ll * (n - i) * n);
	if (!i) return power_pow(3, j + 1ll * (n - j) * n);
	return power_pow(3, 1 + 1ll * (n - i) * (n - j));
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();init(n);
	i64 ans = 0, all = power_pow(3, 1ll * n * n);

	REP(i, 0, n) (ans += (i & 1 ? -1 : 1) * C(n, i) * f(i, 0)) %= MOD;
	ans = ans * 2 - all;

	REP(i, 1, n)
	{
		i64 res = power_pow(1 - power_pow(3, -(n - i)), n) - 1;
		res = res * C(n, i) % MOD * (i & 1 ? -1 : 1) * power_pow(3, 1 + 1ll * (n - i) * n) % MOD;
		(ans += res) %= MOD;
	}

	cout << (power_pow(3, 1ll * n * n) - ans + MOD) % MOD << endl;
	return 0;
}
