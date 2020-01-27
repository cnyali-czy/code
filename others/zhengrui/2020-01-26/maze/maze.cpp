/*
 * File Name:	maze.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.26 09:21
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <vector>
#include "maze.h"
#include <cstring>

using namespace std;
const int maxn = 200 + 5, maxm = maxn * maxn, inf = 1e9;

int n, G[maxn][maxn], t[maxn][maxn], e[maxn][maxn], deg[maxn], frm[maxn];

int dfs(int fa)
{
	int cur = get_label();
	if (cur > 1)
	{
		move(get_coming_edge());
		return -cur;
	}
	set_label(2);
	int u = n++;
	deg[u] = get_edge_number();
	frm[u] = get_coming_edge();
	REP(i, 1, deg[u])
		if (i == frm[u])
		{
			t[u][i] = fa;
			e[u][i] = fa;
		}
		else
		{
			move(i);
			if ((t[u][i] = dfs(u)) >= 0) e[u][i] = t[u][i];
		}
	set_label(3);
	if (u) move(frm[u]);
	return u;
}
int bin;
void mark(int u, int fa = -1)	
{
	set_label(u / bin % 3 + 1);
	REP(i, 1, deg[u]) if (t[u][i] >= 0 && i ^ frm[u])
	{
		move(i);
		mark(t[u][i], u);
	}
	REP(i, 1, deg[u])
		if (t[u][i] == -2)
		{
			move(i);
			e[u][i] += bin * (get_label() - 1);
			move(get_coming_edge());
		}
	if (u) move(frm[u]);
}

vector <int> solve(int k, int lim)
{
	dfs(-1);
	for (bin = 1; bin < n; bin *= 3) mark(0);
	REP(i, 0, 200)
		REP(j, 0, 200) G[i][j] = inf;
	vector <int> ans(n, 0);
	REP(i, 0, n - 1) G[i][i] = 0;
	REP(i, 0, n - 1)
		REP(j, 1, deg[i]) if (t[i][j] != -3)
		{
			int to = e[i][j];
			G[i][to] = G[to][i] = 1;
		}
	REP(k, 0, n - 1)
		REP(i, 0, n - 1) if (G[i][k] < inf)
		REP(j, 0, n - 1) if (G[k][j] < inf)
		chkmin(G[i][j], G[i][k] + G[k][j]);
	REP(i, 0, n - 1)
		REP(j, i + 1, n - 1) if (G[i][j] < inf)
		ans[G[i][j]-1]++;
	return ans;
}

#ifdef CraZYali
#include "maze.h"

#include <iostream>
#include <cassert>
int _K, _L, _current_node, _move_count;
int _edge[705][705], _label[705], _coming_edge = -1;
std::vector<int> _adj[705];
int get_edge_number() { return _adj[_current_node].size(); }
int get_coming_edge() { return _coming_edge; }
int get_label() { return _label[_current_node] + 1; }
void set_label(int x)
{
	assert(x > 0 && x <= _K);
	_label[_current_node] = x - 1;
}
void move(int e)
{
	assert(++_move_count <= _L);
	assert(e > 0 && e <= get_edge_number());
	int v = _adj[_current_node][e - 1];
	_coming_edge = _edge[v][_current_node];
	_current_node = v;
}
int gg[maxn][maxn], rans[maxn];
int main()
{
	freopen("maze.in", "r", stdin);
	freopen("maze.out", "w", stdout);
	int n, m;
	std::cin >> n >> m >> _K >> _L;
	memset(gg,0x3f,sizeof gg);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		std::cin >> u >> v;
		gg[u][v] = gg[v][u] = 1;
		u--;
		v--;
		_adj[u].push_back(v);
		_adj[v].push_back(u);
		_edge[u][v] = _adj[u].size();
		_edge[v][u] = _adj[v].size();
	}
	REP(k,1,n)
		REP(i,1,n)if(gg[i][k]<=n)
		REP(j,1,n)if(gg[k][j]<=n)
		chkmin(gg[i][j],gg[i][k]+gg[k][j]);
	FILE *Stdout=fopen("std.out","w");
	REP(i,1,n)
		REP(j,i+1,n)if(gg[i][j]<=n)
		rans[gg[i][j]]++;
	REP(i,1,n)fprintf(Stdout, "%d%c", rans[i],i==n?'\n':' ');
	std::cin >> _current_node;
	_current_node--;
	auto ans = solve(_K, _L);
	//	std::cout << _move_count << std::endl;
	for (int i = 0; i < ans.size(); i++)
		std::cout << ans[i] << " \n"[i + 1 == ans.size()];
	return 0;
}
#endif
