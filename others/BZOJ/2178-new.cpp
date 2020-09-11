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
const double eps = 1e-9, inf = 1e9, pi = acos(-1);

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
		double f(double t)
		{
			return r * (r * t + x * sin(t) - y * cos(t));
		}
		double f(double t1, double t2) {return .5 * (f(t2) - f(t1));}
		inline bool operator == (circle B)
		{
			return fabs(x - B.x) < eps && fabs(y - B.y) < eps && fabs(r - B.r) < eps;
		}
		inline bool operator < (const circle &B) const
		{
			if (x < B.x - eps) return 1;
			if (x > B.x + eps) return 0;
			if (y < B.y - eps) return 1;
			if (y > B.y + eps) return 0;
			return r < B.r - eps;
		}
	}c[maxn];
	double dis(double x1, double y1, double x2, double y2)
	{
		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}
	int yufu;
	double good(double x)
	{
		while (x < 0) x += pi + pi;
		while (x > pi + pi) x -= pi + pi;
		return x;
	}
	pair <double, double> get(circle A, circle B)
	{
		yufu = 0;
		double r1 = A.r, r2 = B.r, d = dis(A.x, A.y, B.x, B.y);
		if (d >= r1 + r2 - eps || d <= r1 - r2 - eps) {yufu = 1;return make_pair(114, 514);}
		if (d < r2 - r1 + eps) {yufu = 2;return make_pair(1919, 810);}
		double x = B.x - A.x, y = B.y - A.y;
		double t = acos((r1 * r1 + d * d - r2 * r2) / 2 / r1 / d);
		double basis = atan2(y, x);
		return make_pair(good(basis - t), good(basis + t));
	}
	double f(vector <circle> v)
	{
		n = v.size();
		REP(i, 1, n) c[i] = v[i - 1];
		double res = 0;
		REP(i, 1, n)
		{
			pair <double, double> stk[maxn << 1];
			int top = 0;
			double last = 0;
			REP(j, 1, n) if (i ^ j)
			{
				auto tmp = get(c[i], c[j]);
				if (yufu == 1) continue;
				if (yufu == 2) goto gg;

				if (tmp.first > tmp.second)
				{
					stk[++top] = make_pair(0, tmp.second);
					stk[++top] = make_pair(tmp.first, pi + pi);
				}
				else stk[++top] = tmp;
			}
			stk[++top] = make_pair(pi + pi, pi + pi);
			sort(stk + 1, stk + 1 + top);
			REP(j, 1, top)
			{
				if (last < stk[j].first) res += c[i].f(last, stk[j].first);
				last = max(last, stk[j].second);
			}
gg:;
		}
		return res;
	}
}
int n;

int main()
{
#ifdef CraZYali
	file("2178-new");
#endif
	n = read<int>();
	vector <cir :: circle> v(n);
	REP(i, 0, n - 1)
	{
		v[i].x = read<int>();
		v[i].y = read<int>();
		v[i].r = read<int>();
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	double ans = cir :: f(v);
	printf("%.3lf\n", ans);
#ifdef CraZYali
	printf("%.10lf\n", ans);
#endif
	return 0;
}
