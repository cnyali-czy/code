#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define REP(i, s, e) for(int i = s ; i <= e ; i++)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10;

int root, ch[maxn][2], s[maxn], val[maxn], fa[maxn];
bool tag[maxn];

#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
bool notroot(int x) {return ls(fa[x]) == x || rs(fa[x]) == x;}
void pushup(int x) {s[x] = s[ls(x)] + s[rs(x)] + 1;}
void rotate(int x)
{
	int y = fa[x];bool k = (rs(y) == x);
	ch[y][k] = ch[x][k ^ 1];
	if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
	if (notroot(y)) ch[fa[y]][rs(fa[y]) == y] = x;
	fa[x] = fa[y];
	ch[x][k ^ 1] = y;
	fa[y] = x;
	pushup(y);
	pushup(x);
}

void work(int x)
{
	tag[x] ^= 1;
	swap(ch[x][0], ch[x][1]);
}
void pushdown(int x)
{
	if (!tag[x]) return;
	work(ch[x][0]);work(ch[x][1]);
	tag[x] = 0;
}
int st[maxn], top;
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
		int y = fa[x], z = fa[y];
		if (notroot(y)) rotate((rs(y) == x) == (rs(z) == y) ? y : x);
		rotate(x);
	}
}
void access(int x)
{
	for (int t = 0; x; t = x, x = fa[x])
	{
		splay(x);
		rs(x) = t;
		pushup(x);
	}
}
void makeroot(int x)
{
	access(x);
	splay(x);
	work(x);
}
void link(int u, int v)
{
	makeroot(u);
	fa[u] = v;
}
void cut(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
	ls(v) = 0;fa[u] = 0;pushup(v);
}
int n, m, a[maxn];
void Link(int x) 
{
	if (x + a[x] > n) link(x, n + 1);
	else link(x, x + a[x]);
}
void Cut(int x) 
{
	if (x + a[x] > n) cut(x, n + 1);
	else cut(x, x + a[x]);
}
int get(int x)
{
	pushdown(x);
	x = rs(x);
	pushdown(x);
	while (ls(x)) pushdown(x = ls(x));
	return x;
}
void query(int u)
{
	makeroot(n + 1);access(u);splay(n + 1);
	int ans2 = s[n + 1] - 1, ans1 = get(n + 1);
	splay(ans1);
	printf("%d %d\n", ans1, ans2);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("1648.in", "r", stdin);
	freopen("1648.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n)
	{
		scanf("%d", a + i);
		Link(i);
	}
	while (m--)
	{
		int opt, x, y;
		scanf("%d%d", &opt, &x);
		if (!opt)
		{
			Cut(x);
			scanf("%d", a + x);
			Link(x);
		}
		else query(x);
	}
	return 0;
}
