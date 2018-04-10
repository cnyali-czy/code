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
const int maxn = 1000 + 10;

int sum[maxn];
int n, Case;

int main()
{
#ifdef CraZYali
	freopen("11728.in", "r", stdin);
	freopen("11728.out", "w", stdout);
#endif
	REP(i, 1, 1000)
		REP(j, 1, i)
			if (i % j == 0) sum[i] += j;
	while (scanf("%d", &n) != EOF && n)
	{
		register bool flag = 0;
		DREP(i, 1000, 1)
			if (sum[i] == n)
			{
				printf("Case %d: %d\n", ++Case, i);
				flag = 1;
				break;
			}
		if (!flag) printf("Case %d: %d\n", ++Case, -1);
	}
	return 0;
}
