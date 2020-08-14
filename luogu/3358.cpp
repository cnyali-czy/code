/*
	Problem:	3358.cpp
	Time:		2020-08-12 16:52
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 500 + 10, inf = 1e9;

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

namespace Graph
{
	const int maxn = ::maxn << 1, maxm = 114514;
	int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], cost[maxm << 1], e = 1;
	inline void add(int x, int y, int z, int c)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
		cost[e] = c;
	}
	inline void Add(int x, int y, int z, int c)
	{
		add(x, y, z, c);
		add(y, x, 0, -c);
	}
	queue <int> q;
	int dis[maxn], N, S, T, Max[maxn], pre[maxn];
	bool vis[maxn];
	bool spfa()
	{
		REP(i, 1, N) dis[i] = -inf, Max[i] = 0;
		dis[S] = 0;
		Max[S] = inf;
		q.push(S);
		while (!q.empty())
		{
			int x = q.front();q.pop();
			vis[x] = 0;
			for (int i = bg[x]; i; i = ne[i]) if (w[i] > 0 && dis[to[i]] < dis[x] + cost[i])
			{
				dis[to[i]] = dis[x] + cost[i];
				pre[to[i]] = i;
				Max[to[i]] = min(Max[x], w[i]);
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(to[i]);
				}
			}
		}
		return Max[T] > 0;
	}
	int max_cost;
	void update()
	{
		int x = T;
		max_cost += dis[T] * Max[T];
		while (x ^ S)
		{
			w[pre[x]] -= Max[T];
			w[pre[x] ^ 1] += Max[T];
			x = to[pre[x] ^ 1];
		}
	}
	void work() {while (spfa()) update();}
}

int n, k, l[maxn], r[maxn], len[maxn], b[maxn << 1], m;

int main()
{
#ifdef CraZYali
	file("3358");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n)
	{
		b[++m] = (l[i] = read<int>()) + 1;
		b[++m] = r[i] = read<int>();
		len[i] = r[i] - l[i];
	}
	sort(b + 1, b + 1 + m);
	m = unique(b + 1, b + 1 + m) - b - 1;
	Graph :: S = m + 1;
	Graph :: T = m;
	Graph :: N = m;
	Graph :: Add(Graph :: S, 1, k, 0);
	REP(i, 1, m - 1) Graph :: Add(i, i + 1, inf, 0);
	REP(i, 1, n)
	{
		int L = lower_bound(b + 1, b + 1 + m, l[i] + 1) - b;
		int R = lower_bound(b + 1, b + 1 + m, r[i]) - b;
		Graph :: Add(L, R, 1, len[i]);
	}
	Graph :: work();
	cout << Graph :: max_cost << endl;
	return 0;
}
