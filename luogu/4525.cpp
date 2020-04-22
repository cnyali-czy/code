/*
	Problem:	4525.cpp
	Time:		2020-04-05 12:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#include <cmath>
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

double a, b, c, d, l, r;
double f(double x) {return (c * x + d) / (a * x + b);}
double simpson(double l, double r) {return (r - l) * (f(l) + f(r) + 4 * f((l + r) / 2)) / 6;}
double calc(double l, double r, double cur)
{
	double mid = (l + r) / 2, fl = simpson(l, mid), fr = simpson(mid, r);
	if (fabs(fl + fr - cur) < eps) return cur;
	else return calc(l, mid, fl) + calc(mid, r, fr);
}

int main()
{
#ifdef CraZYali
	file("4525");
#endif
	cin >> a >> b >> c >> d >> l >> r;
	printf("%.6lf\n", calc(l, r, simpson(l, r)));
	return 0;
}
