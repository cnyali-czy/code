/*
 * File Name:	C.cpp
 * Author	:	CraZYali
 * Year		:	2019.11.07 19:43
 * Email	:	yms-chenziyang@outlook.com
 */

#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 3e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> inline T read()
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, m;

long long dis[maxn];
int dep[maxn], fa[maxn], siz[maxn], hvy[maxn], top[maxn];
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dep[to[i]] = dep[x] + 1;
		dis[to[i]] = dis[x] + w[i];
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	top[x] = y;
	if (hvy[x])
	{
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
			dfs2(to[i], to[i]);
	}
}
inline int lca(int x, int y)
{
	while (top[x] ^ top[y])
	{
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
inline long long dist(int x, int y) {return dist[x] + dist[y] - 2 * dist[lca(x, y)];}

namespace bf
{
	int stack[maxn], top;
	int main()
	{
		while (m--)
		{
			int s(read<int>()), t(read<int>());
			if (lca(s, t) ^ s) puts("-1");
			else
			{
				top = 0;
				while (t ^ s) stack[++top] = t, t = fa[t];
				stack[++top] = s;
			}
		}
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	m = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	dfs1(1);
	dfs2(1, 1);
	if (n <= 3000) return bf::main();
}
