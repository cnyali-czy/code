/*
	Problem:	1939-new.cpp
	Time:		2021-01-08 20:05
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int MOD = 1e9 + 7;
#define poly vector <int>

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

poly operator * (poly f, poly g)
{
	int n = f.size() - 1, m = g.size() - 1;
	static u64 res[10];
	REP(i, 0, n) if (f[i])
	{
		u64 fi = f[i];
		REP(j, 0, m) if (g[j])
			res[i + j] += fi * g[j];
	}
	f.resize(n + m + 1);
	REP(i, 0, n + m)
	{
		if (res[i] >= MOD) res[i] %= MOD;
		f[i] = res[i];res[i] = 0;
	}
	return f;
}

poly sqr(poly f)
{
	static u64 res[10];
	int n = f.size() - 1;
	REP(i, 0, n) if (f[i]) {u64 fi = f[i];REP(j, 0, n) if (f[j]) res[i + j] += fi * f[j];}
	f.resize(n + n + 1);
	REP(i, 0, n + n)
	{
		if (res[i] >= MOD) res[i] %= MOD;
		f[i] = res[i];res[i] = 0;
	}
	return f;
}
poly Mod(poly f, const poly &g)
{
	int n(f.size() - 1), m(g.size() - 1);
	if (m > n) return f;
	//g[m] = 1
//	const i64 Inv = inv(g[m]);
	DEP(i, n, m) if (f[i])
	{
		const i64 qaq = f[i];
		REP(j, 0, m)
			f[j - m + i] = (f[j - m + i] - g[j] * qaq) % MOD;
	}
	f.resize(m);
	REP(i, 0, m - 1) if (f[i] < 0) f[i] += MOD;
	return f;
}

poly g, bin[32];

int main()
{
#ifdef CraZYali
	file("1939-new");
#endif
	g.resize(4);
	g[0] = MOD - 1;g[2] = MOD - 1;g[3] = 1;
	bin[0].resize(2);bin[0][1] = 1;
	REP(i, 1, 31) bin[i] = Mod(sqr(bin[i - 1]), g);
	register int T = read<int>();
	while (T--)
	{
		long long n = read<long long>() - 1;
		if (n <= 2) {printf("%d\n", 1);continue;}
		poly f(1, 1);
		REP(i, 0, 31) if (n >> i & 1) f = Mod(f * bin[i], g);
		f.resize(3);
		printf("%lld\n", ((i64)f[0] + f[1] + f[2]) % MOD);
	}
	return 0;
}
