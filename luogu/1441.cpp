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
const int maxn = 100000 + 5;

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
int m, n, k;

int a[maxn];
bool use[maxn];

int dp[maxn], ans;
vector <int> v;

int Total;

inline void DP()
{
	v.clear();
	REP(i, 1, n)
		if (use[i]) v.push_back(a[i]);
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	REP(i, 0, n - m - 1)
		DREP(j, Total, v[i])
			dp[j] |= dp[j - v[i]];
	int res = 0;
	REP(i, 1, Total)
		if (dp[i]) res++;
	chkmax(ans, res);
}

void dfs(int x, int already)
{
	if (x > n) return;
	if (already == n - m)
	{
		DP();
		return;
	}
	x++;
	use[x] = 1;
	dfs(x, already + 1);
	use[x] = 0;
	dfs(x, already + 0);
}

int main()
{
#ifdef CraZYali
	freopen("1441.in", "r", stdin);
	freopen("1441.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, n) Total += a[i] = read<int>();
	dfs(0, 0);
	cout << ans;
	return 0;
}
