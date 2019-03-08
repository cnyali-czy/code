#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 10000 + 10, maxk = 10000 + 10;
const double eps = 1e-8;

int n, k;
double a[maxn];

bool judge(double mid)
{
	int res = 0;
	REP(i, 1, n) res += floor(a[i] / mid);
	return res >= k;
}

int main()
{
#ifdef CraZYali
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
#endif
	while (scanf("%d%d", &n, &k) != EOF && n + k)
	{
		REP(i, 1, n) scanf("%lf", a + i);
		double l(0), r(100000), ans(100000);
		int times = 100;
		while (times--)
		{
			double mid = 0.5 * (l + r);
			if (judge(mid)) l = ans = mid;
			else r = mid;
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}
