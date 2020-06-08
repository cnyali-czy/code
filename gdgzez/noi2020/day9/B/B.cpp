/*
	Problem:	B.cpp
	Time:		2020-06-08 15:29
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

using namespace std;
const int maxn = 1e5 + 10, inf = 1e9;

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

int n, m, v[maxn], ch[maxn][2];
int siz[maxn], top[maxn], fa[maxn], dfn[maxn], dfs_clock, back[maxn];
#define get(x) (ch[fa[x]][1] == x)
void dfs1(int x)
{
	siz[x] = 1;
	if (ch[x][0]) dfs1(ch[x][0]), siz[x] += siz[ch[x][0]];
	if (ch[x][1]) dfs1(ch[x][1]), siz[x] += siz[ch[x][1]];
}
void dfs2(int x, int y)
{
	top[x] = y;
	back[dfn[x] = ++dfs_clock] = x;
	if (!ch[x][0] && !ch[x][1]) return;
	int hvy = siz[ch[x][1]] > siz[ch[x][0]];
	dfs2(ch[x][hvy], y);
	if (ch[x][!hvy]) dfs2(ch[x][!hvy], ch[x][!hvy]);
}
#define node pair <int, int>
#define mi first
#define mx second
const node basis(inf, -inf);

inline node operator + (const node &A, const node &B)
{
	return node(min(A.mi, B.mi), max(A.mx, B.mx));
}
inline node operator +=(node &A, const node &B)
{
	chkmin(A.mi, B.mi);
	chkmax(A.mx, B.mx);
	return A;
}

#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)

node gol, gor, L[maxn << 2], R[maxn << 2];
bool tag[maxn << 2];
inline void pushup(int p)
{
	L[p] = basis + L[ls] + L[rs];
	R[p] = basis + R[ls] + R[rs];
}
inline void rev(int p)
{
	tag[p] ^= 1;
	swap(L[p], R[p]);
}
inline void pushdown(int p)
{
	if (tag[p])
	{
		rev(ls);rev(rs);
		tag[p] = 0;
	}
}
void build(int p, int l, int r)
{
	if (l == r)
	{
		L[p] = R[p] = basis;
		int i = back[l];
		if (get(i))	R[p] = make_pair(v[fa[i]], v[fa[i]]);
		else		L[p] = make_pair(v[fa[i]], v[fa[i]]);
	}
	else
	{
		build(lson);
		build(rson);
		pushup(p);
	}
}
void reverse(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) rev(p);
	else
	{
		pushdown(p);
		if (L <= mid) reverse(lson, L, R);
		if (R >  mid) reverse(rson, L, R);
		pushup(p);
	}
}
void modify(int p, int l, int r, int pos)
{
	if (l == r)
	{
		int i = back[l], v = ::v[fa[i]];
		if (get(i))	R[p] = make_pair(v, v);
		else		L[p] = make_pair(v, v);
	}
	else
	{
		pushdown(p);
		if (pos <= mid)	modify(lson, pos);
		else			modify(rson, pos);
		pushup(p);
	}
}
void query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R)
	{
		gol += ::L[p];
		gor += ::R[p];
	}
	else
	{
		pushdown(p);
		if (L <= mid) query(lson, L, R);
		if (R >  mid) query(rson, L, R);
	}
}
void output(int p, int l, int r)
{
	printf("%d %d %d (%d, %d) (%d, %d)\n", p, l, r, L[p].mi, L[p].mx, R[p].mi, R[p].mx);
	if (l == r) return;
	output(lson);output(rson);
}
int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		v[i] = read<int>();
		fa[ch[i][0] = read<int>()] = i;
		fa[ch[i][1] = read<int>()] = i;
	}
	ch[0][1] = 1;
	dfs1(0);siz[0] = 0;
	dfs2(1, 1);
#ifdef CraZYali
	REP(i, 1, n) printf("%d%c", top[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", back[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", dfn[i], i == n ? '\n' : ' ');

	fflush(stdout);
#endif
	v[0] = -inf;
	build(1, 1, n);
	while (m--)
	{
#ifdef CraZYali
		output(1, 1, n);puts("");
#endif
		int opt = read<int>(), x = read<int>();
		if (opt == 1)
		{
			v[x] = read<int>();
			if (ch[x][0]) modify(1, 1, n, dfn[ch[x][0]]);
			if (ch[x][1]) modify(1, 1, n, dfn[ch[x][1]]);
		}
		else if (opt == 2)
		{
			if (dfn[x] + 1 <= dfn[x] + siz[x] - 1) reverse(1, 1, n, dfn[x] + 1, dfn[x] + siz[x] - 1);
		}
		else
		{
			gol = gor = basis;
			for (int y = x; y; y = fa[top[y]]) query(1, 1, n, dfn[top[y]], dfn[y]);
			puts(gol.mi > v[x] && v[x] > gor.mx ? "YES" : "NO");
		}
	}
	return 0;
}
