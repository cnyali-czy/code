#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5000 + 10, maxm = 50000 + 10, inf((((1 << 30) - 1) << 1) + 1);
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
int m, n, k, S, T;

queue <int> q;
bool vis[maxn];
int dis[maxn], Max[maxn], pre[maxn], pre_id[maxn];

inline bool spfa()
{
	REP(i, 1, n) dis[i] = inf;
	dis[S] = 0;
	memset(vis, 0, sizeof(vis));
	while (!q.empty()) q.pop();
	Max[S] = inf;
	q.push(S);
	
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		vis[x] = 0;
		for (register int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] > dis[x] + cost[i])
			{
				dis[to[i]] = dis[x] + cost[i];
				pre[to[i]] = x;
				pre_id[to[i]] = i;
				Max[to[i]] = min(Max[x], w[i]);
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					q.push(to[i]);
				}
			}
	}
	return dis[T] != inf;
}

int max_flow, min_cost;

inline void update()
{
	int x = T;
	while (x ^ S)
	{
		w[pre_id[x]] -= Max[T];
		w[pre_id[x] ^ 1] += Max[T];
		x = to[pre_id[x] ^ 1];
	}
	max_flow += Max[T];
	min_cost += dis[T] * Max[T];
}

int main()
{
#ifdef CraZYali
	freopen("3381.in", "r", stdin);
	freopen("3381.out", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin >> n >> m >> S >> T;
	while (m --> 0)
	{
		int x, y, z, c;
		cin >> x >> y >> z >> c;
		add(x, y, z, c);
		add(y, x, 0, -c);
	}
	while (spfa()) update();
	cout << max_flow << ' ' << min_cost;
	return 0;
}
