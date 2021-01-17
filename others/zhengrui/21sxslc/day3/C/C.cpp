/*
	Problem:	C.cpp
	Time:		2021-01-17 09:56
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <vector>
#include <cstring>
#include <cassert>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 55, inf = 1e8;

vector <int> G[maxn];

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

int n, A[maxn << 1], u[maxn], v[maxn], ans;
int fa[maxn];

void dfs0(int x)
{
	for (int y : G[x]) if (y ^ fa[x])
	{
		fa[y] = x;
		dfs0(y);
	}
}

bool vis[maxn], Vis[maxn];
void mark_subtree(int x)
{
	vis[x] = 1;
	for (int y : G[x]) if (y ^ fa[x]) mark_subtree(y);
}
int f[maxn][maxn];

struct Edge
{
	int u, v, w;
	Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {}
};
vector <Edge> vec;

namespace Graph
{
	const int maxn = 1e5;
	int bg[maxn], ne[maxn], to[maxn], w[maxn], e, cost[maxn], s, t;
	void add(int x, int y, int z, int c)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
		cost[e] = c;
	}
	void Add(int x, int y, int z, int c)
	{
		add(x, y, z, c);add(y, x, 0, -c);
	}
	void clear()
	{
		e = 1;
		REP(i, 1, n + 2) bg[i] = 0;
		s = n + 1;t = n + 2;
	}
	int ans;
	int Max[maxn], dis[maxn], pre[maxn];
	bool vis[maxn];
	bool spfa()
	{
		queue <int> q;
		REP(i, 1, t) vis[i] = 0, dis[i] = inf;
		while (!q.empty()) q.pop();
		dis[s] = 0;Max[s] = inf;
		q.emplace(s);
		while (q.size())
		{
			int x = q.front();q.pop();
			vis[x] = 0;
			for (int i = bg[x]; i; i = ne[i]) if (w[i] > 0 && dis[to[i]] > dis[x] + cost[i])
			{
				dis[to[i]] = dis[x] + cost[i];
				pre[to[i]] = i;
				Max[to[i]] = min(Max[x], w[i]);
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.emplace(to[i]);
				}
			}
		}
		return dis[t] < inf;
	}
	void update()
	{
		int x = t;
		while (x ^ s)
		{
			w[pre[x]] -= Max[t];
			w[pre[x] ^ 1] += Max[t];
			x = to[pre[x] ^ 1];
		}
		ans += dis[t] * Max[t];
	}
	int solve()
	{
		clear();
		REP(i, 1, n)
			if (Vis[i])	Add(s, i, 1, 0);
			else Add(i, t, 1, 0);
		for (auto E : vec) Add(E.u, E.v, 1, -E.w);
		ans = 0;
		while (spfa()) update();
		return -ans;
	}
}
int S, T;

vector <int> P;

void dfs2(int x, int t, int fa = 0)
{
	for (int y : G[x]) if (y ^ fa && !Vis[y]) dfs2(y, t, x);
	vec.clear();
	for (auto i : P) for (int y : G[x]) if (y ^ fa && !Vis[y])
		vec.emplace_back(i, y, f[i][y]);
	f[t][x] = 1 + Graph :: solve();
}

void dfs3(int x, int fa = 0)
{
	vector <int> tP;
	for (int y : G[x]) if (y ^ fa && Vis[y]) dfs3(y, x), tP.emplace_back(y);
	P = tP;
	dfs2(T, x);
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	while (scanf("%d", A + 1 + n) != EOF) n++;
	n = n / 2 + 1;
	REP(i, 1, n - 1) u[i] = A[i] + 1;
	REP(i, n, n * 2 - 2) v[i - n + 1] = A[i] + 1;
	REP(i, 1, n - 1) G[u[i]].emplace_back(v[i]), G[v[i]].emplace_back(u[i]);
	dfs0(1);
	int ans = 0;
	REP(i, 2, n)
	{
		REP(j, 1, n) vis[j] = 0;
		mark_subtree(i);
		REP(j, 1, n) Vis[j] = vis[j];
		REP(j, 1, n) if (!vis[j])
		{
			S = i;T = j;
			dfs3(i);
			ans = max(ans, f[S][T]);
		}
	}
	cout << ans << endl;
	return 0;
}
