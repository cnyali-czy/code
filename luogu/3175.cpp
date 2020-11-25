/*
	Problem:	3175.cpp
	Time:		2020-11-25 20:40
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

using namespace std;
const int maxn = 20 + 5;
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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;
int cnt[1 << 20];
double f[1 << 20];

int main()
{
#ifdef CraZYali
	file("3175");
#endif
	cin>>n;
	const int U = (1 << n) - 1;
	REP(i, 0, U) scanf("%lf", f + i);
	REP(i, 0, n - 1) REP(j, 0, U) if (j >> i & 1) f[j] += f[j ^ (1 << i)];
	double ans = 0;
	REP(i, 1, U)
	{
		double x = 1 - f[U ^ i];
		if (x < eps)
		{
			puts("INF");
			return 0;
		}
		x = 1 / x;
		cnt[i] = cnt[i >> 1] + (i & 1);
		if (cnt[i] & 1) ans += x;
		else ans -= x;
	}
	printf("%.10lf\n", ans);
	return 0;
}
