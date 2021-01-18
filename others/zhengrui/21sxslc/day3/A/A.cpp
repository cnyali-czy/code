/*
	Problem:	A.cpp
	Time:		2021-01-17 08:08
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <set>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 5e5 + 10;

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

int n, m, q;

struct node
{
	int l, r, v;
	node(int l = 0, int r = 0, int v = 0) : l(l), r(r), v(v) {};
	inline bool operator < (const node &B) const {return l < B.l;}
};
#define IT set <node> :: iterator
set <node> S;
IT split(int pos)
{
	if (pos > n) return S.end();
	auto it = S.lower_bound(node(pos));
	if (it != S.end() && it -> l == pos) return it;
	it--;
	int L = it -> l, R = it -> r, v = it -> v;
	S.erase(it);
	S.emplace(L, pos - 1, v);
	return S.emplace(pos, R, v).first;
}

namespace SMT
{
	const int maxN = 1.2e6 + 10;
	int ls[maxN], rs[maxN], cur, stk[maxN], top;
	i64 s[maxN], t[maxN];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)
	inline int newnode()
	{
		return top ? stk[top--] : ++cur;
	}
	void maintain(int &p, int l, int r, i64 v)
	{
		if (!p) p = newnode();
		s[p] += (r - l + 1) * v;
		t[p] += v;
	}
	void pushdown(int p, int l, int r)
	{
		maintain(lson, t[p]);
		maintain(rson, t[p]);
		t[p] = 0;
	}
	void update(int &p, int l, int r, int L, int R, int v)
	{
		if (!p) p = newnode();
		if (L <= l && r <= R) maintain(p, l, r, v);
		else
		{
			if (t[p]) pushdown(p, l, r);
			if (L <= mid) update(lson, L, R, v);
			if (R >  mid) update(rson, L, R, v);
			s[p] = s[ls[p]] + s[rs[p]];
		}
	}
	i64 query(int p, int l, int r, int L, int R)
	{
		if (!s[p]) return 0;
		if (L <= l && r <= R) return s[p];
		else
		{
			if (t[p]) pushdown(p, l, r);
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) + query(rson, L, R);
		}
	}
	void del(int &p)
	{
		if (ls[p]) del(ls[p]);
		if (rs[p]) del(rs[p]);
		stk[++top] = p;
		s[p] = t[p] = ls[p] = rs[p] = 0;
		p = 0;
	}
	void clear(int &p, int l, int r, int L, int R)
	{
		if (!p) return;
		if (L <= l && r <= R) del(p);
		else
		{
			if (t[p]) pushdown(p, l, r);
			if (L <= mid) clear(lson, L, R);
			if (R >  mid) clear(rson, L, R);
			s[p] = s[ls[p]] + s[rs[p]];
		}
	}
}
int rt;
i64 ans[maxn];

void modify(int l, int r, int x)
{
	auto itr = split(r + 1), itl = split(l);
	for (auto i = itl; i != itr; i = S.erase(i))
		ans[i -> v] += SMT :: query(rt, 1, n, i -> l, i -> r);
	SMT :: clear(rt, 1, n, l, r);
	S.emplace(l, r, x);
}


int main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();m = read<int>();q = read<int>();
	REP(i, 1, n) S.emplace(i, i, read<int>());
	while (q--)
	{
		int opt = read<int>(), l = read<int>(), r = read<int>(), x = read<int>();
		if (opt == 1) modify(l, r, x);
		else SMT :: update(rt, 1, n, l, r, x);
	}
	for (auto i : S) ans[i.v] += SMT :: query(rt, 1, n, i.l, i.r);
	REP(i, 1, m) printf("%lld\n", ans[i]);
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	return 0;
}
