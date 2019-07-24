#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10, maxm = maxn;

int bg[maxn], ne[maxn], to[maxn], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, m, rt, val[maxn];

int depth[maxn], grand[maxn][20];
int lca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, 19, 0) if(depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	DREP(i, 19, 0) if (grand[x][i] ^ grand[y][i]) x = grand[x][i], y = grand[y][i];
	return grand[x][0];
}

bool vis[100000 + 10];
int v[maxn], p;

void dfs(int x)
{
	if (!vis[val[x]]) vis[v[++p] = val[x]] = 1;
	for (int i = bg[x]; i ; i = ne[i]) dfs(to[i]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	depth[1] = 1;
	cin >> m >> val[1];
	while (m--)
	{
		int opt;scanf("%d", &opt);
		if (opt == 1)
		{
			int x;scanf("%d", &x);scanf("%d%d", val + x, &grand[x][0]);
			REP(i, 1, 19) grand[x][i] = grand[grand[x][i-1]][i-1];
			depth[x] = depth[grand[x][0]] + 1;
			add(grand[x][0], x);
		}
		else if (opt == 2)
		{
			int a, b;scanf("%d%d", &a, &b);int c = lca(a, b);
			p = 0;
			while (a ^ c) {if (!vis[val[a]]) vis[v[++p] = val[a]] = 1; a = grand[a][0];};
			while (b ^ c) {if (!vis[val[b]]) vis[v[++p] = val[b]] = 1; b = grand[b][0];};
			if (!vis[val[c]]) vis[v[++p] = val[c]] = 1;
			double bar(0), res(0);
			REP(i, 1, p) bar += v[i];bar /= p;
			REP(i, 1, p) res += (v[i] - bar) * (v[i] - bar);
			res /= p;
			printf("%.8lf\n", res);
			REP(i, 1, p) vis[v[i]] = 0;
		}
		else if (opt == 3)
		{
			int a;scanf("%d", &a);
			p = 0;
			dfs(a);
			double bar(0), res(0);
			REP(i, 1, p) bar += v[i];bar /= p;
			REP(i, 1, p) res += (v[i] - bar) * (v[i] - bar);
			res /= p;
			printf("%.8lf\n", res);
			REP(i, 1, p) vis[v[i]] = 0;
		}
	}
	return 0;
}
