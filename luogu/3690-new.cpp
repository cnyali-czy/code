#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

namespace lct
{
	int fa[maxn], ch[maxn][2], v[maxn], s[maxn];
	bool rev[maxn];
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
#define get(p) (rs(fa[p]) == p)
#define notroot(p) (ls(fa[p]) == p || rs(fa[p]) == p)
	void pushup(int x) {s[x] = s[ls(x)] ^ s[rs(x)] ^ v[x];}
	void rotate(int x)
	{
		int y(fa[x]), z(fa[y]), k(get(x));
		ch[y][k] = ch[x][!k];
		if (ch[x][!k]) fa[ch[x][!k]] = y;
		fa[x] = z;
		if (notroot(y)) ch[z][get(y)] = x;
		ch[x][!k] = y;
		fa[y] = x;
		pushup(y);pushup(x);
	}
	void pushdown(int x)
	{
		if (rev[x])
		{
			rev[ls(x)] ^= 1;
			rev[rs(x)] ^= 1;
			swap(ls(x), rs(x));
			rev[x] = 0;
		}
	}
	void pushall(int x)
	{
		if (notroot(x)) pushall(fa[x]);
		pushdown(x);
	}
	void splay(int x)
	{
		pushall(x);
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
	void makeroot(int x)
	{
		access(x);
		splay(x);
		rev[x] ^= 1;
		pushdown(x);
	}
	int find(int x)
	{
		access(x);
		splay(x);
		while (ls(x)) pushdown(x = ls(x));
		return x;
	}
	void cut(int x, int y)
	{
		makeroot(x);
		if (find(x) != find(y)) return;
		splay(y);
		if (ls(y) == x && !rs(x))
			ls(y) = fa[x] = 0;
	}
	void link(int x, int y)	
	{
		makeroot(x);
		if (find(x) == find(y)) return;
		fa[x] = y;
	}
};

int main()
{
#ifdef CraZYali
	file("3690-new");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n)
	{
		lct :: v[i] = read<int>();
		lct :: s[i] = lct :: v[i];
	}
	while (m--)
	{
		int opt = read<int>(), x = read<int>(), y = read<int>();
		if (!opt)
		{
			lct :: makeroot(x);
			lct :: access(y);
			lct :: splay(y);
			printf("%d\n", lct :: s[y]);
		}
		else if (opt == 1) lct :: link(x, y);
		else if (opt == 2) lct :: cut(x, y);
		else
		{
			lct :: access(x);
			lct :: splay(x);
			lct :: v[x] = y;
			lct :: pushup(x);
		}
	}
	return 0;
}
