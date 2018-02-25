#define DREP(i, s, e) for (register int i = s; i >= e ; i--)
#define  REP(i, s, e) for (register int i = s; i <= e ; i++)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 105, maxm = 505;

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

int n, m, k, c, p;
int dp[maxn][maxm], pre[maxn][maxm], use[maxn][maxm], level[maxn];

int main()
{
	freopen("diablo.in", "r", stdin);
	freopen("diablo.out", "w", stdout);
	n = read<int>();
	m = read<int>();
	REP(i, 1, n)
	{
		c = read<int>();
		p = read<int>();
		REP(j, 1, m)
			dp[i][j] = dp[i - 1][pre[i][j] = j];
		REP(q, 1, p)
		{
			int v(read<int>()), w(c * q);
			REP(j, w, m)
				if (dp[i][j] < dp[i - 1][j - w] + v)
				{
					dp[i][j] = dp[i - 1][pre[i][j] = j - w] + v;
					use[i][j] = q;
				}
		}
	}
	k = 1;
	REP(i, 2, m)
		if(dp[n][i] > dp[n][k])	k = i;
	printf("%d\n", dp[n][k]);
	DREP(i, n, 1)
	{
		level[i] = use[i][k];
		k = pre[i][k];
	}
	REP(i, 1, n) printf("%d\n", level[i]);
	return 0;
}
