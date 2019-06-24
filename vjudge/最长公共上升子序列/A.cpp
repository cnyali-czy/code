#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 500 + 5, maxm = 500 + 5;

int n, m, Case;
int a[maxn], b[maxm], dp[maxn][maxm];

pair <int, int> path[maxn][maxm];

int s[maxm], top;

int main()
{
	cin >> Case;
	while (Case--)
	{
		scanf("%d", &n);
		REP(i, 1, n) scanf("%d", a + i);
		scanf("%d", &m);
		REP(i, 1, m) scanf("%d", b + i);
		//		REP(i, 1, n) printf("%d%c", a[i], i == n ? '\n' : ' ' );
		//		REP(i, 1, m) printf("%d%c", b[i], i == m ? '\n' : ' ' );
		memset(path, 0, sizeof(path));
		memset(dp, 0, sizeof(dp));
		REP(i, 1, n)
		{
			int Max(0), prei(0), prej(0);
			REP(j, 1, m)
			{
				path[i][j] = make_pair(i-1, j);
				dp[i][j] = dp[i-1][j];
				if (a[i] > b[j] && Max < dp[i][j])
				{
					Max = dp[i][j];
					prei = i-1;
					prej = j;
				}
				if (a[i] == b[j])
				{
					dp[i][j] = Max + 1;
					path[i][j] = make_pair(prei, prej);
				}
			}
		}
		int ans = dp[n][1];
		int End = 1;
		REP(i, 2, m)
			if (dp[n][i] > dp[n][End])
			{
				ans = dp[n][i];
				End = i;
			}
		printf("%d\n", ans);
		int i = n, j = End;
		top = 0;
		while (dp[i][j])
		{
			int ti = path[i][j].first;
			int tj = path[i][j].second;
			if (dp[i][j] ^ dp[ti][tj]) s[++top] = b[j];
			i = ti;j = tj;
		}
		DREP(i, top, 1) printf("%d%c", s[i], i == 1 ? '\n' : ' ' );
		putchar(10);
	}
	return 0;
}
