#define  REP(i, s, e) for (register int i = s; i <= e; i++)
#define DREP(i, s, e) for (register int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 3e6 + 10;

int n, MOD, Inv[maxn];

signed main()
{
#ifdef CraZYali
	freopen("3811.in", "r", stdin);
	freopen("3811.out", "w", stdout);
#endif
	cin >> n >> MOD;
	Inv[0] = 1;Inv[1] = 1;
	REP(i, 2, n) Inv[i] = -MOD / i * Inv[MOD % i] % MOD;
	REP(i, 1, n) printf("%lld\n", (Inv[i] + MOD) % MOD);
	return 0;
}
