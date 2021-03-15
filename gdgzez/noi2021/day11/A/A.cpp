#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	int T;cin >> T;
	while (T--)
	{
		int n, m, a, b, c, d;
		scanf("%lld%lld", &n, &m);
		int nn = n, mm = m;
		if (n == m) a = b = c = d = 1;
		else
		{
			int flg = 0;
			if (n > m) {swap(n, m);flg = 1;}
			int p = 1, q = 1;
			while (m >= n * 8) {n <<= 3;q <<= 1;}
			while (m >= n * 2) {m *= 8;n *= 27;p *= 2;q *= 3;}
			if (n > m) {swap(n, m);swap(p, q);flg ^= 1;}
			int x = m + n, y = 3 * (m - n);
			int u = x + y >> 1, v = x - y >> 1;
			a = 3 * n + u, b = 3 * n - u;
			c = 3 * m + v, d = 3 * m - v;
			a *= p;b *= p;c *= q;d *= q;
			if (flg) swap(a, c), swap(b, d);
		}
		printf("%lld %lld %lld %lld\n", a, b, c, d);
	}
	return 0;
}
