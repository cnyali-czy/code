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

const int maxn = 100010;

int m, n, k;

int main()
{
#ifdef CraZYali
	freopen("1969.in", "r", stdin);
	freopen("1969.out", "w", stdout);
#endif
	long long ans;
	cin >> n >> ans;k = ans;
	while (--n)
	{
		cin >> m;
		if (m > k) ans += m - k;
		k = m;
	}
	cout << ans;
	return 0;
}

