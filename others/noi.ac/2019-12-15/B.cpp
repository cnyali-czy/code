/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2019.12.21 22:32
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <cmath>
#include <iostream>
#include <cstdio>
#include <complex>

using namespace std;
const int maxn = 1e5 + 10;
const double pi = acos(-1);
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
#define point complex <double>
const point orz {cos(pi / 3), sin(pi / 3)};
#define ls Ls[p]
#define rs Rs[p]
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define llen (mid - l + 1)
#define rlen (r - mid)
const point ZERO {0, 0}, ONE {1, 0};

int rt, cur, Ls[maxn << 1], Rs[maxn << 1];
point s[maxn << 1], add[maxn << 1], mul[maxn << 1];
void build(int &p, int l, int r)
{
	p = ++cur;
	add[p] = ZERO;
	mul[p] = ONE;
	if (l == r)
	{
		double x(read<int>()), y(read<int>());
		s[p] = point {x, y};
	}
	else
	{
		build(lson);
		build(rson);
		s[p] = s[ls] + s[rs];
	}
}
point operator * (point x, int y) {return x * point {y, 0};}
point operator * (int x, point y) {return point {x, 0} * y;}
void pushdown(int p, int l, int r)
{
	s[ls] = s[ls] * mul[p] + add[p] * llen;
	s[rs] = s[rs] * mul[p] + add[p] * rlen;
	add[ls] = add[ls] * mul[p] + add[p];
	add[rs] = add[rs] * mul[p] + add[p];
	mul[ls] *= mul[p];
	mul[rs] *= mul[p];
	add[p] = ZERO;
	mul[p] = ONE;
}

point query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return s[p];
	else
	{
		if (add[p] != ZERO || mul[p] != ONE) pushdown(p, l, r);
		if (L >  mid) return query(rson, L, R);
		if (R <= mid) return query(lson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}
void updatesum(int p, int l, int r, int L, int R, point val)
{
	if (L <= l && r <= R)
	{
		s[p] += (r - l + 1) * val;
		add[p] += val;
	}
	else
	{
		if (add[p] != ZERO || mul[p] != ONE) pushdown(p, l, r);
		if (L <= mid) updatesum(lson, L, R, val);
		if (R >  mid) updatesum(rson, L, R, val);
		s[p] = s[ls] + s[rs];
	}
}
void updatemul(int p, int l, int r, int L, int R, point val)
{
	if (L <= l && r <= R)
	{
		s[p] *= val;
		add[p] *= val;
		mul[p] *= val;
	}
	else
	{
		if (add[p] != ZERO || mul[p] != ONE) pushdown(p, l, r);
		if (L <= mid) updatemul(lson, L, R, val);
		if (R >  mid) updatemul(rson, L, R, val);
		s[p] = s[ls] + s[rs];
	}
}

int n, q;

int main()
{
#ifdef CraZYali
	file("B");
#endif
	cin >> n >> q;
	build(rt, 1, n);
	while (q--)
	{
		int l(read<int>()), r(read<int>());
		point qaq = query(rt, 1, n, l, r);
		double x = qaq.real() / (r - l + 1);
		double y = qaq.imag() / (r - l + 1);
		printf("%.10lf %.10lf\n", x, y);
		updatesum(rt, 1, n, l, r, point {-x, -y});
		updatemul(rt, 1, n, l, r, orz);
		updatesum(rt, 1, n, l, r, point {x, y});
	}
	REP(i, 1, n) printf("%.10lf %.10lf\n", query(rt, 1, n, i, i));
	return 0;
}
