/*
	Problem:	G.cpp
	Time:		2021-01-27 21:32
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10, maxk = 200 + 5, MOD = 1e9 + 7;

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

int n, k, f[maxn][maxk], ans[maxk];
int fac[maxk], str[maxk][maxk];

void init()
{
	fac[0] = 1;
	REP(i, 1, k) fac[i] = 1ll * i * fac[i - 1] % MOD;
	str[0][0] = 1;
	REP(i, 1, k) REP(j, 1, i) str[i][j] = (str[i - 1][j - 1] + 1ll * j * str[i - 1][j]) % MOD;
}
vector <int> G[maxn];
int siz[maxn];
void dfs(int u, int fa = 0)
{
	siz[u] = 1;
	f[u][0] = 2;
	for (int v : G[u]) if (v ^ fa)
	{
		dfs(v, u);
		static int tmp[maxk];
		REP(i, 0, min(siz[u], k)) REP(j, 0, min(k - i, siz[v]))
			tmp[i + j] = (tmp[i + j] + 1ll * f[u][i] * f[v][j]) % MOD;
		REP(i, 0, k) f[u][i] = tmp[i], tmp[i] = 0, (ans[i] -= f[v][i]) %= MOD;
		siz[u] += siz[v];
	}
	REP(i, 0, k) (ans[i] += f[u][i]) %= MOD;
	DEP(i, k, 1) (f[u][i] += f[u][i - 1]) %= MOD;
	f[u][1]--;
}

int main()
{
#ifdef CraZYali
	file("G");
#endif
	n = read<int>();k = read<int>();
	init();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		G[x].emplace_back(y);G[y].emplace_back(x);
	}
	dfs(1);
	i64 Ans = 0;
	REP(i, 0, k) (Ans += 1ll * fac[i] * str[k][i] % MOD * ans[i]) %= MOD;
	cout << (Ans + MOD) % MOD << endl;
	return 0;
}
