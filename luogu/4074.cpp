#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)

#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 10, maxm = 100000 + 10, maxq = 100000 + 10, maxw = 1e6 + 10;
int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n, m, q;
int v[maxm], w[maxn];

int grand[maxn][20], LOG, depth[maxn], dfn[maxn], low[maxn], cur;
int g[maxn << 1];
void dfs(int x)
{
	REP(i, 1, LOG) grand[x][i] = grand[grand[x][i-1]][i-1];
	g[dfn[x] = ++cur] = x;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			dfs(to[i]);
		}
	g[low[x] = ++cur] = x;
}
int lca(int x, int y)
{
	if (x == y) return x;
	if (dfn[x] > dfn[y]) swap(x, y);
	DREP(i, LOG, 0) if (dfn[grand[y][i]] > dfn[x]) y = grand[y][i];
	return grand[y][0];
}
int col[maxn], last[maxn];
int belong[maxn << 1];
struct query
{
	int l, r, t, id;
	bool operator < (query b) const {return belong[l] < belong[b.l] || belong[l] == belong[b.l] && belong[r] < belong[b.r] || belong[l] == belong[b.l] && belong[r] == belong[b.r] && t < b.t;}
}a[maxm], b[maxm];int cnt1, cnt2;

bool vis[maxn << 1];
long long nowans, ans[maxm], cnt[maxw];

void add(int x)
{
	if (vis[x])	nowans -= 1ll * v[col[x]] * w[cnt[col[x]]--];
	else		nowans += 1ll * v[col[x]] * w[++cnt[col[x]]];
	vis[x] ^= 1;
}
void modify(int x, int y)
{
	if (vis[x])
	{
		add(x);
		col[x] = y;
		add(x);
	}
	else col[x] = y;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("4074.in", "r", stdin);
	freopen("4074.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	REP(i, 1, m) scanf("%d", v + i);
	REP(i, 1, n) scanf("%d", w + i);
	REP(i, 2, n)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);add(y, x);
	}
	LOG = log2(n);
	depth[1] = 1;
	dfs(1);
	REP(i, 1, n) scanf("%d", col + i), last[i] = col[i];
	int block_siz = pow(cur, 2. / 3);
	REP(i, 1, cur) belong[i] = (i-1) / block_siz;
	while (q--)
	{
		int opt, x, y;
		scanf("%d%d%d", &opt, &x, &y);
		if (!opt)
		{
			b[++cnt2] = (query){x, last[x], y};
			last[x] = y;
		}
		else
		{
			if (dfn[x] > dfn[y]) swap(x, y);
			a[++cnt1] = (query){lca(x, y) == x ? dfn[x] : low[x], dfn[y], cnt2, cnt1};
		}
	}
	sort(a + 1, a + 1 + cnt1);
	int nowl(0), nowr(0), T(1);
	REP(i, 1, cnt1)
	{
		while (T <= a[i].t)
		{
			modify(b[T].l, b[T].t);
			T++;
		}
		while (T > a[i].t)
		{
			modify(b[T].l, b[T].r);
			T--;
		}
		while (nowl < a[i].l) add(g[nowl++]);
		while (nowl > a[i].l) add(g[--nowl]);
		while (nowr < a[i].r) add(g[++nowr]);
		while (nowr > a[i].r) add(g[nowr--]);
		int x(g[nowl]), y(g[nowr]), l(lca(x, y));
		if (x ^ l && y ^ l)
		{
			add(l);
			ans[a[i].id] = nowans;
			add(l);
		}
		else ans[a[i].id] = nowans;
	}
	REP(i, 1, cnt1) printf("%lld\n", ans[i]);
	return 0;
}
