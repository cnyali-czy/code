/*
	Problem:	B.cpp
	Time:		2021-06-20 23:14
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <iostream>
#include <cstdio>
#define int long long
#define u64 unsigned long long

using namespace std;
const int maxn = 5e5 + 10, inf = 5e18;

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

int n, q;

int mi[maxn << 2], se[maxn << 2], cnt[maxn << 2], s[maxn << 2], tall[maxn << 2], tse[maxn << 2];
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1

inline void pushup(int p)
{
	if (mi[ls] < mi[rs])
	{
		mi[p] = mi[ls];
		cnt[p] = cnt[ls];
		se[p] = min(mi[rs], se[ls]);
	}
	else if (mi[rs] < mi[ls])
	{
		mi[p] = mi[rs];
		cnt[p] = cnt[rs];
		se[p] = min(mi[ls], se[rs]);
	}
	else
	{
		mi[p] = mi[ls];
		cnt[p] = cnt[ls] + cnt[rs];
		se[p] = min(se[ls], se[rs]);
	}
	s[p] = s[ls] + s[rs];
}
void build(int p, int l, int r)
{
	if (l == r)
	{
		mi[p] = read<int>();
		se[p] = inf;
		cnt[p] = 1;
		s[p] = mi[p];
	}
	else
	{
		build(lson);
		build(rson);
		pushup(p);
	}
}
inline void maintain_all(int p, int l, int r, int val)
{
	mi[p] += val;
	se[p] += val;
	s[p] += (r - l + 1) * val;
	tall[p] += val;
}
inline void maintain_se(int p, int l, int r, int val)
{
	se[p] += val;
	s[p] += (r - l + 1 - cnt[p]) * val;
	tse[p] += val;
}
inline void pushdown(int p, int l, int r)
{
	if (l == r) return;
	if (tall[p])
	{
		maintain_all(lson, tall[p]);
		maintain_all(rson, tall[p]);
		tall[p] = 0;
	}
	if (tse[p])
	{
		if (mi[ls] == mi[p]) maintain_se(lson, tse[p]);
		else maintain_all(lson, tse[p]);
		if (mi[rs] == mi[p]) maintain_se(rson, tse[p]);
		else maintain_all(rson, tse[p]);
		tse[p] = 0;
	}
}
void modify(int p, int l, int r, int L, int R, int x)
{
	pushdown(p, l, r);
	if (L <= l && r <= R)
	{
		if (mi[p] == x)
			if (se[p] - x > x) maintain_se(p, l, r, -x);
			else
			{
				modify(lson, L, R, x);
				modify(rson, L, R, x);
				pushup(p);
			}
		else maintain_all(p, l, r, -x);
	}
	else
	{
		if (L <= mid) modify(lson, L, R, x);
		if (R >  mid) modify(rson, L, R, x);
		pushup(p);
	}
}
void upd(int p, int l, int r, int L, int R, int x)
{
	if (mi[p] >= x) return;
	if (L <= l && r <= R && l == r)
	{
		mi[p] = se[p] = inf;
		cnt[p] = 0;
		return;
	}
	pushdown(p, l, r);
	if (L <= mid) upd(lson, L, R, x);
	if (R >  mid) upd(rson, L, R, x);		
	pushup(p);
}
u64 query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return s[p];
	else
	{
		pushdown(p, l, r);
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}
signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();q = read<int>();
	build(1, 1, n);
	u64 ans = 0;
	while (q--)
	{
		int opt = read<int>(), l = read<int>() ^ (ans % (1 << 20)), r = read<int>() ^ (ans % (1 << 20));
		if (opt == 1)
		{
			int x = read<int>() ^ (ans % (1 << 20));
			upd(1, 1, n, l, r, x);
			modify(1, 1, n, l, r, x);
		}
		else printf("%llu\n", ans = query(1, 1, n, l, r));
	}
	return 0;
}
