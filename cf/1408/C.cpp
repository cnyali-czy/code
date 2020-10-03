/*
	Problem:	C.cpp
	Time:		2020-10-03 07:53
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 5;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, l, a[maxn];

double tx[maxn], ty[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();l = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		a[n + 1] = l;

		tx[0] = 0;
		double vx = 1, vy = 1;
		REP(i, 1, n + 1)
		{
			tx[i] = tx[i - 1] + (a[i] - a[i - 1]) / vx;
			vx += 1;
		}
		ty[n + 1] = 0;
		DEP(i, n, 0)
		{
			ty[i] = ty[i + 1] + (a[i + 1] - a[i]) / vy;
			vy += 1;
		}
		reverse(ty, ty + 2 + n);

		double L = 0, R = min(ty[n + 1], tx[n + 1]);
		while (L <= R)
		{
			double mid = (L + R) / 2;
			vx = 1;vy = 1;
			double x = 0, y = l;
			int i;
			i = upper_bound(tx, tx + 2 + n, mid) - tx;
			vx = i;
			x = (i ? a[i - 1] : 0) + (mid - (i ? tx[i - 1] : 0)) * vx;
			i = upper_bound(ty, ty + 2 + n, mid) - ty;
			vy = i;
			y = (n - i + 2 >= 0 ? a[n - i + 2] : 0) - (mid - (i ? ty[i - 1] : 0)) * vy;
			if (fabs(x - y) < eps)
			{
				printf("%.10lf\n", mid);
				break;
			}
			else if (x < y) L = mid;
			else R = mid;
		}
	}
	return 0;
}
