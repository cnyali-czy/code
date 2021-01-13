#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10, maxm = 5e5 + 10, maxN = maxn + maxm;

int read()
{
	int res = 0;
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	while (isdigit(c)) res = res * 10 + (c - 48), c = getchar();
	return res;
}

int n, m, q;
vector <int> T[maxN], H[maxN];

int lg_table[1 << 10];
struct __init__
{
	__init__()
	{
		REP(i, 2, 1023) lg_table[i] = lg_table[i >> 1] + 1;
	}
}__INIT__;
int _log(int x)
{
	if (x >> 10) return 10 + lg_table[x >> 10];
	return lg_table[x];
}

namespace LCA
{
	int dep[maxN], dfn[maxN], dfs_clock, st[20][maxN], cir[maxN], fa[maxN];
	int Min(int x, int y) {return dep[x] < dep[y] ? x : y;}
	void dfs(int x, int f = 0)
	{
		fa[x] = f;
		dep[x] = dep[f] + 1;
		cir[x] = cir[f] + (x <= n);
		st[0][dfs_clock] = Min(st[0][dfs_clock], x);
		st[0][dfn[x] = ++dfs_clock] = x;
		for (int y : T[x]) if (y ^ f)
		{
			dfs(y, x);
			st[0][dfs_clock] = Min(st[0][dfs_clock], x);
		}
	}
	void init()
	{
		dfs(1);
		REP(j, 1, 19)
			REP(i, 1, dfs_clock - (1 << j) + 1)
			st[j][i] = Min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
	}
	int lca(int x, int y)
	{
		if (x == y) return x;
		int l = dfn[x], r = dfn[y];
		if (l > r) swap(l, r);
		r--;int k = _log(r - l + 1);
		return Min(st[k][l], st[k][r - (1 << k) + 1]);
	}
}
using LCA :: lca;
using LCA :: fa;
using LCA :: cir;

bool cmp(int x, int y) {return LCA :: dfn[x] < LCA :: dfn[y];}
i64 cnt[maxN], f[maxN];
int build_vtree(vector <int> v)
{
	sort(v.begin(), v.end(), cmp);
	REP(i, 0, (int)v.size() - 2) v.emplace_back(lca(v[i], v[i + 1]));
	sort(v.begin(), v.end(), cmp);
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for (auto i : v) H[i].clear(), cnt[i] = f[i] = 0;
	REP(i, 0, (int)v.size() - 2)
	{
		int fa = lca(v[i], v[i + 1]);
		H[fa].emplace_back(v[i + 1]);
	}
	return v[0];
}

int dfn[maxn], low[maxn], dfs_clock, N;
vector <int> G[maxn];
void tarjan(int u, int fa = 0)
{
	static int stk[maxn], top;
	stk[++top] = u;
	dfn[u] = low[u] = ++dfs_clock;
	for (int v : G[u])// if (v ^ fa)
		if (!dfn[v])
		{
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] == dfn[u])
			{
				++N;
				stk[++top] = u;
				while (1)
				{
					int x = stk[top--];
					T[N].emplace_back(x);
					T[x].emplace_back(N);
					if (x == v) break;
				}
			}
		}
		else low[u] = min(low[u], dfn[v]);
}

void dfs(int u)
{
	for (int v : H[u])
	{
		dfs(v);
		cnt[u] += cnt[v];
		f[u] += f[v] + cnt[v] * (cir[v] - cir[u]);
	}
}
i64 ans, k;
void solve(int u, int vfa = 0)
{
	if (u <= n)
		ans = min(ans, f[u]);
	else if (cir[fa[u]] > cir[fa[vfa]])
		ans = min(ans, f[u] - (k - cnt[u]));
	for (int v : H[u])
	{
		f[v] = f[u];
		f[v] -= cnt[v] * (cir[v] - cir[u]);
		f[v] += (cir[fa[v]] - cir[fa[u]]) * (k - cnt[v]);
		if (u > n && cir[u] < cir[v]) ans = min(ans, f[u] - cnt[v]);
		solve(v, u);
	}
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	N = n = read();m = read();q = read();
	REP(i, 1, m)
	{
		int x = read(), y = read();
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	tarjan(1);
	LCA :: init();
	while (q--)
	{
		k = read();
		vector <int> v(k);
		REP(i, 0, k - 1) v[i] = read();
		int rt = build_vtree(v);
		for (auto i : v) cnt[i]++;
		dfs(rt);
		ans = 1e18;
		solve(rt);
		printf("%lld\n", (n - 1ll) * k - ans);
	}
	return 0;
}
