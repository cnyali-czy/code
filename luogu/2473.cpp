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
const int maxk = 100 + 5, maxn = 16;

double dp[maxk][1 << maxn], val[maxn];
bool vis[maxk][1 << maxn];

int n, m, k, temp;
int need[maxn];

double dfs(int x = 1, int y = 0)
{
	if (x > k) return 0;
	else if (vis[x][y]) return dp[x][y];
	else
	{
		vis[x][y] = 1;
		dp[x][y] = 0;
		REP(z, 1, n)
			if ((need[z] & y) == need[z])
				dp[x][y] += max(dfs(x + 1, y | (1 << (z - 1))) + val[z], dfs(x + 1, y));
			else dp[x][y] += dfs(x + 1, y);
		return dp[x][y] /= n;
	}
}


int main()
{
#ifdef CraZYali
	freopen("2473.in", "r", stdin);
	freopen("2473.out", "w", stdout);
#endif
	cin >> k >> n;
	REP(i, 1, n)
	{
		scanf("%lf", val + i);
		while (scanf("%d", &temp) * temp)
			need[i] |= 1 << (temp - 1);
	}

	printf("%.6lf", dfs());
	return 0;
}
