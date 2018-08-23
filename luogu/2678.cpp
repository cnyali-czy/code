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
const int maxn = 50000 + 10, inf = 1e9;

int m, n, L;
int d[maxn];

bool check(int mid)
{
	register int now = 0;
	REP(i, 1, n)
	{
		int S = i;
		register int dist = d[i] - d[i - 1];
		while (dist < mid && i < n)
		{
			dist = d[++i] - d[S - 1];
			now++;
			if (now > m) return 0;
		}
		if (dist < mid) return 0;
	}
	return 1;
}

int main()
{
#ifdef CraZYali
	freopen("2678.in", "r", stdin);
	freopen("2678.out", "w", stdout);
#endif
	cin >> L >> n >> m;
	REP(i, 1, n) scanf("%d", d + i);
	d[n + 1] = L;
	n++;

	register int l(0), r(inf);
	while (l <= r)
	{
		register int mid = l + r >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid - 1;
	}

	cout << l - 1;
	
	return 0;
}
