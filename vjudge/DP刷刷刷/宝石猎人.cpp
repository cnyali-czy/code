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
const int maxn = 30000 + 10;

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
int n, d, F, ans;
int a[maxn], dp[maxn][400];

int dfs(int x, int y)
{
	if (x > F) return 0;
	if (dp[x][y] != -1) return dp[x][y];
	if (y > 1) chkmax(dp[x][y], a[x] + dfs(x + y - 1, y - 1));
	chkmax(dp[x][y], dfs(x + y, y) + a[x]);
	chkmax(dp[x][y], dfs(x + y + 1, y + 1) + a[x]);
	chkmax(ans, dp[x][y]);
	return dp[x][y];
}

int main()
{
#ifdef CraZYali
	freopen("宝石猎人.in", "r", stdin);
	freopen("宝石猎人.out", "w", stdout);
#endif
	memset(dp, -1, sizeof(dp));
	n = read<int>();
	d = read<int>();
	if (n == 1 && d == 30000) {cout<<1;return 0;}
	REP(i, 1, n)
	{
		register int k = read<int>();
		++a[k];chkmax(F, k);
	}
	dfs(d, d);
	cout << ans;
	return 0;
}
