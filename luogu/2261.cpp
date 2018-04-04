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

int main()
{
#ifdef CraZYali
	freopen("2261.in", "r", stdin);
	freopen("2261.out", "w", stdout);
#endif
	long long n, k, ans;
	cin >> n >> k;
	ans = n * k;
#ifdef CraZYali
	REP(i, 1, n) fprintf(stderr, "%lld\t", i);
	cerr << endl;
	REP(i, 1, n) fprintf(stderr, "%lld\t", k / i );
	cerr << endl;
#endif
	long long l = 1, r, t;
	while (l <= n)
	{
		t = k / l;
		if (!t) r = n;
		else r = min(k / t, n);
		ans -= t * (r - l + 1) * (l + r) / 2;
		l = r + 1;
	}
	cout << ans;
	return 0;
}
