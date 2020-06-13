/*
	Problem:	5170-new.cpp
	Time:		2020-06-13 23:26
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
const int MOD = 998244353, inv2 = MOD + 1 >> 1, inv3 = (MOD + 1) / 3;
#define i64 long long

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

struct Ans
{
	int f, g, h;
};

Ans calc(i64 n, int a, int b, int c)
{
	if (!n) return {b / c, 0, 1ll * (b / c) * (b / c) % MOD};
	if (!a) return {(n + 1) * (b / c) % MOD, n * (n + 1) / 2 % MOD * (b / c) % MOD, (n + 1) * (b / c) % MOD * (b / c) % MOD};
	if (a >= c || b >= c)
	{
		auto res = calc(n, a % c, b % c, c);
		i64 f = res.f, g = res.g, h = res.h;
		const i64 s1 = n * (n + 1ll) / 2 % MOD, s2 = s1 * (n + n + 1) % MOD * inv3 % MOD;
		const int ac = a / c, bc = b / c;
		(h +=	2ll * (bc * f + ac * g) + s2 * ac % MOD * ac + (n + 1ll) * bc % MOD * bc + s1 * 2 * ac % MOD * bc) %= MOD;
		(f +=	s1 * ac + (n + 1ll) * bc) %= MOD;
		(g +=	s2 * ac	+ s1 * bc) %= MOD;
		return {f, g, h};
	}
	i64 m = (1ll * a * n + b) / c;
	auto res = calc(m - 1, c, c - b - 1, a);
	m %= MOD;
	const i64 nm = n * m % MOD;
	int f = (MOD + nm - res.f) % MOD;
	int g = (nm * (n + 1) - res.h - res.f + MOD + MOD) % MOD * inv2 % MOD;
	int h = (nm * (m + 1) - 2ll * (res.g + res.f) - f + 5ll * MOD) % MOD;
	return {f, g, h};
}

int main()
{
#ifdef CraZYali
	file("5170-new");
#endif
	register int T = read<int>();
	while (T--)
	{
		int n = read<int>(), a = read<int>(), b = read<int>(), c = read<int>();
		auto ans = calc(n, a, b, c);
		printf("%d %d %d\n", ans.f, ans.h, ans.g);
	}
	return 0;
}
