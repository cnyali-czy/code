#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#define  REP(i, s, e) for(register int i = s ; i <= e ; i++)
#define DREP(i, s, e) for(register int i = s ; i >= e ; i--)

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxV = 1000 + 10, maxE = 1000000 + 10, N = 60, M = 6000, inf = 0x3f3f3f;

struct Edge
{
	int u, v, dis;
	Edge() {}
	Edge(int u, int v, int dis): u(u), v(v), dis(dis) {}
}edges[maxE];

struct Graph
{
	int n, m;
	int vis[maxV], pre[maxV], id[maxV], in[maxV];

	inline void init(int n)
	{
		this -> n = n;
		m = 0;
	}

	inline void add(int u, int v, int dis) {edges[m++] = Edge(u, v, dis);}

	inline int sovle(int root)
	{
		int ans = 0;
		while (1)
		{
			REP(i, 0, n - 1) in[i] = inf;

			REP(i, 0, m - 1)
				if (edges[i].dis < in[edges[i].v] && edges[i].u ^ edges[i].v)
				{
					in[edges[i].v] = edges[i].dis;
					pre[edges[i].v] = edges[i].u;
				}

			REP(i, 0, n - 1) if (i ^ root && in[i] == inf) return -1;

			register int cnt = 0;
			memset(id, -1, sizeof(id));
			memset(vis, -1, sizeof(vis));
			in[root] = 0;

			REP(i, 0, n - 1)
			{
				ans += in[i];
				int v = i;
				while (vis[v] ^ i && id[v] == -1 && v ^ root) {	vis[v] = i;	v = pre[v];	}
				if (v != root && id[v] == -1)
				{
					for (register int u = pre[v]; u != v; u = pre[u]) id[u] = cnt;
					id[v] = cnt++;
				}
			}
			if (cnt == 0) return ans;

			REP(i, 0, n - 1) if (id[i] == -1) id[i] = cnt++;

			REP(i, 0, m - 1)
			{
				int v = edges[i].v;
				edges[i].v = id[edges[i].v];
				edges[i].u = id[edges[i].u];
				if (edges[i].u != edges[i].v) edges[i].dis -= in[v];
			}
			n = cnt;
			root = id[root];
		}
	}
}G;

int n, m;
int level[N], TEMPID[N];
int dis[M][M];

void init()
{
	TEMPID[0] = 0;
	REP(i, 1, n)
	{
		scanf("%d", level + i);
		level[i]++;
		if (i == 1) TEMPID[i] = level[i];
		else TEMPID[i] = TEMPID[i - 1] + level[i];
	}

	G.init(TEMPID[n + 1] = TEMPID[n] + 1);
	G.add(0, 1, 0);
	REP(i, 1, n)
		G.add(0, TEMPID[i - 1] + 1, 0);

	REP(i, 1, n)
		DREP(j, level[i] - 1, 1)
			G.add(j + 1 + TEMPID[i - 1], j + TEMPID[i - 1], 0);

	memset(dis, 0x3f3f3f, sizeof(dis));
	register int c, l1, d, l2, money;
	REP(i, 1, m)
	{
		scanf("%d%d%d%d%d", &c, &l1, &d, &l2, &money);
		REP(u, TEMPID[c - 1] + 1 + l1, TEMPID[c]) chkmin(dis[u][TEMPID[d - 1] + l2 + 1], money);
	}
	REP(i, 1, TEMPID[n + 1] - 1)
		REP(j, 1, TEMPID[n + 1] - 1) if (dis[i][j] ^ inf) G.add(i, j, dis[i][j]);
	printf("%d\n", G.sovle(0));
}

int main()
{
#ifdef CraZYali
	freopen("GGS-DDU.in", "r", stdin);
	freopen("GGS-DDU.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) * n * m) init();
	return 0;
}
