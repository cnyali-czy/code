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
const int maxn = 1500 + 10, maxm = maxn - 1;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, m, x, y, z;

int dp[maxn][2];

inline void DP(int x, int fa)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			DP(to[i], x);
			dp[x][0] += dp[to[i]][1];
			dp[x][1] += min(dp[to[i]][1], dp[to[i]][0]);
		}
}

int main()
{
#ifdef CraZYali
	freopen("2038.in", "r", stdin);
	freopen("2038.out", "w", stdout);
#endif
	while (scanf("%d", &n) != EOF)
	{
		REP(i, 1, n) bg[i] = 0;
		e = 1;
		REP(i, 1, n)
		{
			scanf("%d:(%d)", &x, &y);
			x++;
			while (y--)
			{
				scanf("%d", &z);
				add(x, z + 1);
				add(z + 1, x);
			}
		}

		REP(i, 1, n) dp[i][1] = (dp[i][0] = 0) + 1;
		DP(1, 0);
		printf("%d\n", min(dp[1][0], dp[1][1]));
	}
	
	return 0;
}
