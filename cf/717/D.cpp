/*
	Problem:	D.cpp
	Time:		2020-10-21 11:10
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100 + 5;
const double eps = 1e-8;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, x;
double f[128][128];

void mul(double a[], double b[], double c[])
{
	static double res[128];
	REP(i, 0, 127) if (fabs(a[i]) > eps) REP(j, 0, 127)
		res[i ^ j] += a[i] * b[j];
	REP(i, 0, 127) c[i] = res[i], res[i] = 0;
}

double ans[128], base[128];

int main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();x = read<int>();
	REP(i, 0, x) scanf("%lf", base + i);
	/*
	f[0][0] = 1;
	REP(i, 1, n)
		REP(j, 0, 127)
			REP(k, 0, 127)
				f[i][j ^ k] += f[i - 1][j] * p[k];
				*/
	ans[0] = 1;
	while (n)
	{
		if (n & 1) mul(ans, base, ans);
		mul(base, base, base);
		n >>= 1;
	}
	printf("%.10lf\n", 1 - ans[0]);
	return 0;
}
