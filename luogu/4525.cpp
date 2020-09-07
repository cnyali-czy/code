/*
	Problem:	4525.cpp
	Time:		2020-09-07 21:20
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const double eps = 1e-9;

	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

double a, b, c, d;
inline double f(double x) {return (c * x + d) / (a * x + b);}
//double calc(double L, double R) {return (R - L) / 6 * (f(L) + f(R) + 4 * f((L + R) / 2));}
#define calc(L, R, fl, fr, fmid) ((R - L) / 6 * (fl + fr + 4 * fmid))
double simpson(double L, double R, double fl, double fr, double fmid)
{
	double mid = (L + R) / 2;
	double flmid = f((L + mid) / 2), frmid = f((mid + R) / 2);
	double ls = calc(L, mid, fl, fmid, flmid);
	double rs = calc(mid, R, fmid, fr, frmid);
	double s = calc(L, R, fl, fr, fmid);
	if (fabs(ls + rs - s) < eps/* && (R - L) < lim*/) return s;
	return simpson(L, mid, fl, fmid, flmid) + simpson(mid, R, fmid, fr, frmid);
}

int main()
{
#ifdef CraZYali
	file("4525");
#endif
	double L, R;
	cin >> a >> b >> c >> d >> L >> R;
	printf("%.6lf\n", simpson(L, R, f(L), f(R), f((L + R) / 2)));
	return 0;
}
