#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define  REP(i, s, e) for (int i = s; i <= e ;i++)
#define DREP(i, s, e) for (int i = s; i >= e ;i--)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 100000 + 10, maxN = maxn << 1, maxm = 200000 + 10, inf = (((1 << 30) - 1) << 1) + 1;

struct Edge
{
	int x, y, z;
	Edge(){}
	Edge(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
}E[maxm + maxn];
bool cmp(Edge A, Edge B) {return A.z > B.z;}
int f[maxN];
int find(int x) {return f[x] == x ? f[x] : f[x] = find(f[x]);}
void uni(int x, int y) {f[find(x)] = find(y);}

int n, m;

int ch[maxN][2], fa[maxN], val[maxN], id[maxN];
bool tag[maxN];

#define ls(p) ch[p][0]
#define rs(p) ch[p][1]
#define get(p) (rs(fa[p]) == p)

void pushup(int x)
{
	id[x] = x;id[0] = 0;
	REP(i, 0, 1) if (E[id[x]].z < E[id[ch[x][i]]].z) id[x] = id[ch[x][i]];
}

#define notroot(x) (fa[x] && (ls(fa[x]) == x || rs(fa[x]) == x))
void rotate(int x)
{
	int y = fa[x], z = fa[y];
	bool k = get(x);
	ch[y][k] = ch[x][k ^ 1];
	if (ch[x][k ^ 1]) fa[ch[x][k ^ 1]] = y;
	ch[x][k ^ 1] = y;
	if (notroot(y)) ch[z][get(y)] = x;
	fa[y] = x;
	fa[x] = z;
	pushup(y);
	pushup(x);
}
void work(int x) {tag[x] ^= 1;swap(ls(x), rs(x));}
void pushdown(int x)
{
	if (tag[x])
	{
		work(ls(x));
		work(rs(x));
		tag[x] = 0;
	}
}
void pushall(int x)
{
	cerr << x << endl;
	if (notroot(x)) pushall(fa[x]);
	pushdown(x);
}
void splay(int x)
{
	DEBUG;
	pushall(x);
	DEBUG;
	while (notroot(x))
	{
	DEBUG;
		int y = fa[x];
		if (notroot(y)) rotate(get(x) == get(y) ? y : x);
		rotate(x);
	}
}
void access(int x)
{
	DEBUG;
	for (int y = 0; x; x = fa[y = x])
	{
	DEBUG;
		splay(x);
	DEBUG;
		rs(x) = y, pushup(x);
	DEBUG;
	}
	DEBUG;
}
void makeroot(int x)
{
	access(x);
	splay(x);
	work(x);
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
	ls(y) = fa[x] = 0;
	pushup(y);
}
int query(int x, int y)
{
	DEBUG;
	makeroot(x);
	DEBUG;
	access(y);
	DEBUG;
	splay(y);
	DEBUG;
	return id[y];
}

int N;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n >> m;
	N = n;
	REP(i, n+1, n+m)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		E[i] = Edge(x, y, z);
	}
	sort(E + n, E + 1 + n + m, cmp);
	REP(i, 1, n) f[i] = i;
	REP(i, n + 1, n + m)
		if (find(E[i].x) != find(E[i].y))
		{
			DEBUG;
			uni(E[i].x, E[i].y);
			DEBUG;
			++N;
			DEBUG;
			link(E[i].x, i);
			DEBUG;
			link(i, E[i].y);
			DEBUG;
		}
		else
		{
			int pos = query(E[i].x, E[i].y);
			DEBUG;
			if (E[pos].z <= E[i].z) continue;
			else
			{
				cut(E[pos].x, pos);
				DEBUG;
				cut(E[pos].y, pos);
				DEBUG;
				link(E[i].x,i);
				DEBUG;
				link(E[i].y, i);
			}
		}
	return 0;
}
