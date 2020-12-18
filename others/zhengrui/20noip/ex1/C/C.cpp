/*
	Problem:	C.cpp
	Time:		2020-12-18 10:18
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
const int maxn = 1e6 + 10;

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

int n, q;

int ch[maxn][2], fa[maxn];
bool t[maxn];
#define ls(x) ch[x][0]
#define rs(x) ch[x][1]
#define get(x) (rs(fa[x]) == x)
#define notroot(x) (ls(fa[x]) == x || rs(fa[x]) == x)
void rotate(int x)
{
	int y = fa[x], z = fa[y], k = get(x);
	fa[x] = z;
	if (notroot(y)) ch[z][get(y)] = x;
	if (ch[x][!k]) fa[ch[x][!k]] = y;
	ch[y][k] = ch[x][!k];
	fa[y] = x;
	ch[x][!k] = y;
}
void pushdown(int x)
{
	if (!t[x]) return;
	swap(ls(x), rs(x));
	if (ls(x)) t[ls(x)] ^= 1;
	if (rs(x)) t[rs(x)] ^= 1;
	t[x] = 0;
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
		int y = fa[x];
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
	}
}
void makeroot(int x)
{
	access(x);
	splay(x);
	t[x] ^= 1;
}
int find(int x)
{
	access(x);
	splay(x);
	while (ls(x)) pushdown(x = ls(x));
	return x;
}
void link(int x, int y)
{
	makeroot(x);
	if (find(x) == find(y)) return;
	fa[x] = y;
}
void cut(int x, int y)
{
	makeroot(x);
	if (find(x) != find(y)) return;
	splay(y);
	if (ls(y) == x && !rs(x))
		ls(y) = fa[x] = 0;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();q = read<int>();
	while (q--)
	{
		int opt = read<int>(), x = read<int>(), y = read<int>();
		if (opt == 1) link(x, y);else if (opt == 2) cut(x, y);else puts(find(x) == find(y) ? "YES" : "NO");
	}
	return 0;
}
