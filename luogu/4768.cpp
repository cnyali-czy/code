#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>

using namespace std;
const int maxn = 400000 + 10, maxm = 400000 + 10, inf = 1e9;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, N, lastans, q, k, s;
struct Edge
{
	int u, v, l, a;
	Edge() {}
	Edge(int _u, int _v, int _l, int _a) : u(_u), v(_v), l(_l), a(_a) {}
}E[maxm];
bool cmp(Edge A, Edge B) {return A.a > B.a;}

int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

int grand[maxn][20], Min[maxn][20], LOG;

bool vis[maxn];
int d[maxn];
struct node
{
	int x, dist;
	node(){}
	node(int _x, int _dist) : x(_x), dist(_dist) {}
	bool operator < (node B) const {return dist > B.dist;}
};
priority_queue <node> Q;

int main()
{
#ifdef CraZYali
	file("4768");
#endif
	int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) bg[i] = 0;e = 0;
		REP(i, 1, m)
		{
			int u(read<int>()), v(read<int>()), l(read<int>()), a(read<int>());
			E[i] = Edge(u, v, l, a);
			add(u, v, l);add(v, u, l);
		}
		sort(E + 1, E + 1 + m, cmp);
		N = n;
		REP(i, 1, n * 2) fa[i] = i;
		REP(i, 1, m)
		{
			int u = find(E[i].u), v = find(E[i].v);
			if (u ^ v)
			{
				fa[u] = fa[v] = grand[u][0] = grand[v][0] = ++N;
				Min[u][0] = Min[v][0] = E[i].a;
			}
		}
		LOG = log2(N);
		REP(j, 1, LOG)
			REP(i, 1, N)
			{
				grand[i][j] = grand[grand[i][j-1]][j-1];
				Min[i][j] = min(Min[i][j-1], Min[grand[i][j-1]][j-1]);
			}
		REP(i, 1, n) vis[i] = 0;
		REP(i, 1, N) d[i] = inf;
		Q.push(node(1, d[1] = 0));
		while (!Q.empty())
		{
			int x = Q.top().x, dist = Q.top().dist;
			Q.pop();
			if (vis[x]) continue;
			vis[x] = 1;
			for (int i = bg[x] ; i ; i = ne[i])
				if (!vis[to[i]] && d[to[i]] > d[x] + w[i]) Q.push(node(to[i], d[to[i]] = dist + w[i]));
		}
		REP(i, 1, N-1) chkmin(d[grand[i][0]], d[i]);
		lastans = 0;
		q = read<int>();k = read<int>(); s = read<int>();
		while (q--)
		{
			int v0(read<int>()), p0(read<int>());
			int v = (v0 + k * lastans - 1) % n + 1, p = (p0 + k * lastans) % (s + 1);
			DREP(i, LOG, 0)
				if (grand[v][i] && Min[v][i] > p) v = grand[v][i];
			printf("%d\n", lastans = d[v]);
		}
	}
	return 0;
}
