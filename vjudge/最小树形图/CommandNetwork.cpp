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
const int maxn = 100 + 5, maxm = 1e4 + 10, inf = 1e9;

double x[maxn], y[maxn];
#define dist(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

struct edeg
{
	int u, v;
	double dis;
}e[maxm];

int pre[maxn], id[maxn], vis[maxn];
int m, n, k;

double in[maxn];

inline double sovle(int root)
{
	double ret = 0;
	while (1)
	{
		REP(i, 1, n) in[i] = inf;
		REP(i, 1, m)
			if (e[i].dis < in[e[i].v] && e[i].u ^ e[i].v)
			{
				in[e[i].v] = e[i].dis;
				pre[e[i].v] = e[i].u;
			}
		REP(i, 1, n) if (i ^ root && in[i] == inf) return -1;
		register int cnt = 1;
		memset(id, 0, sizeof(id));
		memset(vis, 0, sizeof(vis));
		in[root] = 0;
		REP(i, 1, n)
		{
			register int v = i;
			ret += in[v];
			while (vis[v] ^ i && !id[v] && v ^ root)
			{
				vis[v] = i;
				v = pre[v];
			}
			if (!id[v] && v ^ root)
			{
				for (register int u = pre[v]; u != v; u = pre[u]) id[u] = cnt;
				id[v] = cnt++;
			}
		}
		if (!(--cnt)) break;
		REP(i, 1, n) if (!id[i]) id[i] = ++cnt;
		REP(i, 1, m)
		{
			int u = e[i].u;
			int v = e[i].v;
			e[i].u = id[u];
			e[i].v = id[v];
			if (e[i].u ^ e[i].v) e[i].dis -= in[v];
		}
		n = cnt;
		root = id[root];
	}
	return ret;
}

int main()
{
#ifdef CraZYali
	freopen("CommandNetwork.in", "r", stdin);
	freopen("CommandNetwork.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) != EOF)
	{
		REP(i, 1, n) scanf("%lf%lf", x + i, y + i);
		REP(i, 1, m)
		{
			scanf("%d%d", &e[i].u, &e[i].v);
			if (e[i].u ^ e[i].v) e[i].dis = dist(x[e[i].u], y[e[i].u], x[e[i].v], y[e[i].v]);
			else e[i].dis = inf;
		}
		double ans = sovle(1);
		if (ans == -1) printf("poor snoopy\n");
		else printf("%.2f\n", ans);
	}

	return 0;
}
