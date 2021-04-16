#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long 

using namespace std;
const int maxn = 1e5 + 10, inf = 1e9, MOD = 998244353;

int bg[maxn], ne[maxn], to[maxn], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int n, m, u[20], v[20], t;
vector <int> G[maxn];
int f[maxn][2], g[maxn][2];
int dfn[maxn], dfs_clock;

bool have[maxn];
void dfs0(int x, int fa = 0)
{
	dfn[x] = ++dfs_clock;
	for (int y : G[x]) if (y ^ fa)
		if (!dfn[y])
		{
			add(x, y);
			dfs0(y, x);
		}
		else if (dfn[y] < dfn[x])
		{
			++t;
			u[t] = y;
			v[t] = x;
		}
}
int qd[maxn];
void dfs(int x)
{
	if (!have[x])
	{
		f[x][0] = g[x][0];
		f[x][1] = g[x][1];
		return;
	}
	i64 f0 = 1, f1 = 1;
	if (qd[x] ==  1) f0 = 0;
	if (qd[x] == -1) f1 = 0;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs(to[i]);
		f0 *= (f[to[i]][0] + f[to[i]][1]);if (f0 >= MOD) f0 %= MOD;
		f1 *= f[to[i]][0];if (f1 >= MOD) f1 %= MOD;
	}
	f[x][0] = f0;f[x][1] = f1;
}

int back[maxn];
void dfs1(int x)
{
	back[++dfs_clock] = x;
	g[x][0] = g[x][1] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs1(to[i]);have[x] |= have[to[i]];
		g[x][0] = 1ll * g[x][0] * (g[to[i]][0] + g[to[i]][1]) % MOD;
		g[x][1] = 1ll * g[x][1] * g[to[i]][0] % MOD;
	}
}

int main()
{
#ifdef CraZYali
	freopen("4426.in", "r", stdin);
	freopen("4426.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		int x, y;scanf("%d%d", &x, &y);
		G[x].emplace_back(y);G[y].emplace_back(x);
	}
	dfs0(1);
	REP(i, 1, t) have[u[i]] = have[v[i]] = 1;
	dfs_clock = 0;dfs1(1);

	i64 ans = 0;
	static int fk[50];
	REP(i, 1, t) fk[i] = u[i];
	sort(fk + 1, fk + 1 + t);int tt = unique(fk + 1, fk + 1 + t) - fk - 1;
	
	REP(i, 0, (1 << tt) - 1)
	{
		REP(j, 1, t) qd[v[j]] = 0;
		REP(j, 1, tt)
			if (i >> (j - 1) & 1) qd[fk[j]] = 1;
			else qd[fk[j]] = -1;
		REP(j, 1, t) if (qd[u[j]] == 1)
		{
			if (qd[v[j]] == 1) goto gg;
			qd[v[j]] = -1;
		}
		DEP(c, n, 1)
		{
			int x = back[c];
			if (!have[x])
			{
				f[x][0] = g[x][0];
				f[x][1] = g[x][1];
				continue;
			}
			i64 f0 = 1, f1 = 1;
			if (qd[x] ==  1) f0 = 0;
			if (qd[x] == -1) f1 = 0;
			for (int i = bg[x]; i; i = ne[i])
			{
				f0 *= (f[to[i]][0] + f[to[i]][1]);if (f0 >= MOD) f0 %= MOD;
				f1 *= f[to[i]][0];if (f1 >= MOD) f1 %= MOD;
			}
			f[x][0] = f0;f[x][1] = f1;
		}
		//		dfs(1);
		ans += f[1][0] + f[1][1];
gg:;
	}
	cout << ans % MOD << endl;
	return 0;
}
