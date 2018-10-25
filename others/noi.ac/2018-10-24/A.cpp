#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

#define double long double
using namespace std;
const double eps = 1e-10, E = 1e-7;
const int maxn = 1e5 + 10;

unsigned long long int n, m, k;

unsigned long long d[maxn], a[maxn], b[maxn], c[maxn];

bool check(double x)
{
	double res = 0;
	REP(i, 1, n)
	{
		double need = x - d[i];
		if (need > 0) res += need * need * a[i] + b[i] * need + c[i];
		if (res > m) return 0;
		if (res == m && eps) return 0;
	}
	return res <= m;
}

int main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) scanf("%llu%llu%llu%llu", d + i, a + i, b + i, c + i);
	cin >> m;
	register double l = 0, r = 1e20, ans;
	while (r - l >= eps)
	{
		register double mid = (l + r) / 2.0;
		if (check(mid))
		{
			l = mid;
			ans = mid;
		}
		else r = mid;
	}
	printf("%.8Lf", ans);
	return 0;
}

