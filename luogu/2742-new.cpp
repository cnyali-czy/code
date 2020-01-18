#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 10000 + 10;
const double eps = 1e-8;
struct vector
{
	double x, y;
	vector(double x = 0, double y = 0) : x(x), y(y) {}
	inline vector operator + (vector B) {return vector(x + B.x, y + B.y);}
	inline vector operator - (vector B) {return vector(x - B.x, y - B.y);}
	inline double operator * (vector B) {return x * B.y - y * B.x;}
}p[maxn], s[maxn];
#define point vector
int n, top;
double dis(double x1, double y1, double x2, double y2) {return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));}
double dis(point A, point B) {return dis(A.x, A.y, B.x, B.y);}
inline bool cmp(point x, point y) {return (x - p[1]) * (y - p[1]) > -eps;}
int main()
{
#ifdef CraZYali
	freopen("2742-new.in", "r", stdin);
	freopen("2742-new.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n)
	{
		scanf("%lf%lf", &p[i].x, &p[i].y);
		if (p[i].y + eps < p[1].y) swap(p[i], p[1]);
	}
	sort(p + 2, p + 1 + n, cmp);
	if (n <= 1) return 0 * puts("0.00");
	s[top = 1] = p[1];
	REP(i, 2, n)
	{
		while (top >= 2 && (s[top] - s[top-1]) * (p[i] - s[top]) < -eps) top--;
		s[++top] = p[i];
	}
	double ans = 0;
	REP(i, 1, top - 1) ans += dis(s[i], s[i+1]);

	printf("%.2lf\n", ans + dis(s[1], s[top]));
	return 0;
}
