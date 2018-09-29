#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 7, maxN = (1 << maxn) + 10;

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

int m, n, k, N;

double p[maxN][maxN], dp[maxn + 5][maxN];

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF && n != -1)
	{
		N = 1 << n;
		REP(i, 0, N - 1)
			REP(j, 0, N - 1)
			{
				scanf("%lf", &p[i][j]);
				dp[0][i] = 1;
			}
		REP(i, 0, n - 1)
			REP(j, 0, N - 1)
			{
				register double sum = 0;
				for (register int k = 1 << i; k <= (1 << (i + 1)) - 1; k++)
					sum += (double)dp[i][j ^ k] * p[j][j ^ k];
				dp[i + 1][j] = dp[i][j] * sum;
			}
/*
		REP(i, 0, N - 1)
			fprintf(stderr, "%.4lf%c", dp[n][i], i == N - 1 ? '\n' : ' ');
*/

		register int ans = 0;

		REP(i, 1, N - 1)
			if (dp[n][i] > dp[n][ans]) ans = i;
		printf("%d\n", ans + 1);
	}
	return 0;
}
