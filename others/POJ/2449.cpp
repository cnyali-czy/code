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
const int maxn = 1000 + 10, maxm = 100000 + 10;

struct Graph
{
	int bg[maxn], ne[maxm], to[maxm], w[maxm], e;
	void init(int n)
	{
		REP(i, 1, n) bg[i] = 0;
		e = 0;
	}
	inline void add(int x, int y, int z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
}G1, G2;

int m, n, k, S, T;

priority_queue <pair<int, int> > q;
int dis[maxn];

void dij()
{
	REP(i, 1, n) dis[i] = 1e9;
	q.push(make_pair(dis[T] = 0, T));
	while (!q.empty())
	{
		register int x = q.top().second;
		register int dist = -q.top().first;
		q.pop();
		if (dist > dis[x]) continue;
		else for (register int i = G2.bg[x]; i ; i = G2.ne[i])
			if (dis[G2.to[i]] > dist + G2.w[i]) q.push(make_pair(-(dis[G2.to[i]] = dist + G2.w[i]), G2.to[i]));
	}
}

struct node
{
	int x, g, h;

	node(int _x, int _g, int _h): x(_x), g(_g), h(_h){}

	bool operator < (node B) const {return g + h > B.g + B.h;}
};

priority_queue <node> Q;

int times[maxn];

int kth(int S, int T)
{
	dij();
	REP(i, 1, n) times[i] = 0;
	while (!Q.empty()) Q.pop();
	Q.push(node(S, 0, dis[S]));
	while (!Q.empty())
	{
		register int x = Q.top().x;
		register int g = Q.top().g;
		register int h = Q.top().h;
		Q.pop();
		times[x]++;
		if (times[x] == k && x == T) return g + h;
		else if (times[x] <= k)
			for (register int i = G1.bg[x]; i ;i = G1.ne[i])
				Q.push(node(G1.to[i], g + G1.w[i], dis[G1.to[i]]));
	}
	return -1;
}
int main()
{
#ifdef CraZYali
	freopen("2449.in", "r", stdin);
	freopen("2449.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) != EOF)
	{
		G1.init(n);G2.init(n);
		while (m --> 0)
		{
			register int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			G1.add(x, y, z);
			G2.add(y, x, z);
		}
		scanf("%d%d%d", &S, &T, &k);
		if (S == T) ++k;
		printf("%d\n", kth(S, T));
	}

	return 0;
}
