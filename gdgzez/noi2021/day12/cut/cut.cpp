#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;
const double eps = 1e-8;

int n;
struct P
{
	double x, y;
	void input()
	{
		scanf("%lf%lf", &x, &y);
	}
	void output()
	{
		printf("%.10lf %.10lf\n", x, y);
	}
	P() {}
	P(double x, double y) : x(x), y(y) {}
	double len() {return sqrt(x * x + y * y);}
	double operator * (P B) {return x * B.y - y * B.x;}
	P operator + (P B) {return P(x + B.x, y + B.y);}
	P operator - (P B) {return P(x - B.x, y - B.y);}
}a[maxn * 3];
double C, S;
inline P operator * (P p, double B) {return P(B * p.x, B * p.y);}
inline P operator * (double B, P p) {return P(B * p.x, B * p.y);}
#define fi first
#define se second
double L[maxn * 3];
pair <P, int> go(P x, int cur, double need = C / 2)
{
	need += (x - a[cur]).len();
	while (need > eps)
	{
		double full = L[cur];
		if (need > full)
		{
			need -= full;
			cur++;
		}
		else return make_pair(a[cur] + (need / full) * (a[cur + 1] - a[cur]), cur % n);
	}
}
#define findnext go
double f(P p, int s)
{
	auto res = findnext(p, s);
	auto q = res.fi;
	auto t = res.se;
	if (t < s) t += n;
	double s1 = 0, s2 = 0;
	REP(i, s + 1, t - 1) s1 += (a[i] - p) * (a[i + 1] - p);s1 += (a[t] - p) * (q - p);
	s1 /= 2;s2 = S - s1;
	return s1 - s2;
}
inline bool iszero(double x) {return fabs(x) < eps;}
void output(P p, int s)
{
	p.output();
	findnext(p, s).fi.output();
	exit(0);
}
int main()
{
#ifdef CraZYali
	freopen("cut.in", "r", stdin);
	freopen("cut.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 0, n - 1) a[i].input(), a[i + n + n] = a[i + n] = a[i];
	REP(i, 0, n - 1) L[i] = L[i + n] = L[i + n + n] = (a[i + 1] - a[i]).len();
	REP(i, 0, n - 1) C += L[i];//(a[i] - a[i + 1]).len();
	REP(i, 1, n - 2) S += (a[i] - a[0]) * (a[i + 1] - a[0]);S /= 2;
	cerr << C << ' ' << S << endl;

#ifdef CraZYali
	auto qd = P(-7.64126, 2.69509);
	findnext(qd, 0).fi.output();
	cout << findnext(qd, 0).se << endl;
	cout << f(qd, 0) << endl;
	puts("Test Done\n===============");
#endif

	auto p = a[0];int s = 0;

	double l = 0, r = C / 2, fp = f(p, s);
	if (iszero(f(p, s))) output(p, s);

	REP(Times, 1, 100)
	{
		double mid = (l + r) / 2;
		auto res = go(p, s, mid);
		auto np = res.fi;auto ns = res.se;
		double F = f(np, ns);
		if (iszero(F)) output(np, ns);
		if (fp > eps)
			if (F < -eps) r = mid;
			else l = mid;
		//				p = np;s = ns;
		else
			if (F > eps) r = mid;
			else l = mid;
		//				p = np;s = ns;
	}
	auto res = go(p, s, l);
	p = res.fi;s = res.se;
	output(p, s);

	return 0;
}
