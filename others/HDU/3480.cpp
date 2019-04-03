#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 10000 + 10, maxm = 5000 + 10, inf = 0x3f3f3f3f;

template <typename T> T read()
{
	T ans = 0, p = 1;
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

int n, m, a[maxn], s[maxm][maxn];

int cost(int i, int j) {return (a[i]-a[j]) * (a[i]-a[j]);}

int dp[maxm][maxn];

int main()
{
#ifdef CraZYali
	freopen("3480.in", "r", stdin);
	freopen("3480.out", "w", stdout);
#endif
	int T = read<int>();
	REP(Case, 1, T)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		sort(a + 1, a + 1 + n);
		REP(i, 1, n) dp[1][i] = cost(s[1][i] = 1, i);
		REP(i, 2, m) s[i][n+1] = n-1;
		REP(i, 2, m)
			DREP(j, n, 1)
			{
				int &ans = dp[i][j] = inf;
				REP(k, s[i-1][j], s[i][j+1])
					if (ans > dp[i-1][k] + cost(k+1, j))
						ans = dp[i-1][s[i][j] = k] + cost(k+1, j);
			}
		printf("Case %d: %d\n", Case, dp[m][n]);
	}
	return 0;
}
