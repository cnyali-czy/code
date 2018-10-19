#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define int long long
using namespace std;
const int maxn = 300 + 5;

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

int d[maxn], c[maxn];
int dp[maxn][maxn];

void dfs(int l, int r)
{
	if (l > 1 && dp[l-1][r] < dp[l][r] + (r - l + 2 == c[l-1]) * d[l-1]) dp[l-1][r] = dp[l][r] + (r - l + 2 == c[l-1]) * d[l-1], dfs(l - 1, r);
	if (r < n && dp[l][r+1] < dp[l][r] + (r - l + 2 == c[r+1]) * d[r+1]) dp[l][r+1] = dp[l][r] + (r - l + 2 == c[r+1]) * d[r+1], dfs(l, r + 1);
}

signed main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	n = read<int>();
	REP(i, 1, n) c[i] = read<int>();
	REP(i, 1, n) d[i] = read<int>();

	REP(i, 1, n)
	{
		REP(p, 1, n) REP(q, 1, n) dp[p][q] = -1;
		dp[i][i] = (c[i] == 1) * d[i];
		dfs(i, i);
		printf("%lld ", dp[1][n]);
	}

	return 0;
}
