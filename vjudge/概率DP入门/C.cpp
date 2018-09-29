#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;

int n, m;

double dp[maxn][maxm];

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m;

	DREP(i, n, 0)
		DREP(j, m, 0)
		{
			if (i == n && j == m) continue;
			register double sum = n * m - i * j;
			register double p1 = (double)(i * j) / sum;
			register double p2 = (double)(i * (m - j)) / sum;
			register double p3 = (double)((n - i) * j) / sum;
			register double p4 = (double)((n - i) * (m - j)) / sum;
			dp[i][j] = (dp[i][j] + 1) * p1 + (dp[i][j+1] + 1) * p2 + (dp[i+1][j] + 1) * p3 + (dp[i+1][j+1] + 1) * p4;
		}
	
	printf("%.4lf", dp[0][0]);

	return 0;
}
