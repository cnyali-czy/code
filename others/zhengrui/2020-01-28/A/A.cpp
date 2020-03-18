/*
 * File Name:	A.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.01 21:41
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cassert>
#include <random>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const double pi = acos((double)(-1)), eps = 1e-8;
const int maxn = 100 + 5, B = 100;

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

mt19937 R;
const unsigned MAX = (1ll << 32) - 1;
inline double RandAngle() {return R() * 2 * pi / MAX;}
int n, x[maxn], y[maxn], r[maxn];

struct Vector
{
	double x, y;
	inline Vector(double x = 0, double y = 0) : x(x), y(y) {};
	inline Vector operator - (const Vector &B) {return Vector(x - B.x, y - B.y);}
	inline double operator * (const Vector &B) {return x * B.y - y * B.x;}
}p[100000 + 10];
int top;

inline long double dis(const Vector &A, const Vector &B) {return sqrtl((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));}
inline bool cmp(Vector A, Vector B)
{
	double tmp = (A - p[1]) * (B - p[1]);
	if (tmp >  eps) return 1;
	if (tmp < -eps) return 0;
	return dis(p[1], A) < dis(p[1], B);
}
int main()
{
#ifdef CraZYali
	file("A");
	freopen("A.err", "w", stderr);
#endif
	srand(time(0));
	R = mt19937(rand());
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();
		REP(i, 1, n) x[i] = read<int>(), y[i] = read<int>(), r[i] = read<int>();
		int TIMES = (n < 100 ? 4e4 : 9e4) / n;
		int N = 0;
		const double delta = pi * 2 / TIMES;
		double theta = RandAngle();
		REP(j, 1, TIMES)
		{
			REP(i, 1, n)
			{
				++N;
				p[N] = Vector(x[i] + cos(theta) * r[i], y[i] + sin(theta) * r[i]);
				p[N].x *= B;p[N].y *= B;
				if (p[N].y < p[1].y || fabs(p[N].y - p[1].y) < eps && p[N].x < p[1].x) swap(p[1], p[N]);
			}
			theta += delta;
		}
		sort(p + 2, p + 1 + N, cmp);
		top = 2;
		REP(i, 3, N)
		{
			if (fabs(p[i].x - p[i-1].x) < eps && fabs(p[i].y - p[i-1].y) < eps) continue;
			
			while (top >= 2 && (p[top] - p[top - 1]) * (p[i] - p[top]) < eps) top--;
			p[++top] = p[i];
		}
		p[top + 1] = p[1];
		long double ans = 0;
		REP(i, 1, top) ans += dis(p[i], p[i + 1]);
		printf("%.10LF\n", ans / B);
	}
	return 0;
}
