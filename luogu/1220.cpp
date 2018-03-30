#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
const int maxn = 105;

template <typename T> T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}
int n, k, all, ans = (int)1e9;

pair <int, int> a[maxn];

bool off[maxn];

void dfs(int now, int less, int already = 0, int All = all)
{
	if (already >= ans) return;
	if (!less) ans = already;
	REP(i, 1, n)
		if (i ^ now && !off[i])
		{
			off[i] = 1;
			dfs(i, less - 1, already + All * abs(a[i].first - a[now].first), All - a[i].second);
			off[i] = 0;
		}
}

int s[maxn];
int dp[maxn][maxn][2];

int main()
{
#ifdef CraZYali
	freopen("1220.in", "r", stdin);
	freopen("1220.out", "w", stdout);
#endif
	n = read<int>();
	k = read<int>();
	REP(i, 1, n)
		a[i].first = read<int>(),
		s[i] = s[i-1] + (a[i].second = read<int>());
	memset(dp, 127, sizeof(dp));
	dp[k][k][1] = dp[k][k][0] = 0;
	REP(j, k, n)
		DREP(i, j-1, 1)
		{
			dp[i][j][0] = min(	dp[i+1][j][0] + (s[n] - (s[j] - s[i])) * (a[i+1].first - a[i].first	)	,
								dp[i+1][j][1] + (s[n] - (s[j] - s[i])) * (a[j].first - a[i].first)	)	;
			dp[i][j][1] = min(	dp[i][j-1][0] + (s[n] - (s[j-1] - s[i-1])) * (a[j].first - a[i].first	)	,
								dp[i][j-1][1] + (s[n] - (s[j-1] - s[i-1])) * (a[j].first - a[j-1].first	)	);
		}
	cout << min(dp[1][n][0], dp[1][n][1]);
	return 0;
}
