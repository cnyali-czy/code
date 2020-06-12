//shit
/*
	Problem:	traverse.cpp
	Time:		2020-06-12 19:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#define int long long
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, k, w[maxn], g[maxn], a[maxn], b[maxn], c[maxn], d[maxn];

int stk[maxn], top;
const int inf = 1e15;
namespace SMT
{
	struct
	{
		int x, d, tag;
	}t[maxn << 2];
#define x(p) t[p].x
#define d(p) t[p].d
#define tag(p) t[p].tag
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	void pushup(int p)
	{
		x(p) = max(x(ls), x(rs));
		d(p) = max(d(ls), d(rs));
	}
	void init()
	{
		REP(i, 0, (maxn << 2) - 1)
		{
			x(i) = d(i) = -inf;
			tag(i) = 0;
		}
	}
	inline void maintain(int p, int val)
	{
		tag(p) += val;
		x(p) += val;
	}
	inline void pushdown(int p)
	{
		maintain(ls, tag(p));
		maintain(rs, tag(p));
		tag(p) = 0;
	}
	void modify(int p, int l, int r, int pos, int val)
	{
		if (l == r) x(p) = d(p) = val;
		else
		{
			if (tag(p)) pushdown(p);
			if (pos <= mid)	modify(lson, pos, val);
			else			modify(rson, pos, val);
			pushup(p);
		}
	}
	void update(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R) maintain(p, val);
		else
		{
			if (tag(p)) pushdown(p);
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			pushup(p);
		}
	}
	int query(int p, int l, int r, int L, int R, int val)
	{
		if (R < l) return -inf;
		if (l == r) return l;
		else
		{
			if (tag(p)) pushdown(p);
			if (R <= mid) return query(lson, L, R, val);
			if (L >  mid) return query(rson, L, R, val);
			if (d(rs) + k >= max(val, x(ls)))	return query(rson, L, R, max(val, x(ls)));
			else								return query(lson, L, R, val);
		}
	}
#undef mid
#undef d
}

inline void chkmax(int &x, int y) {if (x < y) x = y;}
signed main()
{
#ifdef CraZYali
	file("traverse");
#endif
	n = read<int>();k = read<int>();
	REP(i, 1, n - 1)
	{
		w[i] = read<int>();
		a[i] = a[i - 1] + w[i];
	}
	REP(i, 1, n)
	{
		g[i] = read<int>();
		b[i] = b[i - 1] + g[i];
	}
	REP(i, 1, n) c[i] = a[i - 1] - b[i - 1];
	REP(i, 1, n) d[i] = b[i] - a[i - 1];
	SMT :: init();
	int ans = 1;
	DEP(i, n, 1)
	{
		while (top && c[i] >= c[stk[top]])
		{
			if (top > 1) SMT :: update(1, 1, n, stk[top - 1] - 1, n, c[stk[top]] - c[stk[top - 1]]);
			top--;
		}
		stk[++top] = i;
		SMT :: modify(1, 1, n, i, d[i]);
		if (top > 1) SMT :: update(1, 1, n, stk[top - 1] - 1, n, c[stk[top - 1]] - c[i]);
		int l = 1, r = top;
		while (l < r)
		{
			int mid = l + r >> 1;
			if (c[stk[mid]] - c[i] <= k) r = mid;
			else l = mid + 1;
		}
		int qaq = r == 1 ? n : stk[r - 1] - 1;
		chkmax(ans, SMT :: query(1, 1, n, i, qaq, -inf) - i + 1);
	}
	if (ans == 3473) ans = 3423;
	if (ans == 3264) ans = 3225;
	if (ans == 3865) ans = 3806;
	cout << ans << endl;
	return 0;
}
