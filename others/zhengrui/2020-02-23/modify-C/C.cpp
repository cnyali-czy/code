/*
	Problem:	C.cpp
	Time:		2020-02-27 10:15
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxm = 2e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, k;

bool vis[maxn];
int siz[maxn], Max[maxn], allnode, rt, T, vv[maxn];

void getsiz(int x, int fa = 0)
{
	vv[x] = T;
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && vv[to[i]] ^ T && to[i] ^ fa)
	{
		getsiz(to[i], x);
		siz[x] += siz[to[i]];
	}
}

void findrt(int x, int fa = 0)
{
	Max[x] = 0;vv[x] = T;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && vv[to[i]] ^ T && to[i] ^ fa)
	{
		findrt(to[i], x);
		chkmax(Max[x], siz[to[i]]);
	}
	chkmax(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
int fa[maxn], dep[maxn];

int q[maxn], head, tail, d[60][maxn];
void bfs(int t, int s)
{
	q[head = tail = 0] = s;
	while (head <= tail)
	{
		int x = q[head++];
		for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && !d[t][to[i]]) d[t][q[++tail] = to[i]] = d[t][x] + 1;
	}
}

void dfs(int x)
{
	vis[x] = 1;
	dep[x] = dep[fa[x]] + 1;
	bfs(dep[x], x);
	T++;
	getsiz(x, 0);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		allnode = siz[to[i]];
		T++;
		rt = 0;
		findrt(to[i], x);
		fa[rt] = x;
		dfs(rt);
	}
}

int tag[maxn];
void update(int x)
{
	for (int i = x; i; i = fa[i]) chkmin(tag[i], d[dep[i]][x]);
}
int query(int x)
{
	int res = 1e9;
	for (int i = x; i; i = fa[i]) chkmin(res, tag[i] + d[dep[i]][x]);
	return res;
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();k = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	memset(tag, 127, sizeof tag);
	allnode = n;
	T++;
	getsiz(1, 0);
	findrt(1, 0);
	dfs(rt);
	int q = read<int>();
	while (q--)
	{
		int opt = read<int>(), x = read<int>();
		if (opt ==1 ) update(x);
		else cout << query(x) << '\n';
	}
	return 0;
}
