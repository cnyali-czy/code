/*
	Problem:	4859.cpp
	Time:		2020-04-02 15:29
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
const int maxn = 2000 + 10, MOD = 1e9 + 9;

inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

int power_pow(i64 base, int b)
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

int invs[maxn], Inv[maxn], fac[maxn], n, a[maxn], b[maxn], c[maxn], k, dp[maxn][maxn], F[maxn], G[maxn];
inline int C(int n, int m) {return 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int main()
{
#ifdef CraZYali
	file("4859");
#endif
	n = read<int>();k = read<int>();
	if ((n + k) & 1)
	{
		puts("0");
		return 0;
	}
	(k += n) >>= 1;
	REP(i, 1, n) a[i] = read<int>();sort(a + 1, a + 1 + n);
	REP(i, 1, n) b[i] = read<int>();sort(b + 1, b + 1 + n);
	REP(i, 1, n)
	{
		int &j = c[i];j = c[i-1];
		while (j < n && b[j + 1] < a[i]) j++;
	}
	dp[0][0] = 1;
	REP(i, 1, n)
		REP(j, 0, i)
		{
			dp[i][j] = dp[i-1][j];
			if (j && j <= c[i]) inc(dp[i][j], dp[i-1][j-1] * (c[i] - j + 1ll) % MOD);
		}
	invs[0] = invs[1] = 1;
	Inv[0] = Inv[1] = 1;
	fac[0] = fac[1] = 1;
	REP(i, 2, n)
	{
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * Inv[i-1] * invs[i] % MOD;
		fac[i] = 1ll * fac[i-1] * i % MOD;
	}
	REP(i, 1, n) F[i] = 1ll * fac[n - i] * dp[n][i] % MOD;
	int ans = 0;
	REP(i, k, n) inc(ans, ((i - k) & 1 ? MOD - 1ll : 1ll) * C(i, k) % MOD * F[i] % MOD);
	cout << ans << '\n';
	return 0;
}
