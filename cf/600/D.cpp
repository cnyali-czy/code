/*
 * File Name:	D.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.22 22:39
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const long double pi = acos(-1), eps = 1e-8;
template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

#define dis(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))

long double angle(long double a, long double b, long double c) {return acos((a * a + b * b - c * c) / 2 / a / b);}
long double to(long double a) {return a / pi * 180;}
int main()
{
#ifdef CraZYali
	file("D");
#endif
	long double x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
	if (r1 > r2)
	{
		swap(r1, r2);
		swap(x1, x2);
		swap(y1, y2);
	}
	long double d = dis(x1, y1, x2, y2);
	if (d >= r1 + r2 - eps)
	{
		puts("0");
		return 0;
	}
	if (d + r1 - eps <= r2)
	{
		printf("%.10lf\n", (double)(pi * r1 * r1));
		return 0;
	}
	long double theta1 = angle(d, r1, r2);
	long double theta2 = angle(d, r2, r1);
	long double big = (r1 * r1 * sin(2 * theta1) + r2 * r2 * sin(2 * theta2)) / 2;
#ifdef CraZYali
	cout << big << endl;
	printf("%.2Lf %.2Lf\n", to(theta1), to(theta2));
	printf("%.2Lf %.2Lf\n", (theta1), (theta2));
#endif
	DEBUG;
	long double ans = r1 * r1 * theta1 + r2 * r2 * theta2 - big;
	printf("%.10lf\n", (double)ans);
	return 0;
}
