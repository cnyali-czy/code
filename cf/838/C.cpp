/*
	Problem:	C.cpp
	Time:		2020-10-21 19:43
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2.5e5 + 10;

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

int n, k, p;
i64 power_pow(i64 base, int b, const i64 MOD = p)
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

int fac[maxn], Inv[maxn];
void init()
{
	const int MOD = p;
	fac[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[n] = inv(fac[n]);
	DEP(i, n - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
}

int f[26][maxn];

int dp(int x, int S)
{
	if (~f[x][S]) return f[x][S];
	const int MOD = p;
	if (!S)
	{
		i64 res = fac[n];
		REP(i, 1, x) res = res * (k - i + 1) % MOD;
		return res;
	}
	i64 res = 0;
	int U = S & (S - 1);
	for (int U = S & (S - 1), T = U; ; T = (T - 1) & U)
	{
		res = (res + 1ll * Inv[S - T] * dp(x + 1, T)) % MOD;
		if (!T) break;
	}

	return f[x][S] = res;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> k >> p;
	i64 ans = power_pow(k, n);
	const int MOD = p;

	if (n % 2 == 0)
	{
		init();
		memset(f, -1, sizeof f);
		ans = (ans + MOD - dp(0, n)) % MOD;
	}
	cout << ans << endl;
	return 0;
}
