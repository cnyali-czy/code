#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5000 + 10, maxm = 50000 + 10, inf = 1e9;

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

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, S, T;

int dis[maxn], pre[maxn], Max[maxn];bool vis[maxn];
queue <int> q;

bool spfa()
{
	REP(i, 1, n) vis[i] = 0, dis[i] = inf;
	dis[S] = 0;Max[S] = inf;q.push(S);
	while (!q.empty())
	{
		register int x = q.front();vis[x] = 0;q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] > dis[x] + cost[i])
			{
				dis[to[i]] = dis[x] + cost[i];
				Max[to[i]] = min(Max[x], w[i]);
				pre[to[i]] = i;
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
void update()
{
	max_flow += Max[T];
	min_cost += Max[T] * dis[T];
	register int x = T;
	while (x ^ S)
	{
		w[pre[x]] -= Max[T];
		w[pre[x] ^ 1] += Max[T];
		x = to[pre[x] ^ 1];
	}
}

int main()
{
#ifdef CraZYali
	freopen("3381-new.in", "r", stdin);
	freopen("3381-new.out", "w", stdout);
#endif
	cin >> n >> m >> S >> T;
	while (m --> 0)
	{
		register int x, y, z, c;
		x = read<int>();y = read<int>();z = read<int>();c = read<int>();
		add(x, y, z, c);
		add(y, x, 0, -c);
	}
	while (spfa()) update();
	cout << max_flow <<  ' ' << min_cost << endl;
	return 0;
}
