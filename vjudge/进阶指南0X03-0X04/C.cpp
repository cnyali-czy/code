#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;
const double eps = 1e-8;

int n, k;
double a[maxn], sum[maxn];

bool check(double mid)
{
	REP(i, 1, n) sum[i] = sum[i-1] + a[i] - mid;
	double now = 1e10, ans = -1e10;
	REP(i, k, n)
	{
		chkmin(now, sum[i-k]);
		chkmax(ans, sum[i] - now);
	}
	return ans > -eps;
}

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> k;
	REP(i, 1, n) scanf("%lf", a + i);
	
	double l = -1e6, r = 1e6;
	while (r - l > eps)
	{
		double mid = 0.5 * (l + r);
		if (check(mid)) l = mid;
		else r = mid;
	}
	int ans = r * 1000;
	cout << ans << endl;
	return 0;
}
