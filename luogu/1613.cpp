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
const int maxn = 55;

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
int G[maxn][maxn];
bool can[maxn][maxn][70];
int dp[maxn];

#define lowbit(x) (x & -x)

int main()
{
#ifdef CraZYali
	freopen("1613.in", "r", stdin);
	freopen("1613.out", "w", stdout);
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 1, n)
		REP(j, 1, n)
			G[i][j] = 1e9;
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		G[x][y] = 1;
		can[x][y][0] = 1;
	}
	REP(t, 1, 60)
		REP(k, 1, n)
			REP(i, 1, n)
				REP(j, 1, n)
					if (can[i][k][t - 1] && can[k][j][t - 1])
					{
						can[i][j][t] = 1;
						G[i][j] = 1;
					}
	REP(k, 1, n)
		REP(i, 1, n)
			REP(j, 1, n)
				chkmin(G[i][j], G[i][k] + G[k][j]);
	cout << G[1][n];
	return 0;
}
