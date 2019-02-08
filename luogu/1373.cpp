#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 800 + 1, maxm = 800 + 1, maxk = 16 + 1, MOD = 1e9 + 7;

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

int m, n, k;

int a[maxn][maxm], dp[maxn][maxm][maxk][2];

int mod(int x, int y = MOD) {return (x % y + y) % y;}

int main()
{
#ifdef CraZYali
	freopen("1373.in", "r", stdin);
	freopen("1373.out", "w", stdout);
#endif
	cin >> n >> m >> k;++k;
	REP(i, 1, n)
		REP(j, 1, m) dp[i][j][a[i][j] = (read<int>() % k)][0] = 1;
	REP(i, 1, n)
		REP(j, 1, m)
		REP(p, 0, k)
		{
			dp[i][j][p][0] = mod(dp[i][j][p][0] + dp[i-1][j][mod(p - a[i][j], k)][1]);
			dp[i][j][p][0] = mod(dp[i][j][p][0] + dp[i][j-1][mod(p - a[i][j], k)][1]);
			dp[i][j][p][1] = mod(dp[i][j][p][1] + dp[i-1][j][mod(p + a[i][j], k)][0]);
			dp[i][j][p][1] = mod(dp[i][j][p][1] + dp[i][j-1][mod(p + a[i][j], k)][0]);
		}
	int ans = 0;
	REP(i, 1, n) REP(j, 1, m) ans = mod(ans + dp[i][j][0][1]);
	cout << ans;
	return 0;
}
