#define  REP(i, s, e) for(register long long i = s; i <= e ; i++)
#define DREP(i, s, e) for(register long long i = s; i >= e ; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
const long long maxn = 1e6 + 10;

long long a[maxn], r[maxn];
long long n;

long long exgcd(long long a, long long b, long long &x, long long &y)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	register long long tempans = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return tempans;
}

long long solve()
{
	long long M = a[1], R = r[1], x, y;
	REP(i, 2, n)
	{
		register long long d = exgcd(M, a[i], x, y);
		if ((R - r[i]) % d) return -1ll;
		x = (R - r[i]) / d * x % a[i];
		R -= x * M;
		M = M / d * a[i];
		R %= M;
	}
	return (R % M + M) % M;
}

signed main()
{
#ifdef CraZYali
	freopen("2891.in", "r", stdin);
	freopen("2891.out", "w", stdout);
#endif
	while(~scanf("%lld",&n))
	{
		REP(i, 1, n) scanf("%lld%lld", a + i, r + i);
		printf("%lld\n", solve());
	}
	return 0;
}
