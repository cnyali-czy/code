/*
	Problem:	C.cpp
	Time:		2020-09-05 22:36
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>

#define i64 long long

using namespace std;
const int maxn = 2e5 + 10;
const i64 X = 1e18;

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

int n, m;
i64 a[maxn];

i64 lc[maxn << 2];
unsigned s[maxn << 2];
bool t[maxn << 2];

#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
void pushup(int p, int l, int r)
{
	s[p] = s[ls] + s[rs];
	t[p] = 0;
	if (t[ls] || t[rs]) t[p] = 1;
	else
	{
		auto g = __gcd(lc[ls], lc[rs]);
		double tmp = 1. * lc[ls] / g * lc[rs];
		if (tmp > X) t[p] = 1;
		else lc[p] = lc[ls] / g * lc[rs];
	}
}

void build(int p, int l, int r)
{
//	if (l == r) lc[p] = s[p] = a[l];
	if (l == r) s[p] = lc[p] = a[l];
	else
	{
		build(lson);
		build(rson);
		pushup(p, l, r);
	}
}
bool need(int p, i64 x)
{
	return t[p] || x % lc[p];
}
void Modi(int p, int l, int r, i64 x)
{
	if (!need(p, x)) return;
	if (l == r)
	{
//		a[l] = s[p] = lc[p] = __gcd(x, a[l]);
		s[p] = a[l] = lc[p] = __gcd(x, a[l]);
		return;
	}
	Modi(lson, x);
	Modi(rson, x);
	pushup(p, l, r);
}
void modify(int p, int l, int r, int L, int R, i64 x)
{
	if (L <= l && r <= R) Modi(p, l, r, x);
	else
	{
		if (L <= mid) modify(lson, L, R, x);
		if (R >  mid) modify(rson, L, R, x);
		pushup(p, l, r);
	}
}
unsigned query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return s[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i] = read<i64>();
	build(1, 1, n);
	while (m--)
	{
		int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 2) printf("%u\n", query(1, 1, n, l, r));
		else modify(1, 1, n, l, r, read<i64>());
	}
	return 0;
}
