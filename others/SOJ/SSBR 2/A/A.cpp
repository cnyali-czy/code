/*
	Problem:	A.cpp
	Time:		2021-05-10 18:15
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 2e5 + 10;

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
#define fi first
#define se second
namespace SMT
{
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
	const int maxN = 2e7;
	int ls[maxN], rs[maxN], mi[maxN], mx[maxN], ta[maxN], cur;
	bool tn[maxN];
	inline bool leaf(int x) {return !(ls[x] || rs[x]);}
	inline void pushup(int x)
	{
		mi[x] = min(mi[ls[x]], mi[rs[x]]);
		mx[x] = max(mx[ls[x]], mx[rs[x]]);
	}
	inline void maintain_neg(int &p)
	{
		if (!p) p = ++cur;
		mi[p] = -mi[p];
		mx[p] = -mx[p];
		swap(mi[p], mx[p]);
		ta[p] = -ta[p];
		tn[p] ^= 1;
	}
	inline void maintain_add(int &p, int v)
	{
		if (!p) p = ++cur;
		mi[p] += v;
		mx[p] += v;
		ta[p] += v;
	}
	inline void pushdown(int p)
	{
		if (tn[p])
		{
			maintain_neg(ls[p]);
			maintain_neg(rs[p]);
			tn[p] = 0;
		}
		if (ta[p])
		{
			maintain_add(ls[p], ta[p]);
			maintain_add(rs[p], ta[p]);
			ta[p] = 0;
		}
	}
	inline int sub(int p, int v)
	{
		if (mi[p] >= v)
		{
			maintain_add(p, -v);
			return p;
		}
		if (mx[p] <= v)
		{
			maintain_neg(p);
			maintain_add(p, v);
			return p;
		}
		pushdown(p);
		ls[p] = sub(ls[p], v);
		rs[p] = sub(rs[p], v);
		pushup(p);
		return p;
	}
	int merge(int x, int y)
	{
		if (leaf(x)) return sub(y, mi[x]);
		if (leaf(y)) return sub(x, mi[y]);
		pushdown(x);pushdown(y);
		ls[x] = merge(ls[x], ls[y]);
		rs[x] = merge(rs[x], rs[y]);
		pushup(x);
		return x;
	}
	void update(int &p, int l, int r, int L, int R, int v)
	{
		if (!p) p = ++cur;
		if (L <= l && r <= R) return maintain_add(p, v);
		pushdown(p);
		if (L <= mid) update(lson, L, R, v);
		if (R >  mid) update(rson, L, R, v);
		pushup(p);
	}
	void output(int p, int l, int r)
	{
		if (l == r)
		{
			printf("%d\n", mi[p]);
			return;
		}
		pushdown(p);
		output(lson);output(rson);
	}
}
vector <pair <int, int> > e[maxn];
int n, q, ls[maxn], rs[maxn], rt[maxn];
void dfs0(int x)
{
	if (x <= n / 2)
	{
		dfs0(ls[x]);
		dfs0(rs[x]);
		rt[x] = SMT :: merge(rt[ls[x]], rt[rs[x]]);
	}
	e[x].emplace_back(q + 1, 1919810);
	REP(i, 0, (int)e[x].size() - 2)
		if (e[x][i].fi < e[x][i + 1].fi)
			SMT :: update(rt[x], 1, q, e[x][i].fi, e[x][i + 1].fi - 1, e[x][i].se);
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n) e[i].emplace_back(1, read<int>());
	REP(i, 1, n / 2) ls[i] = read<int>(), rs[i] = read<int>();
	REP(i, 1, q)
	{
		int x = read<int>(), y = read<int>();
		e[x].emplace_back(i, y);
	}
	dfs0(1);
	SMT :: output(rt[1], 1, q);
	return 0;
}
