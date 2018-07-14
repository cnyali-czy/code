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
const int maxn = 50 + 5, maxm = 2000 + 10, maxa = 500 + 10, maxV = maxn * maxa, maxE = maxV + maxm << 1, inf = 1e9;

int m, n, k;

int a[maxn];

int fakeid[maxn][maxa];

int V, E;

struct edge
{
	int u, v, w;
}e[maxE];

inline void add(int x, int y, int z) {e[++E] = (edge){x, y, z};}

int id[maxV], pre[maxV], vis[maxV], in[maxV];

inline int solve(int root)
{
	register int ret = 0;
	while (1)
	{
		REP(i, 1, V) in[i] = inf;
		REP(i, 1, E) if (e[i].u ^ e[i].v && in[e[i].v] > e[i].w) {in[e[i].v] = e[i].w;pre[e[i].v] = e[i].u;}
		in[root] = 0;
		REP(i, 1, V) if (in[i] == inf) return -1;

		register int cnt = 1;
		REP(i, 1, V) id[i] = vis[i] = 0;
		REP(i, 1, V)
		{
			ret += in[i];
			register int v = i;
			while (v ^ root && !id[v] && vis[v] ^ i) {vis[v] = i;v = pre[v];}
			if (v ^ root && !id[v])
			{
				for (register int u = pre[v]; u ^ v; u = pre[u]) id[u] = cnt;
				id[v] = cnt++;
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

int main()
{
#ifdef CraZYali
	freopen("GGS-DDU.in", "r", stdin);
	freopen("GGS-DDU.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) * n * m)
	{
		register int cnt = 0;
		REP(i, 1, n)
		{
			scanf("%d", a + i);
			REP(j, 0, a[i]) fakeid[i][j] = ++cnt;
		}
		int root = cnt + 1;
		V = cnt + 1;
		E = 0;
		REP(i, 1, n) add(root, fakeid[i][0], 0);
		REP(i, 1, n)
			REP(j, 1, a[i]) add(fakeid[i][j], fakeid[i][j - 1], 0);
		while (m --> 0)
		{
			register int c, l1, d, l2, money;
			scanf("%d%d%d%d%d", &c, &l1, &d, &l2, &money);
			add(fakeid[c][l1], fakeid[d][l2], money);
		}
		int ans = solve(root);
		printf("%d\n", ans);
	}

	return 0;
}
