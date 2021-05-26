#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

int n, L, a[maxn];
int opt[maxn];

signed main()
{
#ifdef CraZYali
	freopen("1997.in", "r", stdin);
	freopen("1997.out", "w", stdout);
#endif
	cin >> n >> L;
	REP(i, 1, n) scanf("%lld", a + i);
	int mx = 1;
	REP(i, 1, n - 1) if (a[i] + a[i + 1] > a[mx] + a[mx + 1]) mx = i;
	if (a[mx] + a[mx + 1] < L)
	{
		puts("Impossible");
		return 0;
	}
	puts("Possible");
	DEP(i, n - 1, mx + 1) printf("%lld\n", i);
	REP(i, 1, mx) printf("%lld\n", i);


	return 0;
}
