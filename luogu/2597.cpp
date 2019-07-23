#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
const int maxn = 70000 + 10, maxm = maxn;

int bg[maxn], ne[maxn], to[maxn], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, k, depth[maxn], grand[maxn][20], LOG;
int tcnt;
vector <int> G[maxn], eat[maxn];
int in[maxn], q[maxn], head, tail;

int lca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0)
		if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	DREP(i, LOG, 0)
		if (grand[x][i] ^ grand[y][i]) x = grand[x][i], y = grand[y][i];
	return grand[x][0];
}
int ans[maxn];
void dfs(int x)
{
	ans[x] = 1;
	for (int i = bg[x]; i ;i = ne[i])
	{
		dfs(to[i]);
		ans[x] += ans[to[i]];
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("2597.in", "r", stdin);
	freopen("2597.out", "w", stdout);
#endif
	cin >> n;LOG = log2(n);
	REP(i, 1, n) while (scanf("%d", &k), k) G[k].push_back(i), in[i]++, eat[i].push_back(k);
	REP(i, 1, n)
		if (!in[i]) depth[q[++tail] = i] = 1;
	while (head <= tail)
	{
		int x = q[head++];
		int siz = (int)G[x].size()-1;
		REP(i, 0, siz)
			if (!(--in[G[x][i]])) q[++tail] = G[x][i];
		if (!eat[x].empty())
		{
			siz = (int)eat[x].size() - 1;
			int l = eat[x][0];
			REP(i, 1, siz) l = lca(l, eat[x][i]);
			grand[x][0] = l;
			depth[x] = depth[l] + 1;
			REP(j, 1, LOG) grand[x][j] = grand[grand[x][j-1]][j-1];
			add(l, x);
		}
	}
	REP(i, 1, n) if(!ans[i])dfs(i);
	REP(i, 1, n) printf("%d\n", ans[i] - 1);
	return 0;
}
