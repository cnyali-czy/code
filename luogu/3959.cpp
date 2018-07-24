#define REP(i, s, e) for (register int i = s; i <= e ;  i++)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 15, inf = 1e9;

int n, m, k;

int G[maxn][maxn];

int dp[1 << maxn], dis[maxn], ans(inf);
inline void dfs(int now)
{
	REP(i, 1, n)
		if ((1 << (i - 1)) & now)
			REP(j, 1, n)
				if (((1 << (j - 1)) & now) == 0 && G[i][j] ^ inf)
				{
					register int nxt = now | (1 << (j - 1));
					if (dp[nxt] > dp[now] + dis[i] * G[i][j])
					{
						register int temp = dis[j];
						dis[j] = dis[i] + 1;
						dp[nxt] = dp[now] + dis[i] * G[i][j];
						dfs(nxt);
						dis[j] = temp;
					}
				}
}
int main()
{
#ifdef CraZYali
	freopen("3959.in", "r", stdin);
	freopen("3959.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
		REP(j, 1, n)
			G[i][j] = inf;
	
	while (m --> 0)
	{
		register int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		chkmin(G[x][y], z);
		chkmin(G[y][x], z);
	}

	register int Final = (1 << n) - 1;

	REP(S, 1, n)
	{
		REP(i, 1, n) dis[i] = inf;
		REP(i, 0, Final) dp[i] = inf;
		dp[1 << (S - 1)] = 0;
		dis[S] = 1;
		
		dfs(1 << (S - 1));
		chkmin(ans, dp[Final]);
	} 
	cout << ans;
	return 0;
}
