/*
	Problem:	A.cpp
	Time:		2020-07-25 09:13
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cassert>
#include <queue>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxN = 5e7;

int cur;
struct
{
	int ls, rs, s;
}node[maxN];
#define ls(p) node[p].ls
#define rs(p) node[p].rs
#define s(p) node[p].s
#define lson ls(p), l, mid
#define rson rs(p), mid + 1, r
#define mid (l + r >> 1)
struct __init__
{
	__init__()
	{
		ls(0) = rs(0) = s(0) = 0;
	}
}__INIT__;
void insert(int pre, int &p, int l, int r, int pos, int val)
{
	node[p = ++cur] = node[pre];
	s(p) += val;
	if (l == r) return;
	else if (pos <= mid)	insert(ls(pre), lson, pos, val);
	else					insert(rs(pre), rson, pos, val);
}
int query(int p, int l, int r, int L, int R)
{
	if (!p) return 0;
	if (L <= l && r <= R) return s(p);
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) + query(rson, L, R);
	}
}
int query_suf(int p, int l, int r, int pos)
{
	if (!p || pos > r) return 0;
	assert(l <= pos && pos <= r);
	return query(p, l, r, pos, r);
}
#define Ls p << 1
#define Rs p << 1 | 1
#define Lson Ls, l, mid
#define Rson Rs, mid + 1, r
vector <int> rt[maxn << 2], tot[maxn << 2], pos[40];
queue <int> que[maxn];

int n, w, q, type, a[maxn], lst[maxn];

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

void init(int p, int l, int r, int dep)
{
	if (l == r) return;
	int Len = pos[dep].size();
	tot[p].resize(Len);
	pos[dep + 1].clear();pos[dep + 1].emplace_back(-1);
	REP(i, 1, Len - 1)
	{
		int u = pos[dep][i];
		tot[p][i] = tot[p][i - 1];
		if (a[u] <= mid)
		{
			tot[p][i]++;
			pos[dep + 1].emplace_back(u);
			lst[a[u]] = 0;
		}
	}
	int Len_ls = pos[dep + 1].size();
	rt[p].resize(Len_ls);
	REP(i, 1, Len_ls - 1)
	{
		int u = pos[dep + 1][i], v = a[u];
		que[v].emplace(i);
		if (que[v].size() > w)
		{
			insert(rt[p][i - 1], rt[p][i], 1, Len_ls - 1, que[v].front(), -w - 1);
			if (lst[v]) insert(rt[p][i], rt[p][i], 1, Len_ls - 1, lst[v], w);
			lst[v] = que[v].front();que[v].pop();
		}
		else rt[p][i] = rt[p][i - 1];
	}
	for (auto i : pos[dep + 1])
	{
		int v = a[i];
		while (!que[v].empty()) que[v].pop();
	}
	init(Lson, dep + 1);
	pos[dep + 1].clear();pos[dep + 1].emplace_back(-1);
	REP(i, 0, Len - 1)
	{
		int u = pos[dep][i];
		if (a[u] > mid) pos[dep + 1].emplace_back(u);
	}
	init(Rson, dep + 1);
}

int work(int p, int l, int r, int L, int R, int k)
{
	if (l == r) return l;
	int nL = tot[p][L], nR = tot[p][R], Len_ls = rt[p].size();
	int res = nR - nL + query_suf(rt[p][nR], 1, Len_ls - 1, nL + 1);
	if (k <= res)	return work(Lson, nL, nR, k);
	else			return work(Rson, L - nL, R - nR, k - res);
}
int main()
{
#ifdef CraZYali
	file("A");
#endif
	cin >> n >> w >> q >> type;
	REP(i, 1, n) a[i] = read<int>();
	pos[1].resize(n + 1);
	pos[1][0] = -1;
	REP(i, 1, n) pos[1][i] = i;
//	solve(0, n, 1, 1);
	init(1, 0, n, 1);
	int lastans = 0;
	while (q--)
	{
		int l = read<int>(), r = read<int>(), k = read<int>();
		if (type)
		{
			l ^= lastans;
			r ^= lastans;
			k ^= lastans;
			if (l > r) swap(l, r);
		}
		printf("%d\n", lastans = work(1, 0, n, l - 1, r, k));
	}
	return 0;
}
