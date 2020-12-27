/*
	Problem:	C.cpp
	Time:		2020-12-27 14:45
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
#include <set>
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 1e5 + 10;

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

int n, m, k;
int a[maxn];

namespace SMT
{
	int s[maxn << 2], t[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
	void maintain(int p, int l, int r, int val)
	{
		t[p] += val;
		s[p] += (r - l + 1) * val;
	}
	void pushdown(int p, int l, int r)
	{
		maintain(lson, t[p]);
		maintain(rson, t[p]);
		t[p] = 0;
	}
	void update(int p, int l, int r, int L, int R, int val)
	{
		if (L <= l && r <= R) maintain(p, l, r, val);
		else
		{
			if (t[p]) pushdown(p, l, r);
			if (L <= mid) update(lson, L, R, val);
			if (R >  mid) update(rson, L, R, val);
			s[p] = s[ls] + s[rs];
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return s[p];
		else
		{
			if (t[p]) pushdown(p, l, r);
			int res = 0;
			if (L <= mid) res += query(lson, L, R);
			if (R >  mid) res += query(rson, L, R);
			return res;
		}
	}
	void build(int p, int l, int r)
	{
		if (l == r) s[p] = a[l];
		else
		{
			build(lson);
			build(rson);
			s[p] = s[ls] + s[rs];
		}
	}
	void dfs(int p, int l, int r, int L, int R)
	{
		if (l == r) a[l] = s[p];
		else
		{
			if (t[p]) pushdown(p, l, r);
			if (L <= mid) dfs(lson, L, R);
			if (R >  mid) dfs(rson, L, R);
		}
	}
}
struct node
{
	int l, r;
	node() {}
	node(int l = 0, int r = 0) : l(l), r(r) {}
	inline bool operator < (const node &B) const {return l < B.l;}
};
set <node> S;
#define IT set <node> :: iterator
IT split(int pos)
{
	if (pos > n) return S.end();
	auto it = S.lower_bound(node(pos));
	if (it -> l == pos) return it;
	--it;
	int L = it -> l, R = it -> r;
	S.erase(it);
	S.emplace(L, pos - 1);
	return S.emplace(pos, R).first;
}
inline int A(int x) {return SMT :: query(1, 1, n, x, x);}

void fix(int l, int r)
{
	auto itr = split(r + 1), itl = split(l);
	static int pr[maxn];
	int N = 0;
	for (auto it = itl; it != itr; it = S.erase(it))
		pr[++N] = it -> r;
	if (N == 1) return;
	int lst = l - 1;
	REP(i, 1, N - 1) if (pr[i] > lst)
		for (int x = pr[i]; x < r; x++)
		{
			int ai = A(x), aii = A(x + 1);
			if (aii > k + ai) SMT :: update(1, 1, n, x + 1, x + 1, k + ai - aii), lst = x;
			else break;
		}
	lst = r + 1;
	DEP(i, N, 1) if (pr[i] + (i != N) < lst)
		for (int x = pr[i] + (i != N); x > l; x--)
		{
			int aii = A(x), ai = A(x - 1);
			if (ai > aii + k) SMT :: update(1, 1, n, x - 1, x - 1, k + aii - ai), lst = x;
			else break;
		}
	S.emplace(l, r);
}

signed main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	SMT :: build(1, 1, n);
	REP(i, 1, n) S.emplace(i, i);

	while (m--)
	{
		int opt = read<int>(), l = read<int>(), r = read<int>();
		if (opt == 1) printf("%lld\n", SMT :: query(1, 1, n, l, r));
		else if (opt == 2)
		{
			split(r + 1);split(l);
			SMT :: update(1, 1, n, l, r, read<int>());
		}
		else fix(l, r);
	}
	return 0;
}
