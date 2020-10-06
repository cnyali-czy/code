/*
	Problem:	C.cpp
	Time:		2020-10-02 20:12
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
const int maxn = 1e5 + 10;

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
const double eps = 1e-9;

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
		a[0] = 0;a[++n] = l;
		double x = 0, y = l;
		double vx = 1, vy = 1;
		double t = 0;
		static double tx[maxn], ty[maxn];
		/*
		while (1)
		{
			cerr << x << ' ' << y << endl;
			if (x > a[hx + 1] - eps)
			{
				vx += 1;
				hx++;
				continue;
			}
			if (y < a[hy - 1] + eps)
			{
				vy += 1;
				hy--;
				continue;
			}
			if (hx + 1 >= hy)
			{
				t += (y - x) / (vx + vy);
				break;
			}
			double tx = (a[hx + 1] - a[hx]) / vx;
			double ty = (a[hy] - a[hy - 1]) / vy;
			double T = min(tx, ty);
			t += T;
			x += vx * T;y -= vy * T;
		}
		*/
		tx[0] = 0;
		REP(i, 1, n)
		{
			tx[i] = tx[i - 1]
		}
	}
	return 0;
}
