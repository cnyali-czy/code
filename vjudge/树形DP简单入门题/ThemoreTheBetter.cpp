#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 200 + 5;

int m, n, k;
vector <int> G[maxn];
int dp[maxn][maxn];

void dfs(int x)
{
	int siz = G[x].size() - 1;
	REP(i, 0, siz)
	{
		int y = G[x][i];
		if (G[y].size()) dfs(y);
		DREP(j, m, 2)
			REP(k, 1, j - 1)
				chkmax(dp[x][j], dp[x][k] + dp[y][j - k]);
	}
}

int main()
{
#ifdef CraZYali
	freopen("ThemoreTheBetter.in", "r", stdin);
	freopen("ThemoreTheBetter.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) * n * m)
	{
		REP(i, 0, n) G[i].clear();
		++m;
		memset(dp, 0, sizeof(dp));
		REP(i, 1, n)
		{
			register int a, b;
			scanf("%d%d", &a, &b);
			G[a].push_back(i);
			REP(j, 1, m) dp[i][j] = b;
		}
		dfs(0);
		printf("%d\n", dp[0][m]);
	}

	return 0;
}
