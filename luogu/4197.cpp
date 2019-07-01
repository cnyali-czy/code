#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;
const int maxn = 1e5 + 10, maxm = 5e5 + 10, n_log_n = 2e6;

int bg[maxn << 1], to[maxm], ne[maxm], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int fa[maxn << 1];
int find(int x) {return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, m, q, cur, l;
int val[maxn << 1];
struct Edge
{
	int x, y, z;
	Edge() {}
	Edge(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
}E[maxm];
bool cmp(Edge A, Edge B) {return A.z < B.z;}

int N, grand[maxn << 1][20], LOG, Left[maxn << 1], Right[maxn << 1];
int dfn[maxn], dfs_clock;

void prepare(int x)
{
	if (x <= n) Left[x] = Right[x] = dfn[x] = ++dfs_clock;
	bool flag = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			grand[to[i]][0] = x;
			prepare(to[i]);
			if (x > n)
				if (!flag) {Left[x] = Left[to[i]];Right[x] = Right[to[i]];flag = 1;}
				else
				{
					chkmin(Left[x], Left[to[i]]);
					chkmax(Right[x], Right[to[i]]);
				}
		}
}
void output(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			printf("%d %d\n", x, to[i] <= n ? dfn[to[i]] : to[i]);
			output(to[i]);
		}
}

int a[maxn], b[maxn];

struct node *null;
struct node
{
	node *l, *r;
	int sum ;
	node() : l(null), r(null), sum(0) {};
	node(node *ls, node *rs) : l(ls), r(rs), sum(0) {}
};

#define mid (l + r >> 1)

void build(node *pre, node *p, int l, int r, int pos)
{
	p = new node;
	p -> l = pre -> l;
	p -> r = pre -> r;
	p -> sum = pre -> sum + 1;
	if (pos <= mid) build(pre -> l, p -> l, l, mid, pos);
	else build(pre -> r, p -> r, mid + 1, r, pos);
}
node* T[n_log_n];

int main()
{
#ifdef CraZYali
	file("4197");
#endif
	cin >> n >> m >> q;cur = n;
	REP(i, 1, n) scanf("%d", val + i);
	REP(i, 1, n * 2) fa[i] = i;
	REP(i, 1, m)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		E[i] = Edge(x, y, z);
	}
	sort(E + 1, E + 1 + m, cmp);
	int cnt = 0;
	REP(i, 1, m)
	{
		int x(find(E[i].x)), y(find(E[i].y));
		int fx(find(x)), fy(find(y));
		if (x ^ y)
		{
			val[++cur] = E[i].z;
			add(cur, x);
			add(cur, y);
			fa[fx] = fa[fy] = cur;
			if (++cnt == n - 1) break;
		}
	}
	N = n + n - 1;
	prepare(cur);
	LOG = log2(N);
	REP(j, 1, LOG)
		REP(i, 1, n)
		grand[i][j] = grand[grand[i][j-1]][j-1];
//	REP(i, n+1, N)
//		printf("%d %d %d\n", i, Left[i], Right[i]);
//	output(cur);
	REP(i, 1, n) a[i] = b[i] = val[dfn[i]];
	sort(b + 1, b + 1 + n);
	l = unique(b + 1, b + 1 + n) - b - 1;
	null = new node;
	null -> l = null -> r = null;
	null -> sum = 0;
	T[0] = null;
	REP(i, 1, n) build(T[i-1], T[i], 1, l, lower_bound(b + 1, b + 1 + l, a[i]) - b);

	return 0;
}
