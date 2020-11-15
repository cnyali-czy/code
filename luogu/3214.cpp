/*
	Problem:	3214.cpp
	Time:		2020-11-15 22:12
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
const int maxn = 1e6 + 10, MOD = 1e8 + 7;

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

int n, m;
int Inv[maxn];
void init(int n)
{
	Inv[0] = Inv[1] = 1;
	REP(i, 2, n) Inv[i] = 1ll * (MOD - MOD / i) * Inv[MOD % i] % MOD;
	REP(i, 1, n) Inv[i] = 1ll * Inv[i] * Inv[i - 1] % MOD;
}
inline i64 C(int n, int m)
{
	if (n < 0) n += MOD;if (m < 0) m += MOD;
	if (n < m || m < 0) return 0;
	i64 d = 1;
	REP(i, 0, m - 1) (d *= (n - i)) %= MOD;
	return d * Inv[m] % MOD;
}
inline i64 sgn(int x) {return x & 1 ? -1 : 1;}
int main()
{
#ifdef CraZYali
	file("3214");
#endif
	n = read<int>();m = read<int>();
	init(m);
	i64 ans = 0, n12 = power_pow(2, n - 1), n2 = n12 * 2 % MOD;

	static int c1[maxn], c2[maxn];
	i64 d = 1;
	REP(i, 0, m)
	{
		c1[i] = d * Inv[i] % MOD;
		(d *= n12 - 1 - i) %= MOD;
	}
	d = 1;
	REP(i, 0, m)
	{
		c2[i] = d * Inv[i] % MOD;
		(d *= n12 - i) %= MOD;
	}
	REP(i, 0, m)
		ans = (ans + sgn(m - i) * c1[i] * c2[m - i]) % MOD;
	(ans *= (n2 - 1)) %= MOD;
	ans += C(n2 - 1, m) + MOD;
	cout << ans * inv(n2) % MOD << endl;

	return 0;
}
