#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64
#define poly vector <int>

using namespace std;
const int maxn = 1e7 + 10, MOD = 1e9 + 7, inv2 = MOD + 1 >> 1;

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

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

int n, g[maxn];
int main()
{
#ifndef ONLINE_JUDGE
	file("A");
#endif
	n = read<int>();
	i64 n2 = power_pow(2, n);
	g[0] = 1;g[1] = 0;

	i64 sb = n2 - 1;
	REP(i, 2, n)
	{
		g[i] = (sb - (i - 1ll) * (n2 - 1 - (i - 2ll)) % MOD * g[i - 2] - g[i - 1]) % MOD;
		sb = sb * (n2 - i) % MOD;
	}
	cout << (MOD + sb - g[n]) % MOD << endl;
	return 0;
}
