#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const double eps = 1e-9;

int T;

double y;
double f(double x) {return 6 * x * x * x * x * x * x * x + 8 * x * x * x * x * x * x + 7 * x * x * x + 5 * x * x - y * x;}

int main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	cin >> T;
	while (T --> 0)
	{
		scanf("%lf", &y);
		double l = 0, r = 100, ans(0);
		while (r - l > eps)
		{
			double p1 = l + (r - l) / 3;
			double p2 = r - (r - l) / 3;
			double f1 = f(p1), f2 = f(p2);
			chkmin(ans, min(f1, f2));
			if (f1 < f2) r = p2;
			else l = p1;
		}
		printf("%.4lf\n", ans);
	}

	return 0;
}
