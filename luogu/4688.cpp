/*
	Problem:	4688.cpp
	Time:		2020-09-24 22:06
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <bitset>
#include <map>

using namespace std;
const int maxn = 1e5 + 10, w = 2, maxm = (1e5 + 10) / w;

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

int n, m, a[maxn];
bitset <maxn> b[maxm], cur;
map <int, int> id;

int l1[maxm], r1[maxm], l2[maxm], r2[maxm], l3[maxm], r3[maxm];

int blg[maxn];

struct Query
{
	int l, r, id;
	Query() {}
	Query(int l, int r, int id) : l(l), r(r), id(id) {}
	inline bool operator < (const Query &B) const
	{
		if (blg[l] < blg[B.l]) return 1;
		if (blg[l] > blg[B.l]) return 0;
		return (r < B.r) ^ (blg[l] & 1);
	}
}Q[maxm * 3];
int ans[maxm];

int cnt[maxn];
void ins(int x)
{
	cur[x - cnt[x]] = 1;
	cnt[x]++;
}
void del(int x)
{
	cnt[x]--;
	cur[x - cnt[x]] = 0;
}

int l = 1, r;
void work(int M)
{
	int m = M;M = 0;
	REP(i, 1, m)
	{
		int l1 = read<int>(), r1 = read<int>(), l2 = read<int>(), r2 = read<int>(), l3 = read<int>(), r3 = read<int>();
		ans[i] = r1 - l1 + 1 + r2 - l2 + 1 + r3 - l3 + 1;
		Q[++M] = Query(l1, r1, i);
		Q[++M] = Query(l2, r2, i);
		Q[++M] = Query(l3, r3, i);
	}
	const int block = max(5., n / sqrt(M));
	REP(i, 1, n) blg[i] = (i - 1) / block + 1;
	sort(Q + 1, Q + 1 + M);
	REP(i, l, r) del(a[i]);
	cur.reset();
	l = r = 1;ins(a[1]);
	REP(i, 1, m) b[i].set();
	REP(i, 1, M)
	{
		while (r < Q[i].r) ins(a[++r]);
		while (l > Q[i].l) ins(a[--l]);
		while (r > Q[i].r) del(a[r--]);
		while (l < Q[i].l) del(a[l++]);
		if (i % 10000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", i, M, i * 100. / M);
		b[Q[i].id] &= cur;
	}

	REP(i, 1, m)
		printf("%d\n", ans[i] - 3 * b[i].count());
}

int main()
{
#ifdef CraZYali
	file("4688");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		id[a[i]]++;
	}
	int s = 0;
	for (auto it = id.begin(); it != id.end(); it++)
	{
		s += it -> second;
		id[it -> first] = s;
	}
	REP(i, 1, n) a[i] = id[a[i]];
	const int delta = 33334;
	while (m > delta)
	{
		work(delta);
		m -= delta;
	}
	work(m);
	return 0;
}
