#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 500 + 5, maxm = 500 + 5;

template <typename T> T read()
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

int m, n, k;
int A[maxn][maxm], B[maxn][maxm];
int dp[maxn][maxm];

int main()
{
#ifdef CraZYali
	freopen("3530.in", "r", stdin);
	freopen("3530.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) && (n || m))
	{
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		memset(dp, 0, sizeof(dp));
		REP(i, 1, n)
			REP(j, 1, m)
				A[i][j] = A[i][j - 1] + read<int>();
		REP(i, 1, n)
			REP(j, 1, m)
				B[i][j] = B[i - 1][j] + read<int>();
		REP(i, 1, n)
			REP(j, 1, m)
				dp[i][j] = max(dp[i - 1][j] + A[i][j], dp[i][j - 1] + B[i][j]);
		printf("%d\n", dp[n][m]);
	}


	return 0;
}
