#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <vector>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
const int maxn = 2000 + 5, maxm = 2000 + 5, maxk = 2000 + 5;
const long long inf = 1e15;

int n, m, k;
int a[maxn];
long long dp[maxk][maxn];

struct node
{
	int x;
	long long dist;
	inline bool operator < (const node &B) const {return dist > B.dist;}
};
#include<queue>
__gnu_pbds :: priority_queue <node> q;
bool vis[maxn];

struct Graph
{
	vector <pair <int, long long> > G[maxn];
	long long dis[maxn][maxn];
	inline void init()
	{
		REP(i, 1, n)
			REP(j, 1, n) dis[i][j] = inf;
		REP(i, 1, n) dis[i][i] = 0;
	}
	inline void add(int x, int y, long long z)
	{
		G[x].push_back(make_pair(y, z));
		G[y].push_back(make_pair(x, z));
	}
	inline void calc()
	{
		REP(start, 1, n)
		{
			REP(i, 1, n) vis[i] = 0;
			q.push(node{start, 0});
			while (!q.empty())
			{
				int x(q.top().x);
				long long dist(q.top().dist);
				q.pop();
				if (vis[x]) continue;
				vis[x] = 1;
				for (register auto i : G[x])
					if (dis[start][i.first] > dist + i.second && !vis[i.first])
					{
						dis[start][i.first] = dist + i.second;
						q.push(node{i.first, dis[start][i.first]});
					}
			}
		}
	}
}bike, foot;

long long dis[maxn];

int main()
{
#ifdef CraZYali
	freopen("bicycle.in", "r", stdin);
	freopen("bicycle.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	REP(i, 1, k) scanf("%d", a + i);
	a[++k] = 1;
	bike.init();
	foot.init();
	while (m--)
	{
		int u, v, p, q;
		scanf("%d%d%d%d", &u, &v, &p, &q);
		bike.add(u, v, p);
		foot.add(u, v, q);
	}
	bike.calc();
	foot.calc();
	REP(i, 1, k)
		REP(j, 1, n) dp[i][j] = inf;
	REP(i, 1, n) dp[0][i] = bike.dis[1][i] + foot.dis[i][1];
	a[0] = 1;
	REP(i, 0, k-1)
	{
		REP(j, 1, n) dis[j] = inf;
		REP(j, 1, n) if (dp[i][j] < inf)
		{
			dis[j] = dp[i][j] + foot.dis[a[i]][j];
			q.push(node{j, dis[j]});
			chkmin(dp[i+1][j], dp[i][j] + foot.dis[a[i]][a[i+1]]);
		}
		REP(j, 1, n) vis[j] = 0;
		while (!q.empty())
		{
			int x(q.top().x);
			long long dist(q.top().dist);
			q.pop();
			if (vis[x]) continue;
			vis[x] = 1;
			for (register auto i : bike.G[x])
				if (dis[i.first] > dist + i.second && !vis[i.first])
				{
					dis[i.first] = dist + i.second;
					q.push(node{i.first, dis[i.first]});
				}
		}
		REP(j, 1, n) chkmin(dp[i+1][j], dis[j] + foot.dis[j][a[i+1]]);
	}
	cout << dp[k][1] << endl;
	return 0;
}
