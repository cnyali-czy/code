#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define poly vector <int>

using namespace std;
const int maxn = 5e5 + 10;

int n, k;i64 T;

inline int deg(const poly &f) {return (int)f.size() - 1;}
poly operator * (poly f, poly g)
{
	int n = deg(f), m = deg(g);
	poly c(n + m + 1, 0);
	REP(i, 0, n) if (f[i]) REP(j, 0, m) if (g[j])
		c[i + j] ^= (f[i] * g[j]);
	return c;
}
poly fix(poly f)
{
	REP(i, n, deg(f)) f[i % n] ^= f[i];
	f.resize(n);
	return f;
}
inline void output(const poly &f)
{
	REP(i, 0, deg(f)) printf("%d%c", f[i], i == end_i ? '\n' : ' ' );
}
poly get(int bin)
{
	poly base(n, 0);
	REP(j, 0, k - 1)
		base[1ll * j * bin % n] ^= 1;
	return base;
}
poly mul(poly f, int t)
{
	poly g(n, 0);
	const i64 c = (1ll << t) % n;
	REP(i, 0, n - 1)
	{
		int res = 0;
		REP(j, 0, k - 1) res ^= f[(i - j * c % n + n) % n];
		g[i] = res;
	}
	return g;
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> k >> T;
	poly f(n);
	REP(i, 0, n - 1) scanf("%d", &f[i]);

	const i64 py = T % n * (k - 1) % n;
	for (i64 bin = 1, t = 0; bin <= T; bin <<= 1, t++)
		if ((T & bin) == bin)
		{
			f = fix(mul(f, t));
//			f = fix(f * get((1ll << t) % n));
		}
	REP(i, 0, n - 1) printf("%d%c", f[(i + py) % n], i == end_i ? '\n' : ' ' );
	return 0;
}
