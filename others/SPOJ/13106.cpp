/*
	Problem:	13106.cpp
	Time:		2020-11-25 12:26
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
const int maxn = 1e6 + 10, maxm = 20, MOD = 1e9 + 7;

void inc(int &x, i64 y) {x = (x + y) % MOD;}
void dec(int &x, i64 y) {if (y > MOD) y %= MOD;x = (x - y + MOD) % MOD;}

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

int n, m, f[1 << maxm], cnt[1 << maxm];

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

signed main()
{
#ifdef CraZYali
	file("13106");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		int t = 0;
		REP(j, 1, read<int>()) t |= (1 << read<int>() - 1);
		f[t]++;
	}
	const int L = (1 << m) - 1;
	REP(i, 0, m - 1) REP(j, 0, L) if (j >> i & 1) inc(f[j], f[j ^ (1 << i)]);
	static int bin[maxn];
	bin[0] = 1;
	REP(i, 1, n) bin[i] = 2 * bin[i - 1] % MOD;
	i64 ans = 0;
	REP(i, 0, L)
	{
		cnt[i] = cnt[i >> 1] + (i & 1);
		i64 res = bin[f[i]] - 1;
		if (m - cnt[i] & 1) res = MOD - res;
		ans += res;
	}
	cout << ans % MOD << endl;
	return 0;
}
