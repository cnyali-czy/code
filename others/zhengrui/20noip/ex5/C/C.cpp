/*
	Problem:	C.cpp
	Time:		2020-12-18 19:29
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
const int maxn = 1e5 + 10, MOD = 998244353;

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

int n;
int invs[maxn], fac[maxn], s1[maxn], s2[maxn];
i64 sqr(i64 x) {return x * x % MOD;}
void init(int n)
{
	invs[0] = invs[1] = 1;
	fac[0] = fac[1] = 1;
	s1[1] = s2[1] = 1;
	REP(i, 2, n)
	{
		invs[i] = 1ll * invs[MOD % i] * (MOD - MOD / i) % MOD;
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		s1[i] = (s1[i - 1] + invs[i]) % MOD;
		s2[i] = (s2[i - 1] + 1ll * invs[i] * invs[i]) % MOD;
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	init(1e5);
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		i64 ans = 0;
		ans = (sqr(s1[n]) + s1[n] + MOD - s2[n]) % MOD * fac[n] % MOD;
//		REP(i, 1, n)
//			(ans += 1ll * i * i % MOD * str[n][i]) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
