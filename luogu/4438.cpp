#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <cstring>
#include <iostream>
#include <cstdio>
#include <stack>
#define int long long

using namespace std;
const int maxn = 20000 + 10 << 1;

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

int dp[maxn][50][50];
int n, L[maxn], R[maxn], a[maxn], b[maxn], c[maxn];

#define ls L[x]
#define rs R[x]
void dfs(int x, int l, int r)
{
	if (x >= n)
		REP(i, 0, l)
			REP(j, 0, r)
			dp[x][i][j] = c[x] * (a[x] + i) * (b[x] + j);
	else
	{
		dfs(ls, l + 1, r);
		dfs(rs, l, r + 1);
		REP(i, 0, l)
			REP(j, 0, r)
			dp[x][i][j] = min(dp[ls][i+1][j] + dp[rs][i][j], dp[ls][i][j] + dp[rs][i][j+1]);
	}
}

signed main()
{
#ifdef CraZYali
	freopen("4438.in", "r", stdin);
	freopen("4438.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n-1)
	{
		L[i] = read<int>();R[i] = read<int>();
		if (L[i] < 0) L[i] = -L[i] + n - 1;
		if (R[i] < 0) R[i] = -R[i] + n - 1;
	}
	REP(i, n, n + n - 1) a[i] = read<int>(), b[i] = read<int>(), c[i] = read<int>();
	dfs(1, 0, 0);
	cout << dp[1][0][0];
	return 0;
}
