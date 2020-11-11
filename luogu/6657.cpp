/*
	Problem:	6657.cpp
	Time:		2020-11-06 19:37
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
const int maxn = 1e6 + 10, MOD = 998244353;

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

int n, m, a[105], b[105], M[105][105];

int det(int n, int a[105][105])
{
	int ans = 1;
	REP(i, 1, n)
	{
		if (!a[i][i])
			REP(j, i + 1, n) if (a[j][i])
			{
				swap(a[i], a[j]);
				ans = MOD - ans;
				break;
			}
		if (!a[i][i]) return 0;
		ans = 1ll * ans * a[i][i] % MOD;
		const i64 Inv = inv(a[i][i]);
		REP(j, i + 1, n) if (a[j][i])
		{
			const i64 tmp = a[j][i] * Inv % MOD;
			REP(k, i, n) a[j][k] = (a[j][k] + MOD - tmp * a[i][k] % MOD) % MOD;
		}
	}
	return ans;
}

int fac[maxn << 1], Inv[maxn << 1];
void init(int n)
{
	fac[0] = Inv[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[n] = inv(fac[n]);
	DEP(i, n - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
}
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

int main()
{
#ifdef CraZYali
	file("6657");
#endif
	init(2e6);
	REP(Case, 1, read<int>())
	{
		n = read<int>();m = read<int>();
		REP(i, 1, m) a[i] = read<int>(), b[i] = read<int>();
		REP(i, 1, m) REP(j, 1, m) M[i][j] = C(b[j] - a[i] + n - 1, n - 1);
		cout << det(m, M) << endl;
	}
	return 0;
}
