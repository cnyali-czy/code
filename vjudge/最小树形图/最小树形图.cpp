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
const int maxn = 100 + 5, maxV = maxn, maxE = maxn * maxn;
const double inf = 1e9;

int m, n, k;

double a[maxn];
int b[maxn];

struct edge
{
	int u, v;
	double w;
}e[maxE];

int V, E;
inline void add(int u, int v, double w) {e[++E] = (edge){u, v, w};}

double in[maxV];
int id[maxV], pre[maxV], vis[maxV];
inline double solve(int root)
{
	register double ret = 0;
	while (1)
	{
		REP(i, 1, V) in[i] = inf;
		REP(i, 1, E)
			if (e[i].u ^ e[i].v && e[i].w < in[e[i].v])
			{
				in[e[i].v] = e[i].w;
				pre[e[i].v] = e[i].u;
			}
		in[root] = 0;
		memset(vis, 0, sizeof(vis));
		memset(id, 0, sizeof(id));
		int cnt = 1;
		REP(i, 1, V)
		{
			ret += in[i];
			register int v = i;
			while (!id[v] && v ^ root && vis[v] ^ i) {vis[v] = i;v = pre[v];}
			if (v ^ root && !id[v])
			{
				for (register int u = pre[v]; u ^ v; u = pre[u]) id[u] = cnt;
				id[v] = ++cnt;
			}
		}
		if (!(--cnt)) return ret;
		
		REP(i, 1, V) if (!id[i]) id[i] = ++cnt;
		REP(i, 1, E)
		{
			int v = e[i].v;
			e[i].u = id[e[i].u];
			e[i].v = id[e[i].v];
			if (e[i].u ^ e[i].v) e[i].w -= in[v];
		}
		V = cnt;
		root = id[root];
	}
}

double cost[maxn];

int main()
{
#ifdef CraZYali
	freopen("最小树形图.in", "r", stdin);
	freopen("最小树形图.out", "w", stdout);
#endif
	memset(cost, 127 / 3, sizeof(cost));
	cin >> n;
	int root = n + 1;
	REP(i, 1, n) {scanf("%lf%d", a + i, b + i);if (!b[i]) continue;add(root, i, a[i]);cost[i] = a[i];}
	V = root;

	cin >> m;
	while (m--)
	{
		register int x, y;
		double z;
		scanf("%d%d%lf", &x, &y, &z);
		if (x <= n && y <= n)
		{
			add(x, y, z);
			chkmin(cost[y], z);
		}
	}
	double ans = solve(root);
	REP(i, 1, n) ans += b[i] * cost[i] - cost[i];
	printf("%.2lf\n", ans);
	return 0;
}
