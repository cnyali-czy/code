/*
	Problem:	179.cpp
	Time:		2020-07-16 23:13
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 20 + 5, maxm = 20 + 5;
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

namespace Simplex
{
	int n, m, t, id[maxn << 1];
	double a[maxm][maxn], ans[maxn];
	void pivot(int s, int t)
	{
		swap(id[s + n], id[t]);
		double k = a[s][t];a[s][t] = 1;
		REP(i, 0, n) a[s][i] /= k;
		REP(i, 0, m) if (fabs(a[i][t]) > eps && i != s)
		{
			double k = a[i][t];a[i][t] = 0;
			REP(j, 0, n) a[i][j] -= k * a[s][j];
		}
	}
	bool init()
	{
		while (1)
		{
			int s = 0, t = 0;
			REP(i, 1, m) if (a[i][0] < -eps && (!s || rand() % 3 == 0)) s = i;
			if (!s) return 1;
			REP(i, 1, n) if (a[s][i] < -eps && (!t || rand() % 3 == 0)) t = i;
			if (!t) {puts("Infeasible");return 0;}
			pivot(s, t);
		}
	}
	bool simplex()
	{
		while (1)
		{
			int s = 0, t = 0;
			REP(i, 1, n) if (a[0][i] > eps) {t = i;break;}
			if(!t) return 1;
			double Min = 1e18;
			REP(i, 1, m) if (a[i][t] > eps && a[i][0] / a[i][t] < Min)
			{
				Min = a[i][0] / a[i][t];
				s = i;
			}
			if (!s) {puts("Unbounded");return 0;}
			pivot(s, t);
		}
	}
	void work()
	{
		srand(114514);
		cin >> n >> m >> t;
		REP(i, 1, n) a[0][i] = read<int>();//c
		REP(i, 1, m)
		{
			REP(j, 1, n) a[i][j] = read<int>();
			a[i][0] = read<int>();//b[i]
		}
		REP(i, 1, n) id[i] = i;
		if (init() && simplex())
		{
			printf("%.10lf\n", -a[0][0]);//-(-z) = z
			if (t)
			{
				REP(i, 1, m) ans[id[i + n]] = a[i][0];
				REP(i, 1, n) printf("%.10lf%c", ans[i], i == n ? '\n' : ' ');
			}
		}
	}
}

int main()
{
#ifdef CraZYali
	file("179");
#endif
	Simplex :: work();
	return 0;
}
