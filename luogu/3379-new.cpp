#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 500000 + 10, maxm = 500000 + 10;

vector <int> G[maxn];
vector <pair <int, int> > qry[maxn];

inline void add_edge(int x, int y)
{
	G[x].push_back(y);
	G[y].push_back(x);
}
inline void add_query(int x, int y, int i)
{
	qry[x].push_back(make_pair(y, i));
	qry[y].push_back(make_pair(x, i));
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

int fa[maxn];
int find(int x) {return x == fa[x] ? fa[x] : fa[x] = find(fa[x]);}
inline void uni(int x, int y)
{
	fa[find(x)] = find(y);
}

bool vis[maxn];

int ans[maxm];
void dfs(int u)
{
	vis[u] = 1;
	for (int v : G[u]) if (!vis[v])
	{
		dfs(v);
		fa[find(v)] = find(u);
	}
	for (auto qaq : qry[u]) if (vis[qaq.first])
		ans[qaq.second] = find(qaq.first);
}

int main()
{
#ifdef CraZYali
	file("3379-new");
#endif
	int root, n, m;
	cin >> n >> m >> root;
	REP(i, 1, n) fa[i] = i;
	REP(i, 2, n) add_edge(read<int>(), read<int>());
	REP(i, 1, m) add_query(read<int>(), read<int>(), i);
	dfs(root);
	REP(i, 1, m) printf("%d\n", ans[i]);
	return 0;
}
