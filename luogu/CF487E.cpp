#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>

using namespace std;
const int maxn = 2e5 + 10, maxm = 2e5 + 10, maxnode = 7000000, inf = 1e9;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, m, q, N;
int w[maxn], www[maxn];
multiset <int> ww[maxn];

int stack[maxn], Top;
int dfn[maxn], low[maxn], dfs_clock;

int siz[maxn], hvy[maxn], fa[maxn], depth[maxn], top[maxn], back[maxn];

#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

namespace Tree
{
	int query(int x) {return w[back[x]];}
	int query_old(int x) {return w[x];}
	int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
	void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}

	void dfs1(int x)
	{
		siz[x] = 1;
		for (int i = bg[x]; i ; i = ne[i])
			if (to[i] ^ fa[x])
			{
				fa[to[i]] = x;
				depth[to[i]] = depth[x] + 1;
				dfs1(to[i]);
				siz[x] += siz[to[i]];
				if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
				if (x > n) ww[x].insert(w[to[i]]);
			}
	}
	void dfs2(int x, int y)
	{
		www[dfn[x] = ++dfs_clock] = w[x];
		back[dfn[x]] = x;
		top[x] = y;
		if (hvy[x]) dfs2(hvy[x], y);
		for (int i = bg[x]; i ; i = ne[i])
			if (to[i] ^ hvy[x] && to[i] ^ fa[x]) dfs2(to[i], to[i]);
	}
	int root;
	int Min[maxnode], ls[maxnode], rs[maxnode], cur;
	void pushup(int p, int l, int r) {Min[p] = min(Min[ls[p]], Min[rs[p]]);}
	void build(int &p, int l, int r)
	{
		p = ++cur;
		if (l == r) Min[p] = query(l);
		else
		{
			build(lson);
			build(rson);
			pushup(p, l, r);
		}
	}
	int query(int p, int l, int r, int L, int R)
	{
		if (L <= l && r <= R) return Min[p];
		else
		{
			if (L >  mid) return query(rson, L, R);
			if (R <= mid) return query(lson, L, R);
			return min(query(lson, L, R), query(rson, L, R));
		}
	}
	int query(int x, int y)
	{
		int res = inf;
		while (top[x] ^ top[y])
		{
			if (depth[top[x]] < depth[top[y]]) swap(x, y);
			chkmin(res, query(root, 1, N, dfn[top[x]], dfn[x]));
			x = fa[top[x]];
		}
		if (depth[x] > depth[y]) swap(x, y);
		chkmin(res, query(root, 1, N, dfn[x], dfn[y]));
		if (x > n) chkmin(res, w[fa[x]]);
		return res;
	}
	void update(int p, int l, int r, int pos, int val)
	{
		if (l == r) Min[p] = val;
		else
		{
			if (pos <= mid) update(lson, pos, val);
			else update(rson, pos, val);
			pushup(p, l, r);
		}
	}
	void update(int x, int v)
	{
		if (fa[x] && fa[x] > n)
		{
			ww[fa[x]].erase(ww[fa[x]].find(w[x]));
			ww[fa[x]].insert(v);
			w[fa[x]] = *ww[fa[x]].begin();
			update(root, 1, N, dfn[fa[x]], query_old(fa[x]));
		}
		w[x] = v;
		update(root, 1, N, dfn[x], v);
	}
	void output()
	{
		REP(x, 1, n)
			for (int i = bg[x]; i ; i = ne[i]) printf("(%d,%d) (%d,%d)\n", x, query(x), to[i], query(to[i]));
		REP(i, 1, n)
			REP(j, i, n)
			printf("%d %d %d\n", i, j, query(i, j));
	}
} 

namespace Graph
{
	int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
	void add(int x, int y)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
	}
	void dfs(int u, int fa = -1)
	{
		dfn[u] = low[u] = ++dfs_clock;
		stack[++Top] = u;
		for (int i = bg[u]; i ; i = ne[i])
			if (!dfn[to[i]])
			{
				dfs(to[i], u);
				chkmin(low[u], low[to[i]]);
				if (low[to[i]] >= dfn[u])
				{
					N++;
					Tree::add(N, u);Tree::add(u, N);
					while (Top > 0)
					{
						int x = stack[Top--];
						Tree::add(N, x);Tree::add(x, N);
						if (x == to[i]) break;
					}
				}
			}
			else chkmin(low[u], dfn[to[i]]);
	}
	void calc()	{dfs(1);}
}
int main()
{
#ifdef CraZYali
	freopen("CF487E.in", "r", stdin);
	freopen("CF487E.out", "w", stdout);
#endif
	cin >> n >> m >> q;N = n;
	REP(i, 1, n) w[i] = read<int>();
	while (m--)
	{
		int x(read<int>()), y(read<int>());
		Graph::add(x, y);Graph::add(y, x);
	}
	Graph::calc();
	Tree::dfs1(1);
	dfs_clock = 0;
	Tree::dfs2(1, 1);
	REP(i, n + 1, N) w[i] = *ww[i].begin();
	Tree::build(Tree::root, 1, N);
	w[0] = inf;
	//	T.output();
	while (q--)
	{
		char c = getchar();
		while (c != 'A' && c != 'C') c = getchar();
		int x(read<int>()), y(read<int>());
		if (c == 'C') Tree::update(x, y);
		else printf("%d\n", Tree::query(x, y));
	}
	return 0;
}
