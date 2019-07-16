#define  REP(i, s, e) for (int i = s ; i <= e; i++)
#define DREP(i, s, e) for (int i = s ; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 140000 + 10, maxm = 140000 + 10;

int now = 1, root;
int bg[maxn], ne[maxn << 1], to[maxn << 1], e = 1;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int fa[maxn], top[maxn], siz[maxn], depth[maxn], hvy[maxn];
int dfn[maxn], bac[maxn], dfs_clock;
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
		}
}
void dfs2(int x, int y)
{
	top[x] = y;
	dfn[x] = ++dfs_clock;
	if (hvy[x]) dfs2(hvy[x], y);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ hvy[x] && to[i] ^ fa[x]) dfs2(to[i], to[i]);
	bac[x] = dfs_clock;
}
int find(int x, int y)
{
	while (1)
	{
		if (top[x] == top[y]) return hvy[y];
		if (fa[top[x]] == y) return top[x];
		x = fa[top[x]];
	}
}

struct node
{
	int cnt;
	node *ls, *rs;
}pool[55555555], *null, *node_cur = pool;
node* newnode()
{
	node_cur -> ls = node_cur -> rs = null;
	return node_cur++;
}
#define mid (l + r >> 1)
#define lson p -> ls, l, mid
#define rson p -> rs, mid + 1, r
void update(node *&p, int l, int r, int pos, int val)
{
	if (p == null) p = newnode();
	p -> cnt += val;
	if (l == r) return;
	if (pos <= mid) update(lson, pos, val);
	else update(rson, pos, val);
}
int query(node *p, int l, int r, int pos)
{
	if (p == null) return 0;
	if (l == r) return p -> cnt;
	if (pos >  mid) return p -> ls -> cnt + query(rson, pos);
	else return query(lson, pos);
}
struct Trie
{
	node *t;
	Trie *ch[2];
}t[4444444], *pt = t + 1;
int ans[maxm];

struct Query
{
	int id, y, z, ne;
	Query(){}
	Query(int _id, int _y, int _z, int _ne) : id(_id), y(_y), z(_z), ne(_ne) {}
	void query()
	{
		Trie* p = t;
		DREP(i, 29, 0)
		{
			if (z >> i & 1)
				if (p -> ch[((z^y)>>i&1) ^ 1]) ans[id] += ::query(p -> ch[((z^y)>>i&1) ^ 1] -> t, 1, now, id);
			p = p -> ch[(z^y)>>i&1];
			if (!p) return;
		}
		ans[id] += ::query(p -> t, 1, now, id);
	}
}q[288888];
int pq = 144444;
void insert(int v, int id, int y, int z)
{
	q[pq] = Query(id, y, z, q[v].ne);
	q[v].ne = pq++;
}
struct opt
{
	int t, k, x, v;
	opt(){}
	opt(int _t, int _k, int _x, int _v) : t(_t), k(_k), x(_x), v(_v) {}
	void modify()
	{
		Trie* p = ::t;
		DREP(l, 29, 0)
		{
			if (!p -> ch[x >> l & 1]) pt -> t = newnode(), p -> ch[x >> l & 1] = pt++;
			p = p -> ch[x >> l & 1];
			update(p -> t, 1, now, t, k);
		}
	}
	bool operator < (opt B) const {return v < B.v;}
}op[433333];

int qcnt, Cur = 1;

int m, n;
signed main()
{
#ifndef ONLINE_JUDGE
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 2, n)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		add(x, y);add(y, x);
	}
	dfs1(1);
	dfs2(1, 1);
	null = pool + 55555500;
	t -> t = newnode();
	cin >> m;
	REP(i, 1, m)
	{
		int Opt;scanf("%lld", &Opt);
		if (Opt == 1)
		{
			int v, x, k;
			scanf("%lld%lld%lld", &v, &x, &k);
			if (dfn[v] >= dfn[root] || dfn[root] > bac[v])
				if (v == root) op[++qcnt] = opt(now, k, x, 1);
				else
				{
					op[++qcnt] = opt(now, k, x, dfn[v]);
					op[++qcnt] = opt(now, -k, x, bac[v] + 1);
				}
			else
			{
				int temp = find(root, v);
				op[++qcnt] = opt(now, k, x, 1);
				op[++qcnt] = opt(now, -k, x, dfn[temp]);
				op[++qcnt] = opt(now, k, x, bac[temp] + 1);
			}
		}
		else if (Opt == 2)
		{
			int v, y, z;
			scanf("%lld%lld%lld", &v, &y, &z);
			insert(dfn[v], now++, y, z);
		}
		else scanf("%lld", &root);
	}
	sort(op + 1, op + qcnt + 1);
	REP(i, 1, n)
	{
		while (op[Cur].v == i) op[Cur++].modify();
		for (int p = q[i].ne; p ; p = q[p].ne)
			q[p].query();
	}
	REP(i, 1, now - 1) printf("%lld\n", ans[i]);
	return 0;
}
