/*
	Problem:	slime.cpp
	Time:		2020-06-13 11:33
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 400 + 5, MOD = 1e9 + 9;

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

int ans, n, m;
vector <int> G[maxn];
namespace bf
{
	int pick[maxn];
	bool vis[maxn], shit[maxn], good[maxn];

	void Dfs(int x)
	{
		shit[x] = 1;
		for (int y : G[x]) if (!shit[y] && good[y]) Dfs(y);
	}
	bool judge(int l, int r)
	{
		REP(i, 1, n) shit[i] = good[i] = 0;
		REP(i, l, r) good[pick[i]] = 1;
		Dfs(pick[l]);
		REP(i, l + 1, r) if (!shit[pick[i]]) return 0;
		return 1;
	}
	void work()
	{
		REP(i, 1, n) pick[i] = i;
		do
		{
			bool flag = 1;
			REP(i, 1, n - m + 1)
				if (!judge(i, i + m - 1)) {flag = 0;break;}
			if (flag)
			{
				//				REP(i, 1, n) printf("%d%c", pick[i], i == n ? '\n' : ' ');
			}
			ans += flag;
		}while (next_permutation(pick + 1, pick + 1 + n));

	}
}

int fac[maxn], invs[maxn], Inv[maxn];
namespace algo1
{
	int dfs_clock, dfn[maxn], back[maxn], siz[maxn], fa[maxn];
	void dfs(int u)
	{
		back[dfn[u] = ++dfs_clock] = u;
		siz[u] = 1;
		for (int v : G[u]) if (v ^ fa[u]) fa[v] = u, dfs(v), siz[u] += siz[v];
	}
	inline bool inside(int grand, int child)
	{
		return dfn[grand] <= dfn[child] && dfn[child] <= dfn[grand] + siz[grand] - 1;
	}
	int jump(int x, int rt)
	{
		while (fa[x] ^ rt) x = fa[x];
		return x;
	}
	void work()
	{
		i64 ans = 0;
		REP(i, 1, n)
		{
			dfs_clock = 0;
			fa[i] = 0;
			dfs(i);
			REP(j, i + 1, n) if (siz[j] == m)
			{
				int ccc = jump(j, i);
				if (n - siz[ccc] != m) continue;
				i64 resi = fac[m], resj = fac[m];
				REP(k, 1, n)
					if (inside(j, k))
						if (j ^ k) (resj *= invs[siz[k]]) %= MOD;
						else (resj *= invs[m]) %= MOD;
					else if (!inside(ccc, k))
						if (i ^ k) (resi *= invs[siz[k]]) %= MOD;
						else (resi *= invs[m]) %= MOD;
//				cout << i << ' ' << j << ' ' << resi << ' ' << resj << endl;
				ans += resi * resj % MOD;
			}
		}
		::ans = ans * 2 % MOD;
	}
}

namespace algo2
{
	int siz[maxn], Max[maxn], rt, Min = 1e9;
	void findroot(int u, int fa = 0)
	{
		siz[u] = 1;
		Max[u] = 0;
		for (int v : G[u]) if (v ^ fa)
		{
			findroot(v, u);
			siz[u] += siz[v];
			chkmax(Max[u], siz[v]);
		}
		chkmax(Max[u], n - siz[u]);
		if (Min > Max[u])
		{
			Min = Max[u];
			rt = u;
		}
	}
	int cnt[maxn], w[maxn], xw[maxn], xsiz[maxn], dfs_clock, dfn[maxn];
	void dfs(int u, int fa)
	{
		siz[u] = 1;
		cnt[u] = 0;
		dfn[u] = ++dfs_clock;
		w[u] = 1;
		for (int v : G[u]) if (v ^ fa)
		{
			dfs(v, u);
			siz[u] += siz[v];
			w[u] = 1ll * w[u] * w[v] % MOD * Inv[siz[v]] % MOD;
		}
		w[u] = 1ll * w[u] * fac[siz[u] - 1] % MOD;
		xw[dfn[u]] = w[u];
		xsiz[dfn[u]] = siz[u];
	}
	int mc, f[maxn][maxn][maxn];
	void work()
	{
		findroot(1);
		mc = n - m;
		dfs(rt, 0);
		f[1][0][0] = 1;
		REP(i, 1, n) REP(j, 0, i) REP(k, 0, i)
		{
			(f[i + 1][j][k] += f[i][j][k]) %= MOD;
			int tmp = 1ll * f[i][j][k] * xw[i] % MOD * Inv[xsiz[i]] % MOD;
			(f[i + xsiz[i]][j + xsiz[i]][k] += tmp) %= MOD;
			(f[i + xsiz[i]][j][k + xsiz[i]] += tmp) %= MOD;
		}
		::ans = (1ll * f[n + 1][mc][mc] * fac[n - mc - mc] % MOD * fac[mc] % MOD * fac[mc]) % MOD;
	}
}

int main()
{
#ifdef CraZYali
	file("slime");
#endif
	n = read<int>();m = read<int>();
	fac[0] = fac[1] = invs[0] = invs[1] = Inv[0] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = (MOD - MOD / i) * 1ll * invs[MOD % i] % MOD;
		Inv[i] = 1ll * Inv[i - 1] * invs[i] % MOD;
	}
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		G[x].emplace_back(y);G[y].emplace_back(x);
	}
	if (0&&n <= 10) bf :: work();
	else if (m + m <= n) algo1 :: work();
	else algo2 :: work();
	cout << ans << endl;
	return 0;
}
