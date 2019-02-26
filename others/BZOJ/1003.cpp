#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
const int maxn = 20 + 5, maxm = 100 + 5, maxe = maxn * maxn, inf = 1e8;

int bg[maxn], ne[maxe << 1], to[maxe << 1], w[maxe << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

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

//days, nodes, cost-once, edges
int m, n, K, E;

bool vis[maxn], cannot[maxn][maxm];int dist[maxn];
struct node
{
	int x, dis;
	node(int _x, int _dis) : x(_x), dis(_dis){}
	bool operator < (node B) const {return dis > B.dis;}
};
__gnu_pbds :: priority_queue <node> q;
int cost[maxm][maxm];

bool ok(int x, int s, int e)
{
	REP(i, s, e)
		if (cannot[x][i]) return 0;
	return 1;
}

void dij(int s, int e)
{
	REP(i, 1, n) vis[i] = 0, dist[i] = inf;
	q.push(node(1, dist[1] = 0));
	while (!q.empty())
	{
		int x(q.top().x), dis(q.top().dis);q.pop();
		if (vis[x]) continue;
		vis[x] = 1;
		for (int i = bg[x]; i ; i = ne[i])
			if (ok(to[i], s, e)  && !vis[to[i]] && dist[to[i]] > dis + w[i]) q.push(node(to[i], dist[to[i]] = dis + w[i]));
	}
	cost[s][e] = (dist[n] == inf ? inf : dist[n] * (e - s + 1));
}

int dp[maxm];

int main()
{
#ifdef CraZYali
	freopen("1003.in", "r", stdin);
	freopen("1003.out", "w", stdout);
#endif
	cin >> m >> n >> K >> E;
	while (E --> 0)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	int d(read<int>());
	while (d --> 0)
	{
		int P(read<int>()), a(read<int>()), b(read<int>());
		REP(i, a, b) cannot[P][i] = 1;
	}
	REP(i, 1, m)
		REP(j, i, m) dij(i, j);
	REP(i, 1, m)
	{
		dp[i] = cost[1][i];
		REP(j, 2, i)
			chkmin(dp[i], dp[j - 1] + cost[j][i] + K);
	}
	cout << dp[m] << endl;
	return 0;
}
