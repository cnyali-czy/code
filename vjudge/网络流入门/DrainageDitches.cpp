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
const int maxn = 200 + 10, maxm = 200 + 10, inf = (((1 << 30) - 1) << 1) + 1;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z) 
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int m, n, k;

int dis[maxn];
queue <int> q;
inline bool BFS()
{
	memset(dis, -1, sizeof(dis));
	dis[1] = 0;
	q.push(1);
	while (!q.empty())
	{
		register int x = q.front();
		q.pop();
		for (register int i = bg[x]; i ; i = ne[i])
			if (w[i] > 0 && dis[to[i]] == -1)
			{
				dis[to[i]] = dis[x] + 1;
				q.push(to[i]);
			}
	}
	return dis[n] != -1;
}

int dfs(int x = 1, int y = inf)
{
	if (x == n || !y) return y;
	for (register int i = bg[x] ; i ; i = ne[i])
		if (dis[to[i]] == dis[x] + 1 && w[i] > 0)
		{
			register int temp = dfs(to[i], min(y, w[i]));
			if (temp > 0)
			{
				w[i] -= temp;
				w[i ^ 1] += temp;
				return temp;
			}
		}
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("DrainageDitches.in", "r", stdin);
	freopen("DrainageDitches.out", "w", stdout);
#endif
	while (scanf("%d%d", &m, &n) != EOF)
	{
		e = 1;
		memset(bg, 0, sizeof(bg));
		
		while (m --> 0)
		{
			register int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z);add(y, x, 0);
		}
		register int ans = 0 ;
		while (BFS()) ans += dfs();
		printf("%d\n", ans);
	}

	return 0;
}

