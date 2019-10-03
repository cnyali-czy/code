#define  REP(i, s, e) for (int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 3000 + 10, MOD = 998244353;

int n, m, dp[maxn][maxn];
char s[maxn];

int main()
{
#ifdef CraZYali
	freopen("code.in", "r", stdin);
	freopen("code.out", "w", stdout);
#endif
	scanf("%d\n%s", &m, s + 1);
	n = strlen(s + 1);
	dp[0][0] = 1;
//	REP(i, 0, m) sum[0][i] = 1;
	REP(i, 1, n)
	{
		int sta = i - 1, cur = 0;
		DREP(j, i, 1)
		{
			cur |= (s[j] - '0' << i-j);
			if (cur > m) break;
			if (s[j] == '0') continue;
			REP(k, 0, m - cur)
			{
				(dp[i][k + cur] += dp[j-1][k]) %= MOD;
		//		printf("dp[%d][%d] += dp[%d][%d]\n",i,k+cur,j-1,k);
			}
		}
	}
	/*
	REP(i, 1, n)
		REP(j, 1, m)
			printf("dp[%d][%d] = %d\n",i,j,dp[i][j]);
	*/
	int ans(0);
	REP(i, 1, m) (ans += dp[n][i]) %= MOD;
	cout << (2ll * ans % MOD + MOD) % MOD << endl;
	return 0;
}
