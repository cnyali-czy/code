#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 3e5 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k;
int grand[maxn][20], depth[maxn], LOG, dfn[maxn], dfs_clock, siz[maxn];
void dfs(int x)
{
	siz[x] = 1;
	dfn[x] = ++dfs_clock;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			dfs(to[i]);
			siz[x] += siz[to[i]];
		}
}
int get_lca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0) if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	else
	{
		DREP(i, LOG, 1)
			if (grand[x][i] ^ grand[y][i]) x = grand[x][i], y = grand[y][i];
		return grand[x][0];
	}
}
int u[maxm], v[maxm], lca[maxm];

struct BIT
{
	int a[maxn];
	void add(int x, int y)
	{
		if (!x)return;
		while (x <= n)
		{
			a[x] += y;
			x += x & -x;
		}
	}
	int sum(int x)
	{
		int res = 0;
		while (x > 0)
		{
			res += a[x];
			x -= x & -x;
		}
		return res;
	}
}bit;
int w[maxn];

struct node
{
	int p, q, r;
	node() {}
	node(int _p, int _q, int _r = 0) : p(_p), q(_q), r(_r) {}
}a[maxn], b[maxn], c[2][maxn];
bool cmp1(node A, node B) {return A.q < B.q;}
bool cmp2(node A, node B) {return A.r < B.r;}
int cnt[2];
void add(int x, int y, int k, int b ) {c[k][++cnt[k]] = node(x, y, depth[k ? y : x] - b);}
queue <node> q;

int ans[maxn];

int main()
{
#ifdef CraZYali
	freopen("1600.in", "r", stdin);
	freopen("1600.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	REP(i, 1, n) w[i] = read<int>();
	depth[1] = 1;
	dfs(1);
	LOG = log2(n);
	REP(j, 1, LOG)
		REP(i, 1, n) grand[i][j] = grand[grand[i][j-1]][j-1];
	REP(i, 1, m) u[i] = read<int>(), v[i] = read<int>(), lca[i] = get_lca(u[i], v[i]);
	REP(i, 1, n)
		a[i] = node(i, depth[i] + w[i]), b[i] = node(i, depth[i] - w[i]);
	sort(a + 1, a + 1 + n, cmp1);sort(b + 1, b + 1 + n, cmp1);
	REP(i, 1, m)
	{
		if (lca[i] == u[i]) add(v[i], u[i], 1, 0);
		else if (lca[i] == v[i]) add(u[i], v[i], 0, 0);
		else
		{
			register int x = u[i];
			DREP(j, LOG, 0)
				if (depth[grand[x][j]] > depth[lca[i]]) x = grand[x][j];
			add(u[i], x, 0, 0);add(v[i], lca[i], 1, depth[u[i]] - depth[x] + 1);			
		}
	}
	sort(c[0] + 1, c[0] + 1 + cnt[0], cmp2);
	sort(c[1] + 1, c[1] + 1 + cnt[1], cmp2);
	int now1 = 1, now2 = 1;
	REP(i, 1, n)
	{
		while (a[i].q != a[i-1].q && !q.empty())
		{
			bit.add(q.front().p, -1);
			bit.add(q.front().q, 1);
			q.pop();
		}
		for(;now1 <= cnt[0] && c[0][now1].r <= a[i].q;now1++)
			if (a[i].q != a[i-1].q && c[0][now1].r == a[i].q)
			{
				bit.add(dfn[c[0][now1].p], 1);
				bit.add(dfn[grand[c[0][now1].q][0]], -1);
				q.push(node(dfn[c[0][now1].p], dfn[grand[c[0][now1].q][0]], 0));
			}
		ans[a[i].p] += bit.sum(dfn[a[i].p] + siz[a[i].p] - 1) - bit.sum(dfn[a[i].p] - 1);
	}
	while (!q.empty())
	{
		bit.add(q.front().p, -1);
		bit.add(q.front().q, 1);
		q.pop();
	}
	REP(i, 1, n)
	{
		while (b[i].q != b[i-1].q && !q.empty())
		{
			bit.add(q.front().p, -1);
			bit.add(q.front().q, 1);
			q.pop();
		}
		for(;now2 <= cnt[1] && c[1][now2].r <= b[i].q;now2++)
			if (b[i].q != b[i-1].q && c[1][now2].r == b[i].q)
			{
				bit.add(dfn[c[1][now2].p], 1);
				bit.add(dfn[grand[c[1][now2].q][0]], -1);
				q.push(node(dfn[c[1][now2].p], dfn[grand[c[1][now2].q][0]], 0));
			}
		ans[b[i].p] += bit.sum(dfn[b[i].p] + siz[b[i].p] - 1) - bit.sum(dfn[b[i].p] - 1);
	}

	REP(i, 1, n) printf("%d ", ans[i]);
	return 0;
}
