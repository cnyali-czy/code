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
const int maxn = 300 + 5, maxm = 300 + 5;

int m, n;
int G[maxn][maxm];

int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int main()
{
#ifdef CraZYali
	freopen("3720.in", "r", stdin);
	freopen("3720.out", "w", stdout);
#endif
	REP(i, 1, 300)
		REP(j, 1, 300)
			G[i][j] = G[j][i] = gcd(i, j);
	while (scanf("%d%d", &n, &m) != EOF && n && m)
	{
		long long ans = 0;
		REP(i, 1, n)
			REP(j, 1, m)
			{
				register long long temp = ((long long)(n - i)) * (m - j);
				if (G[i][j] == 1) ans += temp;
				else if (G[i][j] == 2) ans -= temp;
			}
		printf("%lld\n", ans * 2ll);
	}
	return 0;
}
