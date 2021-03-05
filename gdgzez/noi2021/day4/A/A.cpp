/*
	Problem:	A.cpp
	Time:		2021-03-04 09:13
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <unordered_map>
#include <set>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 3e5 + 10;

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

int n, m, u[maxn], v[maxn];
vector <int> G[maxn], T[maxn], U[maxn];

int dfn[maxn], low[maxn], dfs_clock, siz[maxn], dep[maxn], anc[20][maxn], mi[20][maxn];
int c[maxn];
void dfs1(int u)
{
	dfn[u] = low[u] = ++dfs_clock;
	siz[u] = 1;

	int cnt = 0, fk = 0;
	for (int v : G[u])
		if (!dfn[v])
		{
			T[u].emplace_back(v);
			dep[v] = dep[anc[0][v] = u] + 1;

			dfs1(v);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) cnt++, fk = v;
			siz[u] += siz[v];
		}
		else if (dfn[v] < dfn[u])
		{
			U[u].emplace_back(v);
			low[u] = min(low[u], dfn[v]);
		}
	if (cnt > 1) c[u] = -1;
	else if (cnt == 1) c[u] = fk;
//	cout << u << ' ' << dfn[u] << ' ' << low[u] << ' ' << c[u] << ' ' << siz[u] << endl;
}

namespace SMT
{
	const int maxN = 1e7;
	int ls[maxN], rs[maxN], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	void ins(int &p, int l, int r, int pos)
	{
		if (!p) p = ++cur;
		if (l == r) return;
		if (pos <= mid) ins(lson, pos);
		else ins(rson, pos);
	}
	void merge(int &x, int y)
	{
		if (!x || !y) return void(x |= y);
		merge(ls[x], ls[y]);
		merge(rs[x], rs[y]);
	}
	bool query(int p, int l, int r, int L, int R)
	{
		if (!p) return 0;
		if (L <= l && r <= R) return 1;
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) || query(rson, L, R);
	}
}
unordered_map <int, int> E[maxn];
bool ans[maxn];
#define cs return void(ans[E[u][v]] = 1)
int rt[maxn];

int jump(int u, int v)
{
	if (anc[0][u] == v) return 0;
	int res = n;
	DEP(i, 18, 0) if (dep[anc[i][u]] > dep[v])
	{
		res = min(res, mi[i][u]);
		u = anc[i][u];
	}
	return res;
}

void check(int u, int v)
{
	int w = u;
	DEP(i, 18, 0) if (dep[anc[i][w]] > dep[v]) w = anc[i][w];
	if (v == 1)
	{
		if (T[v].size() > 2) cs;
		if (T[v].size() > 1) if (siz[u] > 1 || anc[0][u] != v) cs;
		if (anc[0][u] == v)
		{
			if (T[u].size() > 1) cs;
			return;
		}
	}
	else
	{
		if (c[v] == -1) cs;
		if (c[v] && c[v] != w) cs;
	}
	bool flg = 0;
	if (v == 1) flg = 1;
	else if (jump(u, v) < dfn[v]) flg = 1;
	for (int w : T[u])
	{
		auto res1 = (1 <= dfn[v] - 1 ? SMT :: query(rt[w], 1, n, 1, dfn[v] - 1) : 0);
		auto res2 = (dfn[v] + 1 <= dfn[u] - 1 ? SMT :: query(rt[w], 1, n, dfn[v] + 1, dfn[u] - 1) : 0);
		if (res1 == res2)
		{
			if (!res1) cs;
			flg = 1;
		}
	}
	if (!flg) cs;
}


void dfs2(int u)
{
	REP(j, 1, 18) mi[j][u] = min(mi[j - 1][u], mi[j - 1][anc[j - 1][u]]);
	int res = n;
	for (int f : U[u]) res = min(res, dfn[f]);
	multiset <int> ssr;
	ssr.emplace(res);
	for (int v : T[u]) ssr.emplace(low[v]);
	auto it = ssr.begin();
	for (int v : T[u])
	{
		auto ti = it;
		if (*ti == low[v]) ti++;
		mi[0][v] = *ti;
		dfs2(v);
	}
	for (int f : U[u]) check(u, f);
	for (int v : T[u]) SMT :: merge(rt[u], rt[v]);
	for (int v : U[u]) SMT :: ins(rt[u], 1, n, dfn[v]);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		u[i] = read<int>();v[i] = read<int>();
		G[u[i]].emplace_back(v[i]);G[v[i]].emplace_back(u[i]);
		E[u[i]][v[i]] = E[v[i]][u[i]] = i;
	}
	dep[1] = 1;dfs1(1);
	REP(j, 1, 18) REP(i, 1, n) anc[j][i] = anc[j - 1][anc[j - 1][i]];

	dfs2(1);
	REP(i, 1, m) putchar(ans[i] + 48);
	return 0;
}
