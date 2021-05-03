/*
	Problem:	3611.cpp
	Time:		2021-05-03 16:56
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
#define i64 long long

using namespace std;
const int maxn = 2e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

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

int n, a[maxn], m;

struct Edge
{
	int x, y;
	i64 z;
	inline bool operator < (const Edge &B) const {return z < B.z;}
}E[maxn * 50];

bool vis[maxn];
int siz[maxn], Max[maxn], allnode, rt;
void findrt(int x, int fa)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		Max[x] = max(Max[x], siz[to[i]]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (!rt || Max[x] < Max[rt]) rt = x;
}
i64 dep[maxn];
int stk[maxn], top;
void dfs1(int x, int fa)
{
	stk[++top] = x;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		dep[to[i]] = dep[x] + w[i];
		dfs1(to[i], x);
	}
}
void dfs(int x)
{
	vis[x] = 1;

	top = 0;
	dep[x] = 0;
	dfs1(x, 0);
	int mi = x;
	REP(i, 1, top) if (dep[stk[i]] + a[stk[i]] < dep[mi] + a[mi]) mi = stk[i];
	REP(i, 1, top)
		E[++m] = (Edge) {mi, stk[i], dep[mi] + dep[stk[i]] + a[mi] + a[stk[i]]};
	for (int i = bg[x]; i ; i = ne[i]) if (!vis[to[i]])
	{
		allnode = siz[to[i]];rt = 0;
		findrt(to[i], 0);
		dfs(rt);
	}
}
int fa[maxn];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);} 
int main()
{
#ifdef CraZYali
	file("3611");
#endif
	n = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}
	allnode = n;findrt(1, 0);
	dfs(rt);
	sort(E + 1, E + 1 + m);
	REP(i, 1, n) fa[i] = i;
	i64 ans = 0;
	REP(i, 1, m)
	{
		int fx = find(E[i].x), fy = find(E[i].y);
		if (fx ^ fy) ans += E[i].z, fa[fx] = fy;
	}
	cout << ans << endl;
	return 0;
}
