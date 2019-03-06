#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define double long double

using namespace std;
const double eps = 1e-9, down = .97, maxt = .96;

#define x first
#define y second
#define dis2(x1, y1, x2, y2) ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define dis(x1, y1, x2, y2) sqrt(dis2(x1, y1, x2, y2))

double ax, ay, bx, by, cx, cy, dx, dy, P, Q, R, l1, l2, ans = 1e9;
bool same(double a, double b) {return fabs(a - b) < eps;}
pair <double, double> calc(double x1, double y1, double x2, double y2, double a)
{
	if (same(x1, x2))
		if (y1 > y2) return make_pair(x1, y1 - a);
		else return make_pair(x1, y1 + a);
	double D = dis2(x1, y1, x2, y2);
	double x = (x1 * D + a * sqrt(D) * (x2 - x1)) / D;
	double y = (a * (y2 - y1) + y1 * sqrt(D)) / sqrt(D);
	return make_pair(x, y);
}

double f(double a, double b)
{
	pair <double, double> p1(calc(ax, ay, bx, by, a)), p2(calc(dx, dy, cx, cy, b));
	double x1(p1.first), y1(p1.second), x2(p2.first), y2(p2.second);
	return a / P + b / Q + dis(x1, y1, x2, y2) / R;
}

bool flag = 1;

void work()
{
	double T = 1000, d(1), x(0), y(0);
	double ret = f(0, 0);
	while (T > eps)
	{
		chkmin(ans, ret);
		if (clock() / CLOCKS_PER_SEC >= maxt) {flag = 0;return;}
		double tx = x + ((rand() & 1) * 2 - 1) * d * l1;
		double ty = y + ((rand() & 1) * 2 - 1) * d * l2;
		if (fabs(l1) < eps) tx = 0;
		else
		{
			while (tx < 0) tx += l1;
			while (tx > l1) tx -= l1;
		}
		if (fabs(l2) < eps) ty = 0;
		else
		{
			while (ty > l2) ty -= l2;
			while (ty < 0) ty += l2;
		}
		double temp = f(tx, ty), delta = temp - ret;
		if (temp < ret || exp(delta / T) < rand() * 1. / RAND_MAX)
		{
			x = tx;y = ty;
			chkmin(ret, temp);
		}
		d *= down;
		T *= down;
	}
}

int main()
{
#ifdef CraZYali
	freopen("2571.in", "r", stdin);
	freopen("2571.out", "w", stdout);
#endif
	srand((unsigned long long)new char);
	cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy >> P >> Q >> R;
	l1 = dis(ax, ay, bx, by);l2 = dis(cx, cy, dx, dy);
	ans = f(0, 0);
	int times = 70;
	while (flag && times--) work();
	printf("%.2LF\n", ans);
	return 0;
}
