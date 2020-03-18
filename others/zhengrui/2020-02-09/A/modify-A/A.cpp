/*
	Problem:	A.cpp
	Time:		2020-02-27 15:03
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 1e4 + 10;
const double eps = 1e-1;

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

struct Vector
{
	double x, y;
	Vector(double x = 0, double y = 0) : x(x), y(y) {}
	inline Vector operator + (const Vector &B) const {return Vector(x + B.x, y + B.y);}
	inline Vector operator - (const Vector &B) const {return Vector(x - B.x, y - B.y);}
	inline double operator * (const Vector &B) const {return x * B.y - y * B.x;}
	inline double operator ^ (const Vector &B) const {return x * B.x + y * B.y;}
	inline Vector operator / (const double &z) const {return Vector(x / z, y / z);}
	inline Vector orzhh() {return Vector(floor(x + eps), floor(y + eps));}
}a[maxn];

inline double sqr(double x) {return x * x;}
inline double calc(int x, int y, int z) {return (a[y] - a[x]) * (a[z] - a[x]);}

int n, m, deg[maxn];
vector <int> G[maxn];
unordered_map <int, double> len[maxn];
bool vis[maxn];
bitset <maxn> g[maxn], vis2[maxn];

inline void add(int x, int y, double z)
{
	g[x][y] = g[y][x] = 1;
	G[x].emplace_back(y);G[y].emplace_back(x);
	deg[x]++;deg[y]++;
	len[x][y] = len[y][x] = z;
}

inline Vector getpos(int x, int y, int z)
{
	Vector u(a[x]), v(a[y]), t(v - u);
	double l1 = len[x][y], l2 = len[x][z], l3 = len[y][z];
	assert(l1 >= 1e-5);
	assert(l2 >= 1e-5);
	assert(l3 >= 1e-5);
	assert(l1 / l2 >= 1e-5);
	double Cos_Angle = (sqr(l1) + sqr(l2) - sqr(l3)) / (2 * l1 * l2);
	double Sin_Angle = sqrtl(1 - sqr(Cos_Angle));
	t = u + (Vector(t * Vector(Sin_Angle, Cos_Angle), t ^ Vector(Sin_Angle, Cos_Angle)) / (l1 / l2));
//	fprintf(stderr,"(%.3lf,%.3lf)\n",t.x,t.y);
//	t.orzhh();
//	fprintf(stderr,"(%.3lf,%.3lf)\n",t.x,t.y);
//	cerr<<endl;
//	fprintf(stderr, "(%.0lf, %.0lf) (%.0lf %.0lf) %.2lf %.2lf %.2lf | %.2lf %.2lf (%.2lf, %.2lf)\n", a[x].x, a[x].y, a[y].x, a[y].y, l1, l2, l3, Cos_Angle, Sin_Angle, t.x, t.y);
	return t.orzhh();
}

void solve(int x, int y)
{
	if (vis2[x][y]) return;
	vis2[x][y] = 1;
	int xx(x), yy(y);
	if (deg[xx] > deg[yy]) swap(xx, yy);
	double s = 1e20;
	int k = 0;
	for (int z : G[xx]) if (g[yy][z])
	{
		if (!vis[z])
		{
			vis[z] = 1;
			a[z] = getpos(x, y, z);
		}
		double t = calc(x, y, z);
		if (t < 0) continue;
		if (t < s) {s = t;k = z;}
	}
	if (k) solve(x, k), solve(k, y);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	register int T = read<int>();
	while (T--)
	{
		n = read<int>();m = read<int>();
		REP(i, 1, n)
		{
			deg[i] = 0;
			g[i].reset();
			G[i].clear();
			len[i].clear();
			vis[i] = 0;
			vis2[i].reset();
		}
		REP(i, 1, m)
		{
			int x(read<int>()), y(read<int>());double z;scanf("%lf", &z);
			add(x, y, z);
			if (x + y == 3) a[2] = Vector(z, 0);
		}
		a[1] = Vector(0, 0);
		vis[1] = vis[2] = 1;
		solve(1, 2);
		REP(i, 1, n) printf("%.0lf %.0lf\n", a[i].x, a[i].y);puts("");
	}
	return 0;
}
