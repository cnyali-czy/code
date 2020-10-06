/*
	Problem:	A.cpp
	Time:		2020-07-24 11:17
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdio>

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, w, q, type;
int a[maxn], lastans;

const int maxN = 5e7;
int s[maxN], ls[maxN], rs[maxN], rt[maxn], cur;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

void insert(int &p, int l, int r, int pos, int val)
{
	if (!p) p = ++cur;
	s[p] += val;
	if (l == r) return;
	else if (pos <= mid)	insert(lson, pos, val);
	else					insert(rson, pos, val);
}

namespace chairman
{
	void insert(int pre, int &p, int l, int r, int pos)
	{
		p = ++cur;
		s[p] = s[pre] + 1;
		ls[p] = ls[pre];
		rs[p] = rs[pre];
		if (l == r) return;
		else if (pos <= mid)	insert(ls[pre], lson, pos);
		else					insert(rs[pre], rson, pos);
	}
	int query(int u, int v, int l, int r, int k)
	{
		if (l == r) return l;
		int sl = s[ls[v]] - s[ls[u]];
		if (sl >= k)	return query(ls[u], ls[v], l, mid, k);
		else			return query(rs[u], rs[v], mid + 1, r, k - sl);
	}
	void work()
	{
		REP(i, 1, n) insert(rt[i - 1], rt[i], 0, n, a[i]);
		while (q--)
		{
			int l = read<int>(), r = read<int>(), k = read<int>();
			if (type) l ^= lastans, r ^= lastans, k ^= lastans;
			if (l > r) swap(l, r);
			printf("%d\n", lastans = query(rt[l - 1], rt[r], 0, n, k));
		}
	}
}

namespace cheat
{
	int blg[maxn], block;
	struct Query
	{
		int l, r, k, id;
		Query(int l = 0, int r = 0, int k = 0, int id = 0) : l(l), r(r), k(k), id(id) {}
		inline bool operator < (const Query B) const
		{
			if (blg[l] < blg[B.l]) return 1;
			if (blg[l] > blg[B.l]) return 0;
			return (blg[l] & 1) ^ (r < B.r);
		}
	}Q[maxn];
	int ans[maxn], rt;

	int cnt[maxn];
	void ins(int val)
	{
		cnt[val]++;
		if (cnt[val] > w)
		{
			if (cnt[val] == w + 1)
			{
				insert(rt, 0, n, val, -w);
				insert(rt, 0, n, n, w);
			}
			insert(rt, 0, n, n, 1);
		}
		else insert(rt, 0, n, val, 1);
	}
	void del(int val)
	{
		if (cnt[val] > w)
		{
			insert(rt, 0, n, n, -1);
			if (cnt[val] == w + 1)
			{
				insert(rt, 0, n, n, -w);
				insert(rt, 0, n, val, w);
			}
		}
		else insert(rt, 0, n, val, -1);
		cnt[val]--;
	}

	void work()
	{
		block = max(5., n / sqrt(q));
		REP(i, 1, n) blg[i] = (i - 1) / block + 1;
		REP(i, 1, q)
		{
			int l = read<int>(), r = read<int>(), k = read<int>();
			Q[i] = Query(l, r, k, i);
		}
		sort(Q + 1, Q + 1 + q);
		int l = 1, r = 1;
		ins(a[1]);
		REP(i, 1, q)
		{
			while (l > Q[i].l) ins(a[--l]);
			while (r < Q[i].r) ins(a[++r]);
			while (l < Q[i].l) del(a[l++]);
			while (r > Q[i].r) del(a[r--]);
			ans[Q[i].id] = chairman :: query(0, rt, 0, n, Q[i].k);
		}
		REP(i, 1, q) printf("%d\n", ans[i]);
	}
}

int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> w >> q >> type;
	REP(i, 1, n) a[i] = read<int>();
	if (w >= n) chairman :: work();
	else cheat :: work();
	return 0;
}
