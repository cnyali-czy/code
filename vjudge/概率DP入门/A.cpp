#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, maxm = 1000 + 10;
const double inf = 1e9;

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;

double a[maxn][maxm][4];

double dp[maxn][maxm];

int d[][2] = {{1, 0}, {-1, 0}, {0, 0}};

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) != EOF)
	{
		REP(i, 1, n)
			REP(j, 1, m)
				REP(k, 1, 3)
					scanf("%lf", &a[i][j][k]);
		REP(i, 1, n)
			REP(j, 1, m)
				dp[i][j] = inf;
		dp[n][m] = 0;
		DREP(i, n, 1)
			DREP(j, m, 1)
			{
				if (i == n && j == m) continue;
				if (a[i][j][1] == 1) continue;
				dp[i][j] = (dp[i][j+1] * a[i][j][2] + dp[i+1][j] * a[i][j][3] + 2) / (1 - a[i][j][1]);
			}
		printf("%.3lf\n", dp[1][1]);
	}
	
	return 0;
}
