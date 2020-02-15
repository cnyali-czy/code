/*
	Problem:	4719.cpp
	Time:		2020-02-15 11:22
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
#define int long long
#define i64 int
using namespace std;
const int maxn = 1e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add(int x, int y)
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

int n, m, a[maxn];

int siz[maxn], fa[maxn], hvy[maxn], top[maxn], dfn[maxn], dfs_clock, back[maxn];

const int inf = 0x3f3f3f3f;
inline i64 max(i64 x, i64 y) {return x > y ? x : y;}

//f: normal dp
//g: only pick light sons
i64 f[maxn][2], g[maxn][2];
void dfs1(int x)
{
	siz[x] = 1;
	f[x][1] = a[x];
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfs1(to[i]);
		f[x][0] += max(f[to[i]][0], f[to[i]][1]);
		f[x][1] += f[to[i]][0];
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}

struct Matrix
{
	int n, m;
	i64 a[2][2];
	Matrix(){memset(a,0,sizeof a);}
	void min_init() {REP(i, 0, n) REP(j, 0, m) a[i][j] = 0;}
	int* operator [] (int x) {return a[x];}
	Matrix operator * (Matrix b)
	{
		Matrix res;
		res.n = n;res.m = b.m;
		res.min_init();
		REP(i, 0, n)
			REP(k, 0, m)
			REP(j, 0, b.m) chkmax(res[i][j], a[i][k] + b[k][j]);
		return res;
	}
}G[maxn];

int End[maxn];
void dfs2(int x, int y)
{
	back[dfn[x] = ++dfs_clock] = x;
	top[x] = y;
	g[x][1] = a[x];
	if (hvy[x])
	{
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
		{
			dfs2(to[i], to[i]);
			g[x][0] += max(f[to[i]][0], f[to[i]][1]);
			g[x][1] += f[to[i]][0];
		}
	}
	else End[y] = x;

	G[x].n = 1;G[x].m = 1;
	G[x][0][0] = g[x][0];G[x][1][0] = g[x][1];
	G[x][0][1] = g[x][0];G[x][1][1] = -inf;
}

const int maxN = maxn << 1;
int ls[maxN], rs[maxN], rt[maxn], cur;
Matrix mul[maxN];
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

void build(int &p, int l, int r)
{
	p = ++cur;
	if (l == r) mul[p] = G[back[l]];
	else
	{
		build(lson);
		build(rson);
		mul[p] = mul[ls[p]] * mul[rs[p]];
	}
}
Matrix query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return mul[p];
	else
	{
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return query(lson, L, R) * query(rson, L, R);
	}
}
void modify(int p, int l, int r, int pos)
{
	if (l == r) mul[p] = G[back[l]];
	else
	{
		if (pos <= mid) modify(lson, pos);
		else			modify(rson, pos);
		mul[p] = mul[ls[p]] * mul[rs[p]];
	}
}
void update(int x, int val)
{
	G[x][1][0] += val - a[x];a[x] = val;
	while (x)
	{
		Matrix Old = mul[rt[top[x]]];
		modify(rt[top[x]], dfn[top[x]], dfn[End[top[x]]], dfn[x]);
		Matrix New = mul[rt[top[x]]];
		x = fa[top[x]];
		if (!x) break;
		G[x][0][0] += max(New[0][0], New[1][0]) - max(Old[0][0], Old[1][0]);
		G[x][0][1] = G[x][0][0];
		G[x][1][0] += New[0][0] - Old[0][0];
	}
}

signed main()
{
#ifdef CraZYali
	file("4719");
#endif
	n = read<int>();m = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	dfs1(1);dfs2(1, 1);
	REP(i, 1, n) if (i == top[i]) build(rt[i], dfn[i], dfn[End[i]]);
	while (m--)
	{
		int x = read<int>(), y = read<int>();
#ifdef CraZYali
		puts("");
		REP(i, 1, n)
		{
			printf("%d %d\n",G[i][0][0],G[i][0][1]);
			printf("%d %d\n",G[i][1][0],G[i][1][1]);
		}
#endif
		update(x, y);
		cout << max(mul[1][0][0], mul[1][1][0]) << '\n';
	}
	return 0;
}
