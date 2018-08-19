#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 200 + 5;

int m, n, k;

int G[maxn][maxn], match[maxn];
bool vis[maxn];

int dfs(int x)
{
	REP(i, 1, n)
		if (G[x][i] && !vis[i])
		{
			vis[i] = 1;
			if (!match[i] || dfs(match[i]))
			{
				match[i] = x;
				return 1;
			}
		}
	return 0;
}

int main()
{
#ifdef CraZYali
	freopen("1129.in", "r", stdin);
	freopen("1129.out", "w", stdout);
#endif
	register int Case;
	cin >> Case;
	while (Case--)
	{
		scanf("%d", &n);
		REP(i, 1, n)
			REP(j, 1, n)
				scanf("%d", &G[i][j]);
		register int ans = 0;
		REP(i, 1, n) match[i] = 0;
		REP(i, 1, n)
		{
			REP(j, 1, n) vis[j] = 0;
			ans += dfs(i);
		}
		if (ans == n) printf("Yes\n");
		else printf("No\n");
	}


	return 0;
}
