#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 10000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int m, n, k;

int dp[maxn][3];

void dfs1(int x, int fa = -1)
{
	register int ans1 = 0, ans2 = 0;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dfs1(to[i], x);
			register int res = dp[to[i]][0] + w[i];
			if(res >= ans1)
			{
				ans2 = ans1;
				ans1 = res;
			}
			else chkmax(ans2, res);
		}
	dp[x][0] = ans1;
	dp[x][1] = ans2;
}

void dfs2(int x, int fa = -1)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			dp[to[i]][2] = max(dp[x][2], dp[to[i]][0] + w[i] == dp[x][0] ? dp[x][1] : dp[x][0]) + w[i];
			dfs2(to[i], x);
		}
}

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF)
	{
		REP(i, 1, n) dp[i][0] = dp[i][1] = 0;
		e = 1;
		REP(i, 1, n) bg[i] = 0;
		REP(i, 2, n)
		{
			register int x, y;
			scanf("%d%d", &x, &y);
			add(i, x, y);add(x, i, y);
		}
		dfs1(1);
		dfs2(1);
		REP(i, 1, n)
			printf("%d\n", max(dp[i][0], dp[i][2]));
	}

	return 0;
}
