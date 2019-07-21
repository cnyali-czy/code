#define REP(i, s, e) for (int i = s; i <= e ; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
const int maxn = 300000 + 10, maxm = maxn, inf = 1ll << 40;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int depth[maxn];
void dfs(int x, int fa = -1)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			depth[to[i]] = depth[x] + 1;
			dfs(to[i], x);
		}
}

struct worker
{
	int up, w, ne;
}p[maxm << 1];
int cur = 300000;
void insert(int x, int up, int w)
{
	p[++cur] = (worker){up, w, p[x].ne};
	p[x].ne = cur;
}

struct heap *null;
struct heap
{
	int up, f, Min, tag, dis;
	heap *l, *r;
	void pushdown()
	{
		if (tag)
		{
			f += tag;
			Min += tag;
			l -> tag += tag;
			r -> tag += tag;
			tag = 0;
		}
	}
	void pushup()
	{
		Min = min(f, min(l -> Min + l -> tag, r -> Min + r -> tag));
		if (l -> dis < r -> dis) swap(l, r);
		dis = r -> dis + 1;
	}
}pool[maxn], *now = pool, *root[maxn];
heap* merge(heap *x, heap *y)
{
	if (x == null) return y;
	if (y == null) return x;
	x -> pushdown();y -> pushdown();
	if (x -> up <= y -> up) swap(x, y);
	x -> r = merge(x -> r, y);
	x -> pushup();
	return x;
}
void solve(int x, int fa = -1)
{
	int sum = 0;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			solve(to[i], x);
			while (root[to[i]] -> up >= depth[to[i]])
				root[to[i]] = merge(root[to[i]] -> l, root[to[i]] -> r);
			if (root[to[i]] == null)
			{
				cout << -1 << endl;
				exit(0);
			}
			sum += root[to[i]] -> Min;
		}
	for (int i = p[x].ne; i ; i = p[i].ne)
	{
		*now = (heap) {p[i].up, sum + p[i].w, sum + p[i].w, 0, 1, null, null};
		root[x] = merge(root[x], now++);
	}
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa)
		{
			int Min = root[to[i]] -> Min;
			root[to[i]] -> tag += sum - Min;
			root[x] = merge(root[x], root[to[i]]);
		}
	if (root[x] == null)
	{
		cout << -1 << endl;
		exit(0);
	}
}

int m, n, k;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		add(x, y);add(y, x);
	}
	depth[1] = 1;
	dfs(1);
	REP(i, 1, m)
	{
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		insert(u, depth[v], w);
	}
	null = new heap;
	null -> l = null -> r = null;
	null -> Min = inf;
	REP(i, 1, n) root[i] = null;
	solve(1);
	printf("%lld\n", root[1] -> Min + root[1] -> tag);
	return 0;
}
