#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;
const int maxn = 1000 + 10, inf = 1e9, S(1), T(2);

int m, n, k;
int dis[maxn], depth[maxn], dp[maxn];

priority_queue <pair<int, int> > q;

int bg[maxn], *ne, *to, *w, e;

inline void add(int x, int y, int z = 0)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

inline void init()
{
	ne = new int[10 + (m << 1)];
	to = new int[10 + (m << 1)];
	w = new int[10 + (m << 1)];
	e = 1;
	REP(i, 1, n) bg[i] = 0;
}

inline void clean()
{
	delete(ne);
	delete(to);
	delete(w);
}

inline void dij()
{
	while (!q.empty()) q.pop();
	REP(i, 1, n) dis[i] = inf;
	dis[T] = 0;
	q.push(make_pair(0, T));
	while (!q.empty())
	{
		register int x = q.top().second;
		register int dist = -q.top().first;
		q.pop();
		if (dist > dis[x]) continue;
		for (register int i = bg[x]; i ; i = ne[i])
			if (dis[to[i]] > dist + w[i]) q.push(make_pair(-(dis[to[i]] = dist + w[i]), to[i]));
	}
}

void dfs(int x = S)
{
	if (dp[x]) return;
	for (register int i = bg[x]; i ; i = ne[i])
		if (dis[to[i]] < dis[x])
		{
			dfs(to[i]);
			dp[x] += dp[to[i]];
		}
	if (x == T) dp[x] = 1;
}

int main()
{
#ifdef CraZYali
	freopen("10917.in", "r", stdin);
	freopen("10917.out", "w", stdout);
#endif
	while (scanf("%d %d", &n, &m) == 2)
	{
		init();
		while (m --> 0)
		{
			register int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z);
			add(y, x, z);
		}
		dij();
		REP(i, 1, n) dp[i] = 0;
		dfs();
		printf("%d\n", dp[S]);
		clean();
	}
	
	return 0;
}
