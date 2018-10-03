#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 6000 + 10, maxm = maxn << 1;
int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int m, n, k;
int dp[maxn][2];

void dfs(int x, int fa = -1)
{
	dp[x][0] = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs(to[i], x);
			dp[x][0] += max(dp[to[i]][0], dp[to[i]][1]);
			dp[x][1] += dp[to[i]][0];
		}
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF)
	{
		e = 1;
		REP(i, 1, n) bg[i] = 0;
		REP(i, 1, n) scanf("%d", &dp[i][1]);
		REP(i, 1, n)
		{
			register int x, y;
			scanf("%d%d", &x, &y);
			if (i ^ n) add(x, y);add(y, x);
		}
		dfs(1);

		printf("%d\n", max(dp[1][0], dp[1][1]));
	}
	return 0;
}
