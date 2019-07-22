#define REP(i, s, e) for (int i = s; i <= e ;i++)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 4000 + 10, maxm = 60000 + 10, inf = 2e9;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int m, n, S, T;
int q[maxn], head, tail, dis[maxn];
bool bfs()
{
	REP(i, 1, n) dis[i] = -1;
	dis[q[head = tail = 1] = S] = 0;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i ; i = ne[i])
			if (w[i] && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
	}
	return dis[T] != -1;
}
int dfs(int x, int y)
{
	if (x == T || !y) return y;
	int res(0);
	for (int i = bg[x]; i ; i = ne[i])
		if (dis[to[i]] == dis[x] + 1 && w[i])
		{
			int temp = dfs(to[i], min(y, w[i]));
			if (temp)
			{
				res += temp;
				y -= temp;
				w[i] -= temp;
				w[i ^ 1] += temp;
				if (!y) break;
			}
		}
	return res;
}
int dfn[maxn], low[maxn], dfs_clock, cnt, belong[maxn], s[maxn], top;
bool vis[maxn];
void tarjan(int u)
{
	dfn[u] = low[u] = ++dfs_clock;
	vis[u] = 1;s[++top] = u;
	for (int i = bg[u]; i ; i = ne[i])
		if (w[i])
			if (!dfn[to[i]])
			{
				tarjan(to[i]);
				chkmin(low[u], low[to[i]]);
			}
			else if (vis[to[i]]) chkmin(low[u], low[to[i]]);
	if (dfn[u] == low[u])
	{
		cnt++;
		while (1)
		{
			int x = s[top--];
			belong[x] = cnt;
			vis[x] = 0;
			if (x == u) break;
		}
	}
}
int ans[maxm][2];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4126.in", "r", stdin);
	freopen("4126.out", "w", stdout);
#endif
	cin >> n >> m >> S >> T;
	REP(i, 1, m)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);add(y, x, 0);
	}
	while (bfs()) dfs(S, inf);
	REP(i, 1, n) if (!dfn[i]) tarjan(i);
	REP(x, 1, n)
		for (int i = bg[x]; i ; i = ne[i])
			if (!(i & 1) && !w[i]) ans[i>>1][0] = belong[x] != belong[to[i]], ans[i>>1][1] = belong[x] == belong[S] && belong[to[i]] == belong[T];
	REP(i, 1, m) printf("%d %d\n", ans[i][0], ans[i][1]);
	return 0;
}
