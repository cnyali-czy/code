#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;
const int maxn = 20, maxm = maxn * (maxn - 1) / 2,  inf = 1e9;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

int G[maxn][maxn];
unsigned int seed = 1;

int ans = inf;

int depth[maxn];
bool vis[maxn];

struct Edge
{
	int u, v;
	Edge() {}Edge(int _u, int _v) : u(_u), v(_v){}
	int cost() {return depth[u] * G[u][v];}
	bool operator < (Edge B) const {return  depth[u] * G[u][v] > B.cost();}
};
int n, m;
__gnu_pbds::priority_queue <Edge> q;
Edge past[1000];

void SA(int root)
{
	while (!q.empty()) q.pop();
	REP(i, 1, n) depth[i] = vis[i] = 0;
	depth[root] = vis[root] = 1;
	int now = 0, res = 0;
	for (register int i = bg[root]; i ; i = ne[i])
		q.push(Edge(root, to[i]));
	REP(I, 2, n)
	{
		Edge E = q.top();q.pop();
		while (!q.empty() && (vis[E.v] || (rand() % 1000) % (n) == 0))
		{
			if (!vis[E.v]) past[++now] = E;
			E = q.top();q.pop();
		}
		vis[E.v] = 1;
		depth[E.v] = depth[E.u] + 1;
		REP(i, 1, now) q.push(past[i]);
		now = 0;
		for (register int i = bg[E.v]; i ; i = ne[i])
			if (!vis[to[i]]) q.push(Edge(E.v, to[i]));
		res += E.cost();
	}
	chkmin(ans, res);
}

int main()
{
#ifdef CraZYali
	freopen("3959.in", "r", stdin);
	freopen("3959.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) REP(j, 1, n) G[i][j] = inf;
	while (m --> 0)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		chkmin(G[x][y], z);chkmin(G[y][x], z);
		seed *= x * y * z ^ (x ^ y ^ z);
	}
	REP(i, 1, n)
		REP(j, 1, n)
		if (G[i][j] != inf) add(i, j, G[i][j]);
	srand(seed);
	REP(j,1,10000)
		REP(i, 1, n) SA(i);

	cout << ans;
	return 0;
}
