#define DREP(i, s, e) for(register long long i = s; i >= e ;i--)
#define  REP(i, s, e) for(register long long i = s; i <= e ;i++)

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

#define lowbit(a) (a & -a)

inline long long count(long long x)
{
	long long cnt = 0;
	while (x)
	{
		if (x & 1) cnt++;
		x >>= 1;
	}
	return cnt;
}

int main()
{
#ifdef CraZYali
	freopen("1582.in", "r", stdin);
	freopen("1582.out", "w", stdout);
#endif
	long long a, b, ans(0);
	cin >> a >> b;
	while (count(a) > b)
	{
		ans += lowbit(a);
		a += lowbit(a);
	}
	cout << ans;
	return 0;
}

