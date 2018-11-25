#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5000 + 10;

template <typename T> T read()
{
	T ans = 0, p = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, k;
vector <int> G[maxn];

namespace tree
{
	void dfs(int x, int fa = -1)
	{
		printf("%d ", x);
		int siz = (int)G[x].size() - 1;
		REP(i, 0, siz) if (G[x][i] != fa) dfs(G[x][i], x);
	}
	void work()	{dfs(1);}
}

int X[maxn], Y[maxn], delx, dely;

int ans[maxn];bool hans;

bool vis[maxn];
int path[maxn], p;
void update()
{
	if (!hans)
	{
		hans = 1;
		REP(i, 1, n) ans[i] = path[i];
	}
	else
	{
		REP(i, 1, n)
			if (ans[i] < path[i]) return;
			else if (ans[i] > path[i]) break;
		REP(i, 1, n) ans[i] = path[i];
	}
}

void dfs(int x)
{
	if (vis[x]) return;
	vis[x] = 1;
	path[++p] = x;
	if (p == n) update();
	int siz = (int)G[x].size() - 1;
	REP(i, 0, siz)
		if (make_pair(delx, dely) == make_pair(x, G[x][i]) || make_pair(dely, delx) == make_pair(x, G[x][i])) continue;else 
			dfs(G[x][i]);
}

void work()
{
	REP(i, 1, m)
	{
		delx = X[i];dely = Y[i];
		p = 0;
		dfs(1);
		REP(j, 1, n)vis[j]=0;
	}
	REP(i, 1, n) printf("%d%c", ans[i] , i == n ? '\n' : ' ' );
}

int main()
{
#ifdef CraZYali
	freopen("5022.in", "r", stdin);
	freopen("5022.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, m)
	{
		register int x = read<int>(), y = read<int>();
		X[i] = x;Y[i] = y;
		G[x].push_back(y);G[y].push_back(x);
	}
	REP(i, 1, n) sort(G[i].begin(), G[i].end());
	if (m == n - 1) tree::work();
	else work();
	return 0;
}
