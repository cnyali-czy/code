/*
	Problem:	A.cpp
	Time:		2020-08-09 09:42
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
const int maxn = 1e5 + 10, MOD = 998244353;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int n, m, k, s, all;
bool ins[maxn];

int dp[maxn][2];

namespace one
{
	void dfs(int x, int fa = 0)
	{
		dp[x][0] = 1;
		dp[x][1] = !ins[x];
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs(to[i], x);
			dp[x][0] = dp[x][0] * (dp[to[i]][0] * (m - 2ll) % MOD + dp[to[i]][1]) % MOD;
			dp[x][1] = dp[x][1] * (dp[to[i]][0] * (m - 1ll) % MOD) % MOD;
		}
	}
	void work()
	{
		dfs(1);
		int tot = (dp[1][0] * (m - 1ll) + dp[1][1]) % MOD;
		cout << 1ll * m * (all + MOD - tot) % MOD << endl;
	}
}

namespace shit
{
	const int maxk = 100;
	int str[maxk][maxk];
	inline i64 sgn(int x) {return x & 1 ? -1 : 1;}
	int f[maxn], h[maxn], g[maxn];
	int fac[maxn], Inv[maxn];
	struct __init__
	{
		__init__(const int N = 1e5)
		{
			fac[0] = 1;
			REP(i, 1, N) fac[i] = 1ll * i * fac[i - 1] % MOD;
			Inv[N] = inv(fac[N]);
			DEP(i, N - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
		}
	}__INIT__;
	inline i64 C(int n, int m) {return 1ll * fac[n] * Inv[n - m] % MOD * Inv[m] % MOD;}
	i64 J;
	void dfs(int x, int fa = 0)
	{
		dp[x][0] = 1;
		dp[x][1] = !ins[x];
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs(to[i], x);
			dp[x][0] = (dp[to[i]][0] * (m - 1 - J) + dp[to[i]][1] * J) % MOD * dp[x][0] % MOD;
			dp[x][1] = (dp[to[i]][0] * (m - J) + dp[to[i]][1] * (J - 1)) % MOD * dp[x][1] % MOD;
		}
	}
	void work()
	{
		str[0][0] = 1;
		REP(i, 1, k)
			REP(j, 1, i)
				str[i][j] = (str[i - 1][j - 1] + 1ll * j * str[i - 1][j]) % MOD;
		f[0] = all;
		REP(j, 1, k)
		{
			J = j;
			dfs(1);
			f[j] = (1ll * dp[1][0] * (m - j) + 1ll * dp[1][1] * j) % MOD;
		}
		i64 ans = 0, fac = 1;
		REP(i, 0, k)
		{
			i64 res = 0;
			REP(j, 0, i) res += sgn(j) * C(i, j) * f[j] % MOD;
			h[i] = (res % MOD + MOD) % MOD;
		}
		REP(i, 0, k)
		{
			g[i] = C(m, i) * h[i] % MOD;
			ans += fac * str[k][i] % MOD * g[i] % MOD;
			(fac *= (i + 1)) %= MOD;
		}
		cout << (ans % MOD + MOD) % MOD << endl;
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();k = read<int>();s = read<int>();
	all = power_pow(m - 1, n - 1) * m % MOD;
	REP(i, 1, s) ins[read<int>()] = 1;
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	if (k == 1) one :: work();
	else shit :: work();
	return 0;
}
