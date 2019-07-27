//modify to learn

#define REP(i, s, e) for (int i = s; i <= e; i++)
#define dis(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

#define double long double
#define point pair<double, double>
#define x first
#define y second

using namespace std;
const int maxn = 500 + 5;
const double eps = 1e-9, inf = 1e20;
int n, k;
point a[maxn], b[maxn << 1];
double ans;

inline double dist(point A, point B)	{return dis(A.x, A.y, B.x, B.y);}
inline int dcmp(double x)				{return (x > eps) - (x < -eps);}
bool same(double x, double y)			{return fabs(x-y) < eps;}
inline bool cmp(point A, point B)		{return A.x < B.x || A.x == B.x && A.y < B.y;}

point operator + (point A, point B)		{return make_pair(A.x + B.x, A.y + B.y);}
point operator - (point A, point B)		{return make_pair(A.x - B.x, A.y - B.y);}
point operator / (point A, double u)	{return make_pair(A.x / u, A.y / u);}
point operator * (point A, double u)	{return make_pair(A.x * u, A.y * u);}

inline void calc(point o1, point o2, double r, point& x, point& y)
{
	double Dis = dist(o1, o2) / 2;
	point mid = (o1 + o2) / 2, p = (o2 - o1) / 2;
	p = make_pair(p.y, -p.x) / Dis * sqrt(r * r - Dis * Dis);
	x = mid + p, y = mid - p;
}

inline bool check(point o, double r)
{
	int m = k - 1, p = 0;
	REP(i, 1, n)
		if (dcmp(dist(o, a[i])) && dcmp(dist(o, a[i]) - 2 * r) <= 0)
		{
			point x,y;
			calc(o, a[i], r, x, y);
			double ax = atan2(x.y - o.y, x.x - o.x), ay = atan2(y.y - o.y, y.x - o.x);
			b[++p] = make_pair(ax, -1);
			b[++p] = make_pair(ay, 1);
			if (ax > ay)  m--;
		}
	if (m <= 0) return 1;
	sort(b + 1, b + p + 1, cmp);
	REP(i, 1, p)
		if ((m += b[i].y) <= 0) return 1;
	return 0;
}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	srand(233);
	cin >> n >> k;
	REP(i, 1, n) scanf("%LF%LF", &a[i].x, &a[i].y);
	random_shuffle(a + 1, a + n + 1);
	double L, R = inf;
	REP(i, 1, n)
		if (check(a[i], R))
		{
			L = 0;
			while (R - L > eps)
			{
				double MID = (L + R) / 2;
				if (check(a[i], MID)) R = MID;
				else L = MID;
			}
		}
	printf("%.8LF\n", R);
	return 0;
}
