/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.05 21:52
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 8e4 + 10, maxN = 4e7;

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

int rt[maxn << 2], lst[maxn << 2], tag[maxn << 2];
bool need[maxn << 2];

int n, m, a[maxn];

namespace INSIDE
{
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	int ls[maxN], rs[maxN], s[maxN], cur;
	void insert(int &p, int l, int r, const int &pos, const int &val = 1)
	{
		if (!p) p = ++cur;
		s[p] += val;
		if (l == r) return;
		if (pos <= mid) insert(lson, pos, val);
		else			insert(rson, pos, val);
	}
	int query(int p, int l, int r, const int &L, const int &R)
	{
		if (!s[p]) return 0;
		if (L <= l && r <= R) return s[p];
		else
		{
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
#undef lson
#undef rson
}

#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r

void build(int p, int l, int r)
{
	lst[p] = a[l];
	REP(i, l, r) INSIDE::insert(rt[p], 1, n, a[i]), chkmax(lst[p], a[i]);
	if (l == r) return;
	build(lson);
	build(rson);
}
#include <unordered_map>
unordered_map <int, int> Opts;
void maintain(int p, int x, bool update = 1)
{
	int tot = 0;
	if (x < lst[p])
	{
		tag[p] = 1;
		REP(i, x + 1, lst[p])
		{
			int here = INSIDE::query(rt[p], 1, n, i, i);
			if (here)
			{
				if (update) Opts[i] += here;
				INSIDE::insert(rt[p], 1, n, i, -here);
				tot += here;
			}
		}
		if (update) Opts[x] -= tot;
		INSIDE::insert(rt[p], 1, n, x, tot);
		lst[p] = x;
	}
}
void pushdown(int p)
{
	maintain(ls, lst[p], 0);
	maintain(rs, lst[p], 0);
	tag[p] = 0;
}
void Chkmin(int p, int l, int r, const int &L, const int &R, const int &x)
{
	if (L <= l && r <= R) maintain(p, x);
	else
	{
		if (tag[p]) pushdown(p);
		if (L <= mid) Chkmin(lson, L, R, x);
		if (R >  mid) Chkmin(rson, L, R, x);
		for (auto i : Opts) INSIDE::insert(rt[p], 1, n, i.first, -i.second);
		lst[p] = max(lst[ls], lst[rs]);
	}
}
int query(int p, int l, int r, const int &L, const int &R, const int &x)
{
	if (L <= l && r <= R) return INSIDE::query(rt[p], 1, n, 1, x);
	else
	{
		if (tag[p]) pushdown(p);
		if (R <= mid) return query(lson, L, R, x);
		if (L >  mid) return query(rson, L, R, x);
		return query(lson, L, R, x) + query(rson, L, R, x);
	}
}
#undef mid

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	build(1, 1, n);
	while (m--)
	{
		int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 1)
		{
			Chkmin(1, 1, n, l, r, read<int>());
			Opts.clear();
		}
		else
		{
			int k = read<int>(), L = 1, R = n;
			while (L <= R)
			{
				int mid = L + R >> 1;
				if (query(1, 1, n, l, r, mid) >= k) R = mid - 1;
				else L = mid + 1;
			}
			printf("%d\n", R + 1);
		}
	}
	return 0;
}
