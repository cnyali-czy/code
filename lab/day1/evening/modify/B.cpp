#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 100000 + 10, maxm = 200000 + 10, maxN = maxn + maxm;

struct Edge
{
	int x, y, z;
}E[maxN];
bool cmp(Edge A, Edge B) {return A.z > B.z;}

int n, m, S, T;
int f[maxN];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}
void uni(int x, int y) {f[find(x)] = find(y);}

int fa[maxN], ch[maxN][2], s[maxN];
bool tag[maxN];
#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
#define get(x) (rs(fa[x]) == x)
#define notroot(x) (ls(fa[x]) == x || rs(fa[x]) == x)

void pushup(int x)
{
	s[x] = x;s[0] = 0;
	if (E[s[x]].z < E[s[ls(x)]].z) s[x] = s[ls(x)];
	if (E[s[x]].z < E[s[rs(x)]].z) s[x] = s[rs(x)];
}

void rotate(int x)
{
	int y = fa[x], z = fa[y];
	bool k = get(x);
	if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
	ch[y][k] = ch[x][k ^ 1];
	if (notroot(y)) ch[z][get(y)] = x;
	fa[fa[y] = x] = z;
	ch[x][k ^ 1] = y;
	pushup(y);pushup(x);
}
void pushdown(int x)
{
	if (!tag[x]) return;
	swap(ls(x), rs(x));
	tag[ls(x)] ^= 1;tag[rs(x)] ^= 1;
	tag[x] = 0;
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
	for (int t = 0; x; x = fa[t = x])
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
	tag[x] ^= 1;
}
void link(int x, int y)
{
	makeroot(x);
	fa[x] = y;
}
void cut(int x, int y)
{
	makeroot(x);
	access(y);
	splay(y);
	fa[x] = ls(y) = 0;
}
int query(int u, int v)
{
	makeroot(u);
	access(v);
	splay(v);
	return s[v];
}
long long ansu = 1 << 30, ansv = 1;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, n + 1, n + m) scanf("%d%d%d", &E[i].x, &E[i].y, &E[i].z);
	cin >> S >> T;
	sort(E + n + 1, E + 1 + n + m, cmp);
	REP(i, 1, n) f[i] = i;
	REP(i, n + 1, n + m)
	{
		if (find(E[i].x) ^ find(E[i].y))
		{
			uni(E[i].x, E[i].y);
			link(E[i].x, i);
			link(E[i].y, i);
		}
		else
		{
			int pos = query(E[i].x, E[i].y);
			if (E[pos].z <= E[i].z) continue;
			cut(E[pos].x, pos);
			cut(E[pos].y, pos);
			link(E[i].x, i);
			link(E[i].y, i);
		}
		if (find(S) == find(T))
		{
			int v = E[query(S, T)].z;
			if (ansu * E[i].z >= ansv * v) ansu = v, ansv = E[i].z;
		}
	}
	if (ansu % ansv == 0) printf("%lld\n", ansu / ansv);
	else printf("%lld/%lld\n", ansu / __gcd(ansu, ansv), ansv / __gcd(ansu, ansv));
	return 0;
}
