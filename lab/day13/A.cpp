#define REP(i, s, e) for (int i = s; i <= e; i++)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)

#define dis(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define point pair<double, double>
#define x first
#define y second

#include<bits/stdc++.h>
using namespace std;
const int maxn = 500 + 5;
const double eps = 1e-9, inf = 1e20;
point p[maxn];

inline point get_center(point p1, point p2, point p3)
{
	double a = 2 * (p1.x - p2.x), b = 2 * (p1.y - p2.y), c(p1.x * p1.x + p1.y * p1.y - p2.x * p2.x - p2.y * p2.y);
	double d = 2 * (p1.x - p3.x), e = 2 * (p1.y - p3.y), f(p1.x * p1.x + p1.y * p1.y - p3.x * p3.x - p3.y * p3.y);
	return make_pair((f * b - c * e) / (b * d - a * e), (c * d - a * f) / (b * d - a * e));
}
inline double dist(point a, point b) {return dis(a.x, a.y, b.x, b.y);}
inline bool outside(point a, point o, double r) {return dist(a, o) > r + eps;}

int n, k;
double ans = inf;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> k;
	srand(19260817);
	REP(i, 1, n) scanf("%lf%lf", &p[i].x, &p[i].y);
	int T = 500000;
	REP(i, 1, T)
	{
		double ro = 0;
		point O(0, 0); 
		random_shuffle(p + 1, p + 1 + n);
		REP(u, 1, k)
			if(outside(p[u], O, ro))
			{
				O = p[u];
				ro = 0;
				REP(v, 1, u - 1)
					if(outside(p[v], O, ro))
					{
						O = make_pair((p[u].x + p[v].x) / 2, (p[u].y + p[v].y) / 2);
						ro = dist(O, p[u]);
						REP(w, 1, v - 1)
							if(outside(p[w], O, ro)) ro = dist(O = get_center(p[u], p[v], p[w]), p[u]);
					}
			}
		ans = min(ans, ro);
	}
	printf("%.8lf\n", ans);
	return 0;
}
