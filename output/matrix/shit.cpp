/*
	Problem:	matrixinv.cpp
	Time:		2020-08-16 09:40
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
const int maxn = 400 + 5, MOD = 1e9 + 7;

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

int n, a[maxn][maxn], is[maxn], js[maxn];

int main()
{
	freopen("matrix.in", "r", stdin);
	freopen("shit.out", "w", stdout);
	n = read<int>();
	REP(i, 1, n) REP(j, 1, n)
	{
		double x;
		scanf("%lf", &x);
		if (x > 1e-9) a[i][j] = rand();
	}
	REP(i, 1, n)
	{
		REP(j, i, n) REP(k, i, n) if (a[j][k])
		{
			is[i] = j;
			js[i] = k;
			break;
		}
		REP(j, 1, n) swap(a[i][j], a[is[i]][j]);
		REP(j, 1, n) swap(a[j][i], a[j][js[i]]);
		if (!a[i][i])
		{
			puts("No Solution");
			return 0;
		}
		a[i][i] = inv(a[i][i]);
		REP(j, 1, n) if (i ^ j) a[i][j] = 1ll * a[i][j] * a[i][i] % MOD;
		REP(j, 1, n) if (i ^ j)
			REP(k, 1, n) if (i ^ k)
			a[j][k] = (a[j][k] - 1ll * a[j][i] * a[i][k]) % MOD;
		REP(j, 1, n) if (i ^ j)
			a[j][i] = -1ll * a[j][i] * a[i][i] % MOD;
	}
	DEP(i, n, 1)
	{
		REP(j, 1, n) swap(a[j][i], a[j][is[i]]);
		REP(j, 1, n) swap(a[i][j], a[js[i]][j]);
	}
	REP(i, 1, n) REP(j, 1, n) printf("%d%c", (a[i][j] + MOD) % MOD, j == end_j ? '\n' : ' ');
	return 0;
}
