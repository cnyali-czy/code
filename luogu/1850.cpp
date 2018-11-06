#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 2000 + 10, maxm = 2000 + 10, maxv = 300 + 5, maxe = 90000 + 10, inf = 1e9;

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

int n, m, v, e;
int c[maxn], d[maxn], dis[maxv][maxv];
double k[maxn], dp[maxn][maxn][2];

int main()
{
#ifdef CraZYali
	freopen("1850.in", "r", stdin);
	freopen("1850.out", "w", stdout);
#endif
	cin >> n >> m >> v >> e;
	REP(i, 1, n) c[i] = read<int>();
	REP(i, 1, n) d[i] = read<int>();
	REP(i, 1, n) scanf("%lf", k + i);
	REP(i, 1, v)
		REP(j, 1, v) dis[i][j] = (i == j ? 0 : inf);
	REP(i, 1, e)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		chkmin(dis[x][y], z);
		chkmin(dis[y][x], z);
	}
	REP(k, 1, v)
		REP(i, 1, v)
		REP(j, 1, v)
		chkmin(dis[i][j], dis[i][k] + dis[k][j]);
	REP(i, 1, n) REP(j, 0, m) dp[i][j][0] = dp[i][j][1] = inf;
	dp[1][0][0] = dp[1][1][1] = 0;
	REP(i, 2, n)
		REP(j, 0, m)
		{
			dp[i][j][0] = min(dp[i-1][j][1] + k[i-1] * dis[d[i-1]][c[i]] + (1 - k[i-1]) * dis[c[i-1]][c[i]], dp[i-1][j][0] + dis[c[i-1]][c[i]]);
			if (j) dp[i][j][1] = min(dp[i-1][j-1][1] + k[i-1] * k[i] * dis[d[i-1]][d[i]] + k[i-1] * (1-k[i]) * dis[d[i-1]][c[i]] + (1-k[i-1]) * k[i] * dis[c[i-1]][d[i]] + (1 - k[i-1]) * (1-k[i]) * dis[c[i-1]][c[i]], dp[i-1][j-1][0] + k[i]  * dis[c[i-1]][d[i]] + (1-k[i]) * dis[c[i-1]][c[i]]);
		}
	double ans = 1e20;
	REP(i, 0, m) REP(j, 0, 1) chkmin(ans, dp[n][i][j]);
	printf("%.2lf", ans);
	return 0;
}
