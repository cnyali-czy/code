#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10, inf = 0x3f3f3f3f;

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
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int n, t[maxn], b[maxn], dp[maxn][300][20];
const int lim = 1 << 8;

int main()
{
#ifdef CraZYali
	freopen("2157.in", "r", stdin);
	freopen("2157.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();
		REP(i, 1, n)
			t[i] = read<int>(), b[i] = read<int>();
		memset(dp, inf, sizeof(dp));
		dp[1][0][7] = 0;
		REP(i, 1, n)
			REP(j, 0, lim - 1)
			REP(k, 0, 15)
			if (dp[i][j][k] != inf)
				if (j & 1) chkmin(dp[i + 1][j >> 1][k - 1], dp[i][j][k]);
				else
				{
					int ret = inf;
					REP(h, 0, 7)
						if (!((j >> h) & 1))
						{
							if (i + h > ret) break;
							chkmin(ret, i + h + b[i + h]);
							chkmin(dp[i][j | (1 << h)][h + 8], dp[i][j][k] + (i + k - 8 ? (t[i + k - 8] ^ t[i + h]) : 0));
						}
				}
		int ans = inf;
		REP(k, 0, 8) chkmin(ans, dp[n + 1][0][k]);
		printf("%d\n", ans);
	}
	return 0;
}
