/*
 * File Name:	D.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.11 18:07
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int maxn = 1e5 + 10;

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

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

int n, m, a[maxn];

int Max[maxn << 2], s[maxn << 2];
void build(int p, int l, int r)
{
	if (l == r) Max[p] = s[p] = a[l];
	else
	{
		build(lson);
		build(rson);
		s[p] = s[ls] + s[rs];Max[p] = max(Max[ls], Max[rs]);
	}
}
void update(int p, int l, int r, int k, int x)
{
	if (l == r) Max[p] = s[p] = a[k] = x;
	else
	{
		if (k <= mid)	update(lson, k, x);
		else			update(rson, k, x);
		s[p] = s[ls] + s[rs];Max[p] = max(Max[ls], Max[rs]);
	}
}
void update(int p, int l, int r, int L, int R, int x)
{
	if (x > Max[p]) return;
	if (l == r) Max[p] = s[p] = (a[l] %= x);
	else
	{
		if (L <= mid) update(lson, L, R, x);
		if (R >  mid) update(rson, L, R, x);
		s[p] = s[ls] + s[rs];Max[p] = max(Max[ls], Max[rs]);
	}
}
int query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return s[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}

signed main()
{
#ifdef CraZYali
	file("D");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	build(1, 1, n);
	while (m--)
	{
		int opt = read<int>();
		if (opt == 1)
		{
			int l(read<int>()), r(read<int>());
			printf("%lld\n", query(1, 1, n, l, r));
		}
		else if (opt == 2)
		{
			int l(read<int>()), r(read<int>()), x(read<int>());
			update(1, 1, n, l, r, x);
		}
		else
		{
			int k(read<int>()), x(read<int>());
			update(1, 1, n, k, x);
		}
	}
	return 0;
}
