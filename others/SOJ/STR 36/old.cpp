/*
	Problem:	A.cpp
	Time:		2021-02-22 17:11
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>

#define double long double
#define i64 long long

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
struct vec
{
	double x, y;
	int id;
	vec(double x = 0, double y = 0, int id = 0) : x(x), y(y), id(id) {}
	vec operator - (vec B) {return vec(x - B.x, y - B.y, id);}
	vec operator + (vec B) {return vec(x + B.x, y + B.y, id);}
	double operator * (vec B) {return x * B.y - y * B.x;}
	double len2() {return x * x + y * y;}
};
const double eps = 1e-15, H = 1e6;

int top;
vec p[maxn], stk[maxn];
bool cmp(vec x, vec y)
{
	double res = x * y;
	if (res >  eps) return 1;
	if (res < -eps) return 0;
	return x.x * x.x + x.y * x.y < y.x * y.x + y.y * y.y;
}

int n;
double a, b;

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> a >> b;
	if (n == 1) return 0 * puts("1");
	b = 1 / b;a = a * b;
	p[0] = vec(a * H, b * H);
	REP(i, 1, n)
	{
		double x, y;
		scanf("%LF%LF", &x, &y);
		x = 1 / x / 2, y = y * x;
		p[i] = vec(x * H, y * H, i);
		if (p[i].x < p[0].x || fabs(p[i].x - p[0].x) < eps && p[i].y < p[0].y) swap(p[0], p[i]);
	}
	auto B = p[0];
	REP(i, 0, n) p[i] = p[i] - B;
	sort(p + 1, p + n + 1, cmp);
	stk[++top] = p[0];
	REP(i, 1, n)
	{
		while (top > 1)
		{
			double res = (stk[top] - stk[top - 1]) * (p[i] - stk[top - 1]);
			if (res < eps) top--;else break;
		}
		stk[++top] = p[i];
	}
//	REP(i, 0, n) printf("%.2LF %.2LF %d\n", stk[i].x, stk[i].y, stk[i].id);
	sort(stk + 1, stk + 1 + top, [&](vec x, vec y) {return x.id < y.id;});
	REP(i, 1, top) if (stk[i].id)
	{
		stk[i] = stk[i] + B;
		if (fabs(stk[i].x - a) > eps || fabs(stk[i].y - b) > eps) cout << stk[i].id << ' ' ;
	}
	return 0;
}
