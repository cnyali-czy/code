#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100, maxm = 100;

int m, n, k;

int dp[maxn][maxm][maxn][maxm];
int a[maxn][maxm];

int d[][2] = {{1, 0}, {0, 1}};

int main()
{
#ifdef CraZYali
	freopen("1006.in", "r", stdin);
	freopen("1006.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
		REP(j, 1, m)
			scanf("%d", &a[i][j]);

	REP(x1, 1, n)
		REP(y1, 1, m)
			REP(x2, 1, n)
				REP(y2, 1, m)
					REP(i, 0, 1)
						REP(j, 0, 1)
						{
							register int xA = x1 + d[i][0];
							register int yA = y1 + d[i][1];
							register int xB = x2 + d[j][0];
							register int yB = y2 + d[j][1];
							if (xA == xB && yA == yB) chkmax(dp[xA][yA][xB][yB], dp[x1][y1][x2][y2] + a[xA][yA]);
							else chkmax(dp[xA][yA][xB][yB], dp[x1][y1][x2][y2] + a[xA][yA] + a[xB][yB]);
						}

	cout << dp[n][m][n][m];
	return 0;
}
