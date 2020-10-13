/*
	Problem:	181.cpp
	Time:		2020-10-12 10:36
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 40, maxm = 25, MOD = 998244353, inv2 = MOD + 1 >> 1;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
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

int n, m;
int u[maxm], v[maxm], p[maxm];
int bininv[maxn * maxn];
struct __init__
{
	__init__()
	{
		bininv[0] = 1;
		REP(i, 1, maxn * maxn - 1) bininv[i] = 1ll * bininv[i - 1] * inv2 % MOD;
	}
}__INIT__;
inline int at(int x, int p) {return x >> p & 1;}

int N;
int stk[maxn], top, dfn[maxn];
bool vis[maxn];
void dfs(int x)
{
	N++;
	vis[x] = 1;
	dfn[stk[++top] = x] = top;
	for (int i = bg[x]; i; i = ne[i])
		if (!vis[to[i]]) dfs(to[i]);
}
int dp[maxn][maxn], f[maxm];

int main()
{
#ifdef CraZYali
	file("181");
#endif
	const i64 Inv = inv(10000);
	static int G[maxn][maxn];
	n = read<int>();m = read<int>();
	REP(i, 0, n - 1) REP(j, 0, n - 1) G[i][j] = inv2;
	REP(i, 1, m)
	{
		u[i] = read<int>() - 1;
		v[i] = read<int>() - 1;
		p[i] = Inv * read<int>() % MOD;
		G[u[i]][v[i]] = p[i];
		G[v[i]][u[i]] = (1 + MOD - p[i]) % MOD;
		add(u[i], v[i]);
		add(v[i], u[i]);
	}
	i64 w = power_pow(10000, n * (n - 1));
	f[0] = 1;
	REP(x, 0, n - 1) if (!vis[x])
	{
		top = 0;
		dfs(x);
		static i64 g[maxn];
		REP(S, 0, (1 << top) - 1)
		{
			i64 res = 1, c = 0;
			REP(j, 0, top - 1) if (at(S, j))
			{
				c++;
				int x = stk[j + 1];
				for (int i = bg[x]; i; i = ne[i])
					if (at(~S, dfn[to[i]] - 1))
						res = 2ll * res * G[x][to[i]] % MOD;
			}
			g[c] += res;
		}
		REP(i, 0, N) if (g[i] >= MOD) g[i] %= MOD;
		DEP(j, N, 0)
			DEP(k, j, 1) f[j] = (f[j] + 1ll * f[j - k] * g[k]) % MOD;
		REP(i, 0, N) g[i] = 0;
	}
	i64 ans = 1;
	REP(i, 1, n - 1) ans = (ans + 1ll * f[i] * bininv[i * (n - i)]) % MOD;
	ans = ans % MOD * w % MOD;
	cout << ans << endl;
	return 0;
}
