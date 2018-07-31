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
const int maxn = 100000 + 10, maxm = 200000 + 10, inf = 2147483647;

int bg[maxn], ne[maxm], to[maxm], w[maxm], e;

inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int m, n, s;

int dist[maxn];

struct node
{
	int x, dis;
	node(int _x, int _dis) : x(_x), dis(_dis) {}
	bool operator < (node B) const {return dis > B.dis;}
};
priority_queue <node> q;

int main()
{
#ifdef CraZYali
	freopen("4779.in", "r", stdin);
	freopen("4779.out", "w", stdout);
#endif
	cin >> n >> m >> s;
	while (m--)
	{
		register int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z);
	}
	
	REP(i, 1, n) dist[i] = inf;
	dist[s] = 0;
	q.push(node(s, 0));
	while (!q.empty())
	{
		register node now = q.top();
		q.pop();
		int x = now.x;
		int dis = now.dis;
		if (dis > dist[x]) continue;
		for (register int i = bg[x]; i ; i = ne[i])
			if (dist[to[i]] > dis + w[i]) q.push(node(to[i], dist[to[i]] = dis + w[i]));
	}

	REP(i, 1, n) printf("%d ", dist[i]);
	return 0;
}
