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
const int maxn = 1005, maxk = 1005, MOD = 1e6;

int m, n, k;
int c[maxn][maxk];
inline void init_c()
{
	c[1][1] = 1;
	REP(i, 2, 500)
		REP(j, 1, i)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;

}

int main()
{
#ifdef CraZYali
	freopen("10943.in", "r", stdin);
	freopen("10943.out", "w", stdout);
#endif
	init_c();
	while (scanf("%d%d", &n, &k) != EOF && n * k)
		printf("%d\n", c[n + k][k]);
	return 0;
}
