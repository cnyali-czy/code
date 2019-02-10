#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100 + 5, maxm = 2 + 1, maxk = 10 + 2, inf = 0x3f3f3f3f;

template <typename T> inline T read()
{
	T ans(0), p(1);
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

int n, m, k, dp[maxn][maxk][5];

int max(int a1, int a2, int a3, int a4, int a5) {return max(a1, max(a2, max(a3, max(a4, a5))));}
int max(int a1, int a2, int a3) {return max(a1, max(a2, a3));}

int main()
{
#ifdef CraZYali
	freopen("2331.in", "r", stdin);
	freopen("2331.out", "w", stdout);
#endif
	cin >> n >> m >> k;
	if (m == 1) 
	{
		REP(i, 1, n)
		{
			register int temp = read<int>();
			REP(j, 1, k)
			{
				dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0]) + temp;
				dp[i][j][0] = max(dp[i-1][j][1], dp[i-1][j][0]);
			}
		}
		cout << max(dp[n][k][0], dp[n][k][1]) << endl;
	}
	else
	{
		memset(dp, -inf, sizeof(dp));
		REP(i, 0, n) REP(j, 0, k) dp[i][j][0] = 0;
		REP(i, 1, n)
		{
			register int a1 = read<int>(), a2 = read<int>();
			REP(j, 1, k)
			{
				REP(p, 0, 4) chkmax(dp[i][j][0], dp[i-1][j][p]);
				dp[i][j][1] = max(dp[i-1][j-1][0], dp[i-1][j][1], dp[i-1][j-1][2], dp[i-1][j][3], dp[i-1][j-1][4]) + a1;
				dp[i][j][2] = max(dp[i-1][j-1][0], dp[i-1][j-1][1], dp[i-1][j][2], dp[i-1][j][3], dp[i-1][j-1][4]) + a2;
				dp[i][j][3] = max(dp[i-1][j-1][1], dp[i-1][j-1][2], dp[i-1][j][3]) + a1 + a2;
				if (j > 1) chkmax(dp[i][j][3], dp[i-1][j-2][4] + a1 + a2);
				dp[i][j][4] = max(dp[i-1][j-1][0], dp[i-1][j-1][1], dp[i-1][j-1][2], dp[i-1][j-1][3], dp[i-1][j][4]) + a1 + a2;
			}
		}
		int ans = dp[n][k][0];
		REP(i, 1, 4) chkmax(ans, dp[n][k][i]);
		cout << ans << endl;
		REP(i, 1, n)
			REP(j, 1, k)
			REP(p, 0, 4) printf("dp[%d][%d][%d] = %d\n", i, j, p, dp[i][j][p]);
	}
	return 0;
}
