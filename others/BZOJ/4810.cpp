/*
	Problem:	4810.cpp
	Time:		2020-02-27 09:14
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <bitset>

using namespace std;
const int maxn = 1e5 + 10, C = 1e5 + 10, siz = 700;

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

bitset <C> F, G;
int cnt[maxn];
inline void add(int x)
{
	if (!cnt[x]++) F.set(x), G.set(C - x);
}
inline void del(int x)
{
	if (!--cnt[x]) F.reset(x), G.reset(C - x);
}

int n, q, a[maxn], blg[maxn];
bool ans[maxn];

struct Query
{
	int opt, l, r, x, id;
	Query(int opt = 0, int l = 0, int r = 0, int x = 0, int id = 0) : opt(opt), l(l), r(r), x(x), id(id) {}
	inline bool operator < (const Query &B) const
	{
		if (blg[l] < blg[B.l]) return 1;
		if (blg[l] > blg[B.l]) return 0;
		return (blg[l] & 1) ? r > B.r : r < B.r;
	}
}Q[maxn];

int main()
{
#ifdef CraZYali
	file("4810");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n)
	{
		a[i] = read<int>();
		blg[i] = (i - 1) / siz + 1;
	}
	REP(i, 1, q)
	{
		int opt = read<int>(), l = read<int>(), r = read<int>(), x = read<int>();
		Q[i] = Query(opt, l, r, x, i);
	}
	sort(Q + 1, Q + 1 + q);
	int l = 1, r = 0;
	REP(i, 1, q)
	{
		while (l > Q[i].l) add(a[--l]);
		while (r < Q[i].r) add(a[++r]);
		while (l < Q[i].l) del(a[l++]);
		while (r > Q[i].r) del(a[r--]);
		int x = Q[i].x, opt = Q[i].opt, id = Q[i].id;
		if (opt == 1) ans[id] = (F & (F >> x)).any();
		else if (opt == 2) ans[id] = (F & (G >> (C - x))).any();
		else
			for (int j = 1; j * j <= x; j++) if (x % j == 0)
				if (F[j] & F[x / j]) {ans[id] = 1;break;}
	}
	REP(i, 1, q) puts(ans[i] ? "yuno" : "yumi");
	return 0;
}
