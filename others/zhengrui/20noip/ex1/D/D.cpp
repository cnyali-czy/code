/*
	Problem:	D.cpp
	Time:		2020-12-18 11:25
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
const int maxn = 3e5 + 10, MOD = 998244353;

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

int n;
int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
i64 ans;

int f[maxn];
void dfs0(int x, int fa = 0)
{
	f[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs0(to[i], x);
		f[x] = (f[x] + 1ll * w[i] * f[to[i]]) % MOD;
	}
}
void dfs1(int x, int fa = 0)
{
	ans += f[x];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		f[to[i]] = (f[to[i]] + (f[x] - 1ll * f[to[i]] * w[i]) % MOD * w[i]) % MOD;
		dfs1(to[i], x);
	}
}
int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();
	REP(i, 2, n)
	{	
		int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}
//	REP(i, 1, n) dfs(i);
	dfs0(1);dfs1(1);
	ans %= MOD;(ans += MOD - n) %= MOD;
	REP(i, 1, n - 1) (ans *= i) %= MOD;
	cout << ans << endl;
	return 0;
}
