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
const int maxn = 3000 + 10, maxm = maxn;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int m, n, k;

int will[maxn], dp[maxn][maxn];

int DP(int x, int y)
{
	if (x > n - m)
	{
		dp[x][1] = will[x];
		return 1;
	}
	int tot = 0;
	for (register int i = bg[x]; i ; i = ne[i])
	{
		if (to[i] == y) continue;
		tot += DP(to[i], x);
		DREP(j, tot, 1)
			REP(k, 0, j)
				chkmax(dp[x][j], dp[to[i]][k] + dp[x][j - k] - w[i]);
	}
	return tot;
}

int main()
{
#ifdef CraZYali
	freopen("1273.in", "r", stdin);
	freopen("1273.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n - m)
	{
		scanf("%d", &k);
		while (k --> 0)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			add(i, x, y);
			add(x, i, y);
		}
	}
	REP(i, n - m + 1, n) scanf("%d", will + i);
	REP(i, 1, n) REP(j, 1, n) dp[i][j] = -1e9;
	REP(i, 1, n) dp[i][0] = 0;
	DP(1, 0);
	DREP(i, m, 1)
		if (dp[1][i] >= 0)
		{
			cout << i << endl;
			return 0;
		}
}
