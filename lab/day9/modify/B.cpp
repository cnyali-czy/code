//modify std
//still learning

#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1e5 + 10, inf = 1<<30;

namespace dinic
{
	const int maxn = 4e6 + 10, maxm = 3e7 + 100;
	int bg[maxn], ne[maxm], to[maxm], w[maxm], e = 1;
	int S, T, dis[maxn], q[maxn], head, tail;
	int cur[maxn];
	void add(int x, int y, int z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
	void link(int a, int b, int c) {add(a, b, c);add(b, a, 0);}
	bool bfs()
	{
		REP(i, S, T) dis[i] = -1;
		dis[q[head = tail = 1] = T] = 0;
		while (head <= tail)
		{
			int x = q[head++];
			for (int i = bg[x]; i ;i = ne[i])
				if (w[i ^ 1] && dis[to[i]] == -1) dis[q[++tail] = to[i]] = dis[x] + 1;
		}
		return dis[S] != -1;
	}
	int dfs(int x, int y = inf)
	{
		if (x == T || !y) return y;
		int res = 0;
		for (int &i = cur[x]; i ; i = ne[i])
			if (w[i] && dis[to[i]] == dis[x] - 1)
			{
				int temp = dfs(to[i], min(y, w[i]));
				if (temp > 0)
				{
					res += temp;
					y -= temp;
					w[i] -= temp;
					w[i ^ 1] += temp;
					if (!y) break;
				}
			}
		return res;
	}
	void output()
	{
		REP(x, S, T)
			for (int i = bg[x];i;i=ne[i])printf("%d %d %d\n",x,to[i],w[i]);
	}
	int work()
	{
		int ans = 0;
		while (bfs())
		{
			REP(i, S, T) cur[i] = bg[i];
			ans += dfs(S);
		}
		return ans;
	}
}

int n, B, W, ans, LOG;
int dfn[maxn], dfs_clock, grand[maxn][20], depth[maxn];
namespace tree
{
	int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
	void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	void dfs(int x)
	{
		dfn[x] = ++dfs_clock;
		REP(i, 1, LOG) grand[x][i] = grand[grand[x][i-1]][i-1];
		for (int i = bg[x]; i ; i = ne[i])
			if (to[i] ^ grand[x][0])
			{
				grand[to[i]][0] = x;
				depth[to[i]] = depth[x] + 1;
				dfs(to[i]);
			}
	}
	void init()
	{
		LOG = log2(n);
		depth[1] = 1;
		dfs(1);
	}
	int lca(int x, int y)
	{
		if (x == y) return x;
		if (dfn[x] > dfn[y]) swap(x, y);
		DREP(i, LOG, 0)
			if (dfn[grand[y][i]] > dfn[x]) y = grand[y][i];
		return grand[y][0];
	}
}
using tree::add;
using tree::lca;
using dinic::link;
int L[maxn][20], R[maxn][20];
vector <pair <int, int> > E;
int cur;
void getl(int k, int t)
{
	if (!L[k][t])
	{
		L[k][t] = ++cur;
		getl(k, t - 1);
		getl(grand[k][t-1], t-1);
		link(L[k][t], L[k][t-1], inf);
		link(L[k][t], L[grand[k][t-1]][t-1], inf);
	}
}
int jump(int k, int d)
{
	REP(i, 0, LOG)
		if (d & (1 << i)) k = grand[k][i];
	return k;
}
void getr(int k, int t)
{
	if (!R[k][t])
	{
		R[k][t] = ++cur;
		getr(k, t - 1);
		getr(grand[k][t-1], t-1);
		link(R[k][t-1], R[k][t], inf);
		link(R[grand[k][t-1]][t-1], R[k][t], inf);
	}
}
void linkl(int k,int a,int c)
{
	if (a==c) return;
	int t;
	for (t=0;(1<<(t+1))<depth[a]-depth[c];t++);
	getl(a, t);
	link(k, L[a][t], inf);
	a = jump(a, depth[a]-depth[c]-(1<<t));
	getl(a, t);
	link(k, L[a][t], inf);
}
void linkr(int k,int a,int c)
{
	if (a==c) return;
	int t;
	for (t=0;(1<<(t+1))<depth[a]-depth[c];t++);
	getr(a, t);
	link(R[a][t], k, inf);
	a = jump(a, depth[a]-depth[c]-(1<<t));
	getr(a, t);
	link(R[a][t], k, inf);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
#endif
	cin >> n >> B >> W;ans = n;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	tree::init();
	REP(i, 1, n)
	{
		L[i][0] = R[i][0] = ++cur;
		link(0, cur, 1);
	}
	while (B--)
	{
		int x, y, z, v;
		scanf("%d%d%d", &x, &y, &v);z = lca(x, y);
		++cur; ans += v;
		link(0, cur, v);
		linkl(cur, x, grand[z][0]);
		linkl(cur, y, z);
	}
	while (W--)
	{
		int x, y, z, v;
		scanf("%d%d%d", &x, &y, &v);z = lca(x, y);
		++cur; ans += v;
		E.push_back(make_pair(cur, v));
		linkr(cur, x, grand[z][0]);
		linkr(cur, y, z);
	}
	dinic::T = ++cur;
	int siz = (int)E.size() - 1;
	REP(i, 0, siz) link(E[i].first, cur, E[i].second);
	REP(i, 1, n) link(i, cur, 1);
	cout << ans - dinic::work() << endl;
	return 0;
}
