#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 1500 + 10, maxm = maxn * maxn * 2, inf = 1e9;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int m, n, k;

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
	inline void clear() {for (register int i = 1; i <= n; i += 5) bg[i] = bg[i + 1] = bg[i + 2] = bg[i + 3] = bg[i + 4] = 0;e = 1;}
	inline void add(int x, int y, int z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
	
	bool vis[maxn];
	int dist[maxn];
	queue <int> q;
	inline void SPFA()
	{
		while (!q.empty()) q.pop();
		for (register int i = 1; i <= n ; i += 4) {vis[i] = vis[i + 1] = vis[i + 2] = vis[i + 3] = vis[i + 4] = 0;dist[i] = dist[i + 1] = dist[i + 2] = dist[i + 3] = dist[i + 4] = inf;}
		dist[n] = 0;
		q.push(n);
		while (!q.empty())
		{
			register int x = q.front();
			vis[x] = 0;
			q.pop();
			for (register int i = bg[x]; i ;i = ne[i])
				if (dist[to[i]] > dist[x] + w[i])
				{
					dist[to[i]] = dist[x] + w[i];
					if (!vis[to[i]])
					{
						vis[to[i]] = 1;
						q.push(to[i]);
					}
				}
		}
	}

	int dis[maxn];
	inline bool BFS()
	{
		while (!q.empty()) q.pop();
		REP(i, 1, n) dis[i] = -1;
		dis[1] = 0;
		q.push(1);
		while (!q.empty())
		{
			register int x = q.front();
			q.pop();
			for (register int i = bg[x]; i; i = ne[i])
				if (dis[to[i]] == -1 && w[i] > 0)
				{
					dis[to[i]] = dis[x] + 1;
					q.push(to[i]);
				}
		}
		return dis[n] != -1;
	}
	int cur[maxn];
	int dfs(int x, int y)
	{
		if (x == n || !y) return y;
		register int res(0);
		for (register int &i = cur[x]; i ; i = ne[i])
			if (dis[to[i]] == dis[x] + 1 && w[i] > 0)
			{
				register int temp = dfs(to[i], min(y, w[i]));
				if (temp > 0)
				{
					w[i] -= temp;
					w[i ^ 1] += temp;
					res += temp;
					y -= temp;
					if (!y) return res;
				}
			}
		return res;
	}
	inline int maxflow()
	{
		register int ans = 0;
		while (BFS()) {REP(i, 1, n) cur[i] = bg[i]; ans += dfs(1, inf);}
		return ans;
	}
}SPFA_G, DINIC_G;

int main()
{
#ifdef CraZYali
	freopen("war.in", "r", stdin);
	freopen("war.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		SPFA_G.clear();
		DINIC_G.clear();
		n = read<int>();
		while (1)
		{
			register int x, y, z;
			x = read<int>();y = read<int>();z = read<int>();
			if (!x && !y && !z) break;
			SPFA_G.add(x, y, z);
			SPFA_G.add(y, x, z);
		}
		if (n <= 1) {printf("0\n");continue;}
		SPFA_G.SPFA();
//		REP(i, 1, n) fprintf(stderr, "%d%c", SPFA_G.dist[i], i ^ n ? ' ' : '\n');
		REP(x, 1, n)
			for (register int i = SPFA_G.bg[x]; i ; i = SPFA_G.ne[i])
				if (SPFA_G.dist[SPFA_G.to[i]] == SPFA_G.dist[x] + SPFA_G.w[i])
				{
					DINIC_G.add(SPFA_G.to[i], x, 1);
					DINIC_G.add(x, SPFA_G.to[i], 0);
				}
		printf("%d\n", DINIC_G.maxflow());
	}

	return 0;
}
