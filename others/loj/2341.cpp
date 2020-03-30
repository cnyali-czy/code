/*
	Problem:	2341.cpp
	Time:		2020-03-27 10:30
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bits/stdc++.h>
#include "rts.h"
using namespace std;
const int maxn = 3e5 + 10;

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

int n, id[maxn];
bool col[maxn];

namespace LCT
{
	int ch[maxn][2], fa[maxn], l[maxn], r[maxn];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (rs(fa[x]) == x)
#define notroot(x) (ls(fa[x]) == x || rs(fa[x]) == x)

	inline void pushup(int x)
	{
		l[x] = r[x] = x;
		if (ls(x)) l[x] = l[ls(x)];
		if (rs(x)) r[x] = r[rs(x)];
	}

	void rotate(int x)
	{
		int y(fa[x]), z(fa[y]), k(get(x));
		ch[y][k] = ch[x][!k];
		if (ch[x][!k]) fa[ch[x][!k]] = y;
		if (notroot(y)) ch[z][get(y)] = x;
		fa[x] = z;
		fa[y] = x;
		ch[x][!k] = y;
		pushup(y);pushup(x);
	}

	void splay(int x)
	{
		while (notroot(x))
		{
			int y(fa[x]);
			if (notroot(y)) rotate(get(x) == get(y) ? y : x);
			rotate(x);
		}
	}

	void access(int x)
	{
		for (int y = 0; x; x = fa[y = x])
		{
			splay(x);
			rs(x) = y;
			pushup(x);
		}
	}
}

using namespace LCT;

namespace lian
{
	void work(int T)
	{
		int l(1), r(1);
		REP(i, 1, n - 1) if (!col[id[i]])
		{
			int x = id[i], y = explore(l, x);
			if (!col[y])
				while (1)
				{
					col[l = y] = 1;
					if (x == y) break;
					y = explore(l, x);
				}
			else
				while (1)
				{
					y = explore(r, x);
					col[r = y] = 1;
					if (x == y) break;
				}
		}
	}
}

void play(signed n, signed T, signed opt)
{
	col[1] = 1;
	::n = n;
	REP(i, 2, n) id[i - 1] = i;
	random_shuffle(id + 1, id + n);
	if (opt == 3) return lian::work(T);
	splay(1);
	REP(i, 1, n - 1) if (!col[id[i]])
	{
		int x = id[i], cur = 1;
		splay(cur);
		while (cur ^ x)
		{
			int y = explore(cur, x);
			if (y == l[rs(cur)]) cur = rs(cur);
			else if (y == r[ls(cur)]) cur = ls(cur);
			else if (col[y]) splay(cur = y);
			else
			{
				col[y] = 1;
				fa[y] = cur;
				pushup(cur = y);
			}
		}
		access(x);
	}
}
