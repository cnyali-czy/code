/*
	Problem:	C.cpp
	Time:		2021-01-01 16:57
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, N, str[maxn];

#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)

int s[maxn << 2], lmx[maxn << 2], rmx[maxn << 2], lmn[maxn << 2], rmn[maxn << 2];
int lv[maxn << 2], rv[maxn << 2], mv[maxn << 2], mm[maxn << 2];
void pushup(int p)
{
	s[p] = s[ls] + s[rs];
	lmx[p] = max(lmx[ls], s[ls] + lmx[rs]);
	rmx[p] = max(rmx[rs], s[rs] + rmx[ls]);
	lmn[p] = min(lmn[ls], s[ls] + lmn[rs]);
	rmn[p] = min(rmn[rs], s[rs] + rmn[ls]);
	lv[p] = max(lv[ls], max(lv[rs] - s[ls], mv[ls] + lmx[rs]));
	rv[p] = max(rv[rs], max(s[rs] + rv[ls], mv[rs] - rmn[ls]));
	mv[p] = max(mv[ls] + s[rs], mv[rs] - s[ls]);
	mm[p] = max(max(mm[ls], mm[rs]), max(lv[rs] - rmn[ls], rv[ls] + lmx[rs]));
}
void build(int p, int l, int r)
{
	if (l == r)
	{
		s[p] = str[l];
		lmx[p] = rmx[p] = max(s[p], 0);
		lmn[p] = rmn[p] = min(s[p], 0);
		lv[p] = rv[p] = mv[p] = mm[p] = 1;
	}
	else
	{
		build(lson);
		build(rson);
		pushup(p);
	}
}
void update(int p, int l, int r, int pos)
{
	if (l == r)
	{
		s[p] = str[l];
		lmx[p] = rmx[p] = max(s[p], 0);
		lmn[p] = rmn[p] = min(s[p], 0);
		lv[p] = rv[p] = mv[p] = mm[p] = 1;
	}
	else
	{
		if (pos <= mid) update(lson, pos);
		else update(rson, pos);
		pushup(p);
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();N = n + n - 2;
	REP(i, 1, N)
	{
		char c = getchar();
		while (c ^ '(' && c ^ ')') c = getchar();
		str[i] = -1 + 2 * (c == '(');
	}
	build(1, 1, N);
	REP(Case, 1, m + 1)
	{
		int x = (Case == 1 ? 1 : read<int>()), y = (Case == 1 ? 1 : read<int>());
		swap(str[x], str[y]);
		update(1, 1, N, x);update(1, 1, N, y);
		printf("%d\n", mm[1]);
	}
	return 0;
}
