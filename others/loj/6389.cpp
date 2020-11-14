/*
	Problem:	6389.cpp
	Time:		2020-10-31 19:54
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <iostream>
#include <cstdio>
#define i64 long long
#define ui64 unsigned i64
using namespace std;
const int maxn = 23335;

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

const int N = 23333;
int n, f[maxn], g[maxn], P;
int invs[maxn];

void maintain(int i, int v)
{
	static const int MOD = P;
//	REP(j, 1, N / i) g[i * j] = (g[i * j] + 1ll * invs[j] * v) % MOD;
	v = 1ll * v * i % MOD;
	for (int j = i; j <= N; j += i) g[j] = (g[j] + v) % MOD;
}

int main()
{
#ifdef CraZYali
	file("6389");
#endif
	register int T = read<int>();
	P = read<int>();
	const int MOD = P;
	invs[0] = invs[1] = 1;
	REP(i, 2, N) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
	maintain(1, 1);
	f[0] = 1;
	f[1] = 1;
	const ui64 LIM = 16e18;
	REP(i, 1, N - 1)
	{
		ui64 res = 0;
		REP(j, 0, i)
		{
//			res += (j + 1ll) * g[j + 1] % MOD * f[i - j];
			res += 1ll * g[j + 1] * f[i - j];
			if (res >= LIM) res %= MOD;
		}
		if (res >= MOD) res %= MOD;
		res = res * invs[i + 1] % MOD;
		maintain(i + 1, res);
		f[i + 1] = res * 2 % MOD;
//		if (i % 1000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", i, (N - 1), i * 100. / (N - 1));
	}
	while (T--)
	{
		int n = read<int>();
		if (n == 1) puts("1");
		else printf("%d\n", f[n]);
	}
//	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
