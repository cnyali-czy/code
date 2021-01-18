/*
	Problem:	C.cpp
	Time:		2020-12-30 15:37
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
const int maxn = 1e6 + 10, maxq = 1e6 + 10, MOD = 1e9 + 7;

i64 power_pow(i64 base, i64 b)
{
	i64 ans = 1;
	if (!base && b == MOD - 2) return 1;
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

int n, x, y, p ,v;

int binp[maxn], bin1p[maxn], binv[maxn], a[maxn], b[maxn];
void init(int a[], int x, int n)
{
	a[0] = 1;
	REP(i, 1, n) a[i] = 1ll * a[i - 1] * x % MOD;
}
void init(int n)
{
	init(binp, p, n);
	init(binv, v, n);
	a[0] = 1;REP(i, 1, n) a[i] = (binv[i] - 1ll) * a[i - 1] % MOD;a[n] = inv(a[n]);DEP(i, n - 1, 0) a[i] = a[i + 1] * (binv[i + 1] - 1ll) % MOD;
	b[0] = 1;REP(i, 1, n) b[i] = (binp[i] - 1ll) * b[i - 1] % MOD;b[n] = inv(b[n]);DEP(i, n - 1, 0) b[i] = b[i + 1] * (binp[i + 1] - 1ll) % MOD;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();x = read<int>();y = read<int>();
	p = x * inv(y) % MOD;v = inv(p);
	init(n);
	const int in = inv(n);
	REP(Case, 1, read<int>())
	{
		int x = read<int>() - 1;
		if (!x)
		{
			printf("%d\n", in);
			continue;
		}
		i64 res = 0;
		REP(i, 1, x)
			res = (res + power_pow((1ll - binp[i]) * binv[i] % MOD, x - 1) * (1 - power_pow(1 - binp[i], n - x)) % MOD * binv[i] % MOD * a[i - 1] % MOD * b[x - i]) % MOD;
		res = res * power_pow(p, 1ll * x * (x + 1) / 2) % MOD * in % MOD;
		res = (res + MOD) % MOD;
		cout << res << '\n';
	}
	return 0;
}
