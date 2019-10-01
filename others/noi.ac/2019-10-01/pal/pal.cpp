#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1000 + 10;

char s[maxn];
int n, dp[maxn][maxn];

int main()
{
#ifdef CraZYali
	freopen("pal.in", "r", stdin);
	freopen("pal.out", "w", stdout);
#endif
	scanf("%s", s + 1);
	n = strlen(s + 1);
	memset(dp, 0x3f, sizeof dp);
	dp[0][n+1] = 0;
	REP(i, 1, n)
	{
		dp[0][i] = n - i + 1;
		dp[i][n+1] = i;
	}
	int ans(1e9);
	REP(i, 1, n)
		DREP(j, n, 1)
		{
			dp[i][j] = min(dp[i][j+1], dp[i-1][j]) + 1;
			if (s[i] == s[j]) chkmin(dp[i][j], dp[i-1][j+1]);
			if (i >= j - 1) chkmin(ans, dp[i][j]);
		}
	cout << ans << endl;
	return 0;
}
