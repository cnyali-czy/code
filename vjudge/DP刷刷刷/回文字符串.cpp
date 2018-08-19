#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10;

int m, n, k;

int dp[maxn][maxn];

char x[maxn], y[maxn];

int main()
{
#ifdef CraZYali
	freopen("回文字符串.in", "r", stdin);
	freopen("回文字符串.out", "w", stdout);
#endif

	scanf("%s", x + 1);

	n = strlen(x + 1);

	register int l = 1, r = n;
	while (l <= n) y[l++] = x[r--];

	REP(i, 1, n)
		REP(j, 1, n)
			dp[i][j] = max(dp[i-1][j-1] + (x[i] == y[j]), max(dp[i-1][j], dp[i][j-1]));
	cout << n - dp[n][n];
	return 0;
}
