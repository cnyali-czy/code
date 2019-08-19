#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
const int maxnn = 1000 + 10, maxS = 1 << 11, maxn = 10000 + 10, inf = 1e9;

int bg[maxn], ne[maxn], to[maxn], w[maxn], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}
inline void link(int x, int y, int z) {add(x, y, z);add(y, x, z);}

int n, m, k, t, belong[maxn], sum;
int dis[maxnn][maxS],  dp[maxS], cnt[maxn];
int col[maxn][13], num[maxn], vis[maxn];
queue <int> p;

void spfa(int sta)
{
	while (!p.empty())
	{
		int x(p.front());
		p.pop();
		for (int i = bg[x]; i ; i = ne[i])
			if (dis[to[i]][sta] > dis[x][sta] + w[i])
			{
				dis[to[i]][sta] = dis[x][sta] + w[i];
				if (!vis[to[i]])
				{
					vis[to[i]] = 1;
					p.push(to[i]);
				}
			}
		vis[x] = 0;
	}
}

inline bool check(int sta)
{
	memset(cnt,0,sizeof(cnt));
	REP(i, 0, t)
		if (sta&(1<<i))  cnt[belong[i]]++;
	REP(i, 0, sum)
		if (cnt[i] ^ col[i][0] && cnt[i])  return 0;
	return 1;
}
int main()
{
#ifdef CraZYali
	freopen("3264.in", "r", stdin);
	freopen("3264.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	while (m--)
	{
		int x, y, z;
		scanf("%d%d%d",&x, &y, &z);
		link(x, y, z);
	}
	t = -1;
	memset(num, -1, sizeof(num));
	while (k--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		chkmax(sum, (belong[num[col[x][++col[x][0]] = y] = ++t] = x));
	}
	REP(i, 1, n)
		REP(j, 0, (1 << t+1) - 1) dis[i][j] = inf;
	REP(i, 1, n) if (num[i] != -1) dis[i][1 << num[i]]=0;
	REP(sta, 1, (1<<t+1) - 1)
	{
		REP(i, 1, n)
		{
			for (int s = sta & (sta-1); s ;s = sta & (s-1)) chkmin(dis[i][sta], dis[i][sta-s] + dis[i][s]);
			if (dis[i][sta] != inf) p.push(i), vis[i]=1;
		}
		spfa(sta);
	}
	REP(sta, 1, (1<<t+1) - 1)
	{
		dp[sta] = dis[1][sta];
		REP(i, 2, n) chkmin(dp[sta], dis[i][sta]);
	}
	REP(sta, 0, (1<<t+1) - 1)
		if (check(sta))
			for (int s = sta & (sta-1); s ;s = sta & (s-1)) 
				if (check(s)) chkmin(dp[sta], dp[sta^s] + dp[s]);
	cout << dp[(1<<t+1) - 1] << endl;
	return 0;
}
