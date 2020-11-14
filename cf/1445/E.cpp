/*
	Problem:	E.cpp
	Time:		2020-11-01 20:20
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <map>
#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10;

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

vector <int> G[maxn], preG[maxn], tochk[maxn], dog[maxn];
inline void add(int x, int y)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}
int n, m, k, b[maxn], u[maxn], v[maxn];

int col[maxn];

int cur;
map <pair <int, int> , int> Id;
int gg[maxn], flag;
void dfs(int u)
{
	if (!flag) return;
	for (int v : G[u])
	{
		if (!col[v])
		{
			col[v] = 3 - col[u];
			dfs(v);
		}
		else if (col[u] + col[v] != 3) flag = 0;
		if (!flag) return;
	}
}

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}

int main()
{
#ifdef CraZYali
	file("E");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, n)
	{
		b[i] = read<int>();
		dog[b[i]].emplace_back(i);
	}
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, m)
	{
		int x = read<int>(), y = read<int>();
		if (b[x] > b[y]) swap(x, y);
		u[i] = x;v[i] = y;
		if (b[x] == b[y]) preG[b[x]].emplace_back(i);
		else
		{
			auto ljf = make_pair(b[x], b[y]);
			if (!Id[ljf]) Id[ljf] = ++cur;
			tochk[Id[ljf]].emplace_back(i);
		}
	}
	int K = k;
	REP(i, 1, k) for (auto j : preG[i]) add(u[j], v[j]), uni(u[j], v[j]);
	REP(i, 1, n) if (!col[i] && !gg[b[i]])
	{
		flag = 1;
		col[i] = 1;
		dfs(i);
		if (!flag)
		{
			K--;
			gg[b[i]] = 1;
		}
	}

	i64 ans = K * (K - 1ll) / 2;
	for (auto I : Id)
	{
		int b1 = I.first.first, b2 = I.first.second;
		if (gg[b1] || gg[b2]) continue;
		map <int, int> ccc;
		for (auto i : tochk[I.second])
		{
			int a = col[u[i]], b = col[v[i]];
			int fu = find(u[i]), fv = find(v[i]);
			auto pzk = make_pair(find(u[i]), find(v[i]));
			if (ccc.find(fu) == ccc.end()) ccc[fu] = 1;
			if (ccc.find(fv) == ccc.end())
			{
				if (a == b) ccc[fv] = 3 - ccc[fv];
				else ccc[fv] = ccc[fu];
			}
			else
			{
				if ((ccc[fu] == ccc[fv]) != (a == b))
				{
					ans--;
					goto gg;
				}
			}
		}
gg:;
	}
	cout << ans << endl;
	return 0;
}
