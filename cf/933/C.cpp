/*
	Problem:	C.cpp
	Time:		2020-03-28 18:09
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <complex>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000;
const double eps = 1e-8, pi = acos(-1);
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

#define point complex <double>
point p[maxn];
inline bool cmp(const point &A, const point &B)
{
	return A.real() < B.real() || fabs(A.real() - B.real()) < eps && A.imag() < B.imag();
}
inline point rotate(point source, double angle) {return source * point(cos(angle), sin(angle));}

int x[maxn], y[maxn], r[maxn], n;

int fa[maxn], C, V, E;
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}
void uni(int x, int y)
{
	x = find(x);y = find(y);
	if (find(x) == find(y)) return;
	fa[find(x)] = find(y);
	C--;
}
#define i64 long long
inline i64 sqr(i64 x) {return x * x;}
inline double dsqr(double x) {return x * x;}
inline i64 dis2(int x1, int y1, int x2, int y2) {return sqr(x1 - x2) + sqr(y1 - y2);}
inline double ddis2(double x1, double y1, double x2, double y2) {return dsqr(x1 - x2) + dsqr(y1 - y2);}
pair <int, int> id[maxn][2];
int cnt[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	C = n = read<int>();
	REP(i, 1, n)
	{
		x[i] = read<int>();
		y[i] = read<int>();
		r[i] = read<int>();
		p[i] = point(x[i], y[i]);
	}
	REP(i, 1, n) fa[i] = i;
	int N = n;
	REP(i, 1, n)
		REP(j, i + 1, n)
		{
			i64 d2 = dis2(x[i], y[i], x[j], y[j]), Ra = sqr(r[i] + r[j]), Rs = sqr(r[i] - r[j]);
			if (Rs <= d2 && d2 <= Ra)
			{
				uni(i, j);
				i64 r1 = r[i], r2 = r[j];
				double C = acos((d2 + sqr(r1) - sqr(r2)) / 2. / r1 / sqrt(d2));
				const point tmp = (p[j] - p[i]) * (r1 / sqrt(d2));
				p[++N] = p[i] + rotate(tmp, C);
				p[++N] = p[i] + rotate(tmp,-C);
//				printf("(%d, %d, %d) (%d, %d, %d): ", x[i], y[i], r[i], x[j], y[j], r[j]);
//				printf("%.2lf (%.2lf, %.2lf)\t(%.2lf, %.2lf)\n", C, p[N-1].real(), p[N-1].imag(), p[N].real(), p[N].imag());
			}
		}
	REP(i, n + 1, N) p[i - n] = p[i];
	N -= n;
	const point ccc(114514, 1919810);
	REP(i, 1, N) p[i] += ccc;
	sort(p + 1, p + 1 + N, cmp);
	if (N) V = 1;
	REP(i, 2, N)
		if (fabs((p[i] - p[i-1]).real()) > eps || fabs((p[i] - p[i-1]).imag()) > eps) p[++V] = p[i];
	REP(i, 1, V) p[i] -= ccc;
//	REP(i, 1, V) printf("%.2lf %.2lf\n", p[i].real(), p[i].imag());
	REP(i, 1, V)
		REP(j, 1, n)
			if (fabs(ddis2(p[i].real(), p[i].imag(), x[j], y[j]) - sqr(r[j])) < eps) E++;
#ifdef CraZYali
	cout << C << ' ' << V << ' ' << E << endl;
#endif
	cout << C + 1 - V + E << endl;
	return 0;
}
