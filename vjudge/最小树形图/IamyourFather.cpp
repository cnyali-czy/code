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
const int maxn = 1000 + 10, maxm = 10000 + 10, inf = 1e9;

int m, n, k;

struct edge
{
	int u, v, w;
}e[maxm];

int in[maxn], pre[maxn], vis[maxn], id[maxn];

inline int solve(int root)
{
	register int ret = 0;
	while (1)
	{
		REP(i, 0, n - 1) in[i] = inf;
		REP(i, 1, m)
			if (e[i].u ^ e[i].v && in[e[i].v] > e[i].w)	in[e[i].v] = e[i].w, pre[e[i].v] = e[i].u;
		REP(i, 0, n - 1) if (i ^ root && in[i] == inf) return -1;
		in[root] = 0;
		REP(i, 0, n - 1) id[i] = vis[i] = -1;
		register int cnt = 0;
		REP(i, 0, n - 1)
		{
			register int v = i;
			ret += in[i];
			while (vis[v] ^ i && v ^ root && id[v] == -1) vis[v] = i, v = pre[v];
			if (id[v] == -1 && v ^ root)
			{
				for (register int u = pre[v]; u ^ v ; u = pre[u]) id[u] = cnt;
				id[v] = cnt++;
			}
		}
		if (!cnt) return ret;
		REP(i, 1, n) if (id[i] == -1) id[i] = cnt++;
		for (register int i = 1; i <= m;)
		{
			int v = e[i].v;
			e[i].u = id[e[i].u];
			e[i].v = id[e[i].v];
			if (e[i].u ^ e[i].v) e[i++].w -= in[v];
			else swap(e[i], e[--m]);
		}
		n = cnt;
		root = id[root];
	}
}

int main()
{
#ifdef CraZYali
	freopen("IamyourFather.in", "r", stdin);
	freopen("IamyourFather.out", "w", stdout);
#endif
	int T;
	cin >> T;
	while (T --> 0)
	{
		scanf("%d%d", &n, &m);
		REP(i, 1, m)
		{
			register int X, Y, Z;
			scanf("%d%d%d", &X, &Y, &Z);
			e[i] = (edge){X - 1, Y - 1, Z * -1000};
			if (e[i].v == n - 1) e[i].w += e[i].u;
		}
		int ans = -solve(0);
		printf("%d %d\n", (ans + 999) / 1000, (ans + 999) / 1000 * 1000 - ans + 1);
	}

	return 0;
}

