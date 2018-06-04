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

int m, n, k;

int f[maxn];
int find(int x) {return f[x] == x ? x : f[x] = find(f[x]);}

int main()
{
#ifdef CraZYali
	freopen("TheSuspects.in", "r", stdin);
	freopen("TheSuspects.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &m) && (n || m))
	{
		REP(i, 1, n) f[i] = i;
		while (m --> 0)
		{
			register int x, y;
			scanf("%d%d", &k, &x);
			x++;
			while (--k)
			{
				scanf("%d", &y);
				y++;
				f[find(x)] = find(y);
			}
		}
		int ans(0);
		REP(i, 1, n) 
			if (find(i) == find(1)) ans++;
		printf("%d\n", ans);
	}

	return 0;
}
