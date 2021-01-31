/*
	Problem:	A.cpp
	Time:		2021-01-31 15:21
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
#define int long long

using namespace std;
const int maxn = 5e6 + 10;

int n, k, p;
int power_pow(int base, int b)
{
	const int MOD = p;
	int ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}

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

int fac[maxn], invs[maxn], Inv[maxn];

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> k >> p;n /= 2;
	const int MOD = p;
	k %= MOD;
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n << 1)
	{
		fac[i] = i * fac[i - 1] % MOD;
		invs[i] = (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = invs[i] * Inv[i - 1] % MOD;
	}
	static int h[maxn];
	h[0] = 1;
	int bin = 1;
	REP(i, 1, n)
	{
		(bin *= (k - 1)) %= MOD;
		h[i] = MOD - fac[i - 1 << 1] * Inv[i] % MOD * Inv[i - 1] % MOD * k % MOD * bin % MOD;
	}
	int ans = 0;
	bin = 1;
	REP(i, 0, n) 
	{
		(ans += h[n - i] * bin) %= MOD;
		(bin *= (k * k % MOD)) %= MOD;
	}
	cout << ans << endl;
	return 0;
}
