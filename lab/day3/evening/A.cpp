#define REP(i, s, e) for (int i = s; i <= e; i++)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10, maxm = maxn, maxnode = 1800000;

int read()
{
	char c = getchar();
	int ans = 0, flag = 1;
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c)) ans = ans * 10 + c - 48, c = getchar();
	return ans * flag;
}

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int ww[maxn], dfn[maxn], top[maxn], fa[maxn], hvy[maxn], depth[maxn];

int n, m, s, lastans, a[maxn], b[maxn], dfs_clock;
int dfs1(int x)
{
	int siz = 1, Max(0);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			int sizv = dfs1(to[i]);
			siz += sizv;
			if (sizv > Max)
			{
				Max = sizv;
				hvy[x] = to[i];
			}
		}
	return siz;
}
void dfs2(int x, int y)
{
	top[x] = y;
	ww[dfn[x] = ++dfs_clock] = a[x];
	if (hvy[x]) dfs2(hvy[x], y);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x] && to[i] ^ hvy[x]) dfs2(to[i], to[i]);
}
int cnt[maxnode], ls[maxnode], rs[maxnode], rt[maxn], cur;
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

void build(int pre, int &p, int l, int r, int pos)
{
	p = ++cur;
	ls[p] = ls[pre];
	rs[p] = rs[pre];
	cnt[p] = cnt[pre] + 1;
	if (l == r) return;
	if (pos <= mid) build(ls[pre], lson, pos);
	else build(rs[pre], rson, pos);
}

int rcnt;
pair <int, int> RT[maxn];
int query(int k)
{
	int l = 1, r = s;
	while (l != r)
	{
		int res = 0;
		REP(i, 1, rcnt) res += cnt[ls[RT[i].second]] - cnt[ls[RT[i].first]];
		if (res >= k)
		{
			REP(i, 1, rcnt) RT[i].first = ls[RT[i].first], RT[i].second = ls[RT[i].second];
			r = mid;
		}
		else
		{
			REP(i, 1, rcnt) RT[i].first = rs[RT[i].first], RT[i].second = rs[RT[i].second];
			l = mid + 1;k -= res;
		}
	}
	return l;
}

int query(int x, int y, int k)
{
	rcnt = 0;
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		RT[++rcnt] = make_pair(rt[dfn[top[x]]-1], rt[dfn[x]]);
		x = fa[top[x]];
	}
	if (depth[x] > depth[y]) swap(x, y);
	RT[++rcnt] = make_pair(rt[dfn[x]-1], rt[dfn[y]]);
	return query(k);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = b[i] = read();
	REP(i, 2, n)
	{
		int x(read()), y(read());
		add(x, y);add(y, x);
	}
	depth[1] = 1;
	dfs1(1);
	dfs2(1, 1);
	sort(b + 1, b + 1 + n);
	s = unique(b + 1, b + 1 + n) - b - 1;
	REP(i, 1, n) build(rt[i-1], rt[i], 1, s, lower_bound(b + 1, b + 1 + s, ww[i]) - b);
	while (m--)
	{
		int x(read() ^ lastans), y(read()), k(read());
		printf("%d\n", lastans = b[query(x, y, k)]);
	}
	return 0;
}
