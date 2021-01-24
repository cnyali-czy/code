/*
	Problem:	B.cpp
	Time:		2021-01-19 23:06
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
const int maxm = 3e3 + 10, maxn = 50 + 10;

int MOD;
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

int n, k, fac[maxn], Inv[maxn], invs[maxn], m;
void inc(int &x, i64 y) {x = (x + y) % MOD;}

int f[maxm][maxn], h[maxn];

i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

namespace lag
{
	int y[maxm];
	int calc(int n, int X)
	{
		int ans = 0;
		REP(i, 1, n)
		{
			int down = 1, up = 1;
			REP(j, 1, n) if (i ^ j)
			{
				down = 1ll * down * (i + MOD - j) % MOD;
				up = 1ll * up * (X + MOD - j) % MOD;
			}
			ans = (ans + up * inv(down) % MOD * y[i]) % MOD;
		}
		return ans;
	}
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> k >> MOD;
	m = min(n * (n - 1) / 2 + 1, k);
	
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}

	f[0][1] = 1;
	REP(i, 1, m)
	{
		static int pre[maxn];
		REP(j, 1, n)
			pre[j] = power_pow(k - i, MOD - 1 - (j * (j - 1) / 2 + 1));
		REP(j, 1, n)
		{
			static int g[maxn];
			memset(g, 0, sizeof g);
			g[0] = 1;
			static int con[maxn][maxn];
			REP(u, 1, n)
				REP(v, 1, u)
				{
					int val = 1ll * pre[v] * f[i - 1][v] % MOD * v % MOD * j % MOD;
					inc(g[u], C(u - 1, v - 1) * val % MOD * g[u - v]);
				}
			f[i][j] = 1ll * g[j] * invs[j] % MOD * invs[j] % MOD * power_pow(k - i, j * (j - 1) / 2 + 1) % MOD;
			if (i == k) f[i][j] = f[i - 1][j] + (j == 2);
		}
		lag :: y[i] = f[i][n];
	}
	cout << lag :: calc(m, k) << endl;
	return 0;
}
