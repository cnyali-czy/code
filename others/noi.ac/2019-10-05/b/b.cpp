//modify to learn

#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 50 + 5, lim = 1594323;

int n, m;
int dp[maxn][lim], edge[maxn], msk1[lim], msk2[lim];

int main()
{
#ifdef CraZYali
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	REP(i, 0, lim - 1)
	{
		int cur(i);
		REP(j, 0, 12)
		{
			msk1[i] |= (cur % 3 == 1) << j;
			msk2[i] |= (cur % 3 == 2) << j;
			cur /= 3;
		}
	}
	cin >> n >> m;
	while (m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if (x > y) swap(x, y);
		edge[y-1] |= 1 << (y - 1 - x);
	}
	dp[0][0] = 1;
	REP(i, 0, n - 1)
		REP(j, 0, lim - 1) if (dp[i][j])
		{
			register int nj = 3 * j % lim;
				(dp[i + 1][nj		] += dp[i][j]) &= 3;
			if (!(msk2[j] & edge[i]))
				(dp[i + 1][nj + 1	] += dp[i][j]) &= 3;
			if (!(msk1[j] & edge[i]))
				(dp[i + 1][nj + 2	] += dp[i][j]) &= 3;
		}
	int ans(0);
	REP(j, 0, lim - 1)
		(ans += dp[n][j]) &= 3;
	cout << (ans == 3) << endl;
	return 0;
}
