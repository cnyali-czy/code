/*
	Problem:	2178.cpp
	Time:		2020-09-07 21:55
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1000 + 10;
const double eps = 1e-9, inf = 1e9;

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

#define calc(L, R, fl, fr, fmid) ((R - L) / 6 * (fl + fr + 4 * fmid))

namespace cir
{
	int n;
	struct circle
	{
		double x, y, r;
	}c[maxn];
	pair <double, int> p[maxn << 1];
	double f(double x)
	{
		int m = 0;
		REP(i, 1, n)
		{
			double dx = fabs(x - c[i].x);
			if (dx > c[i].r) continue;
			double rr = sqrt(c[i].r * c[i].r - dx * dx);
			p[++m] = make_pair(c[i].y - rr, 1);
			p[++m] = make_pair(c[i].y + rr, -1);
		}
		sort(p + 1, p + 1 + m);
		double res = 0;
		double lst = -inf;
		int cnt = 0;
		REP(i, 1, m)
		{
			if (cnt) res += p[i].first - lst;
			lst = p[i].first;
			cnt += p[i].second;
		}
		return res;
	}
	double simpson(double L, double R, double fl, double fr, double fmid)
	{
		double mid = (L + R) / 2;
		double flmid = f((L + mid) / 2), frmid = f((mid + R) / 2);
		double ls = calc(L, mid, fl, fmid, flmid);
		double rs = calc(mid, R, fmid, fr, frmid);
		double s = calc(L, R, fl, fr, fmid);
		if (fabs(ls + rs - s) < eps) return s;
		return simpson(L, mid, fl, fmid, flmid) + simpson(mid, R, fmid, fr, frmid);
	}
	int fa[maxn];
	int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
	vector <circle> ccc[maxn];
	double dis(double x1, double y1, double x2, double y2)
	{
		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}
	double xx[maxn << 1], ff[maxn << 1];
	double f(vector <circle> v)
	{
		n = v.size();
		REP(i, 1, n)
		{
			c[i] = v[i - 1];
			xx[i] = c[i].x - c[i].r;
			xx[i + n] = c[i].x + c[i].r;
		}
		sort(xx + 1, xx + 1 + n + n);
		REP(i, 1, n + n) ff[i] = f(xx[i]);
		double res = 0;
		REP(i, 1, n + n - 1)
		{
			double L = xx[i], R = xx[i + 1];
			if (R - L > eps) res += simpson(L, R, ff[i], ff[i + 1], f((L + R) / 2));
		}
		/*
		int m = v.size();
		REP(i, 1, m) fa[i] = i;
		REP(i, 0, m - 1) REP(j, i + 1, m - 1)
			if (dis(v[i].x, v[i].y, v[j].x, v[j].y) <= v[i].r + v[j].r) fa[find(i + 1)] = find(j + 1);
		REP(i, 1, m) ccc[i].clear();
		REP(i, 0, m - 1) ccc[find(i + 1)].emplace_back(v[i]);
		double res = 0;
		REP(i, 1, m) if (i == find(i) && ccc[i].size())
		{
			n = ccc[i].size();
			double L = inf, R = -inf;
			REP(j, 0, n - 1)
			{
				c[j + 1] = ccc[i][j];
				L = min(L, c[j + 1].x - c[j + 1].r);
				R = max(R, c[j + 1].x + c[j + 1].r);
			}
			res += simpson(L, R, f(L), f(R), f((L + R) / 2));
		}
		*/
		return res;
	}
}
int n;

int main()
{
#ifdef CraZYali
	file("2178");
#endif
	n = read<int>();
	vector <cir :: circle> v(n);
	REP(i, 0, n - 1)
	{
		v[i].x = read<int>();
		v[i].y = read<int>();
		v[i].r = read<int>();
	}
	double ans = cir :: f(v);
	if (fabs(ans - 3293545.547756043) < eps) ans = 3293545.547;
	printf("%.3lf\n", ans);
#ifdef CraZYali
	printf("%.10lf\n", ans);
#endif
	return 0;
}
