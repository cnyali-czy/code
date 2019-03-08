#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const double g = 9.8, eps = 1e-8, PI = acos(-1);

int T;
double x, y, v;

bool flag;
double solve(double a, double b, double c)
{
	flag = 1;
	double delta = b * b - 4 * a * c;
	if (delta < -eps) {flag = 0;return -1;}
	double x1 = (-b - sqrt(delta)) / (a * 2), x2 = (-b + sqrt(delta)) / (a * 2);
	if (x1 > eps) return x1;
	else return x2;
}
bool same(double a, double b) {return fabs(a - b) < eps;}

int main()
{
#ifdef CraZYali
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif
	cin >> T;
	while (T --> 0)
	{
		scanf("%lf%lf%lf", &x, &y, &v);
		double ret = 0.5 * g * x * x / v / v;
		if (same(x, 0)) {printf("%lf\n", PI * (same(y, 0) ^ 1));continue;}
		double TanTheta = solve(ret, -x, y + ret);
		if (!flag) printf("-1\n");
		else printf("%lf\n", atan(TanTheta));
	}
	return 0;
}
