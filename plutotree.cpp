#define  REP(i, s, e) for (register long long i = s; i <= e ; i++)
#define DREP(i, s, e) for (register long long i = s; i >= e ; i--)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const long long maxn = 100000 + 10, maxm = maxn, inf = 1ll << 60ll;

long long bg[maxn], ne[maxm << 1], to[maxm << 1], e = 1;
inline void add(long long x, long long y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

long long m, n, k, LOG;

long long w[maxn];

long long grand[maxn][30], depth[maxn], sum[maxn];

long long tot[maxn][30], MAX[maxn][30];
long long a[maxn], b[maxn];

void dfs_pre(long long x)
{
	a[x] = inf;
	for (register long long i = bg[x]; i ; i = ne[i])
		if (grand[x][0] ^ to[i])
		{
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			sum[to[i]] = sum[x] + w[to[i]];
			dfs_pre(to[i]);
			if (a[x] > a[to[i]])
			{
				a[x] = a[to[i]];
				b[x] = b[to[i]];
			}
			else if (a[x] == a[to[i]]) chkmax(b[x], b[to[i]]);
		}
	if (a[x] == inf) a[x] = 0;
	a[x] += w[x];
	chkmax(b[x], w[x]);
}

void calc(long long u, long long v, long long &x, long long &y)
{
	y = 0;
	x = sum[u] + sum[v];
	if (depth[u] < depth[v]) swap(u, v);
	DREP(i, LOG, 0)
		if (depth[grand[u][i]] >= depth[v])
		{
			chkmax(y, MAX[u][i]);
			u = grand[u][i];
		}
	DREP(i, LOG, 0)
		if (grand[u][i] ^ grand[v][i])
		{
			chkmax(y, max(MAX[u][i], MAX[v][i]));
			u = grand[u][i];v = grand[v][i];
		}
	if (u ^ v)
	{
		chkmax(y, max(MAX[u][0], MAX[v][0]));
		u = grand[u][0];
	}
	chkmax(y, MAX[u][0]);
	x -= sum[u] + sum[grand[u][0]];
}

void dfs_aft(long long x)
{
	for (register long long i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			if (a[to[i]] > a[x] + w[to[i]])
			{
				a[to[i]] = a[x] + w[to[i]];
				b[to[i]] = max(b[x], w[to[i]]);
			}
			else if (a[to[i]] == a[x] + w[to[i]]) chkmax(b[to[i]], max(b[x], w[to[i]]));
			dfs_aft(to[i]);
		}
}

template <typename T> T read()
{
	T ans = 0;long long p = 1;
	register char c = getchar();
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


signed main()
{
	freopen("plutotree.in", "r", stdin);
	freopen("plutotree.out", "w", stdout);
	cin >> n >> m;
	LOG = log2(n);
	REP(i, 2, n)
	{
		register long long fa = read<long long>();
		add(i, fa);add(fa, i);
	}
	REP(i, 1, n) tot[i][0] = MAX[i][0] = w[i] = read<long long>();

	depth[1] = 1;
	sum[1] = w[1];
	dfs_pre(1);
	dfs_aft(1);

	REP(j, 1, LOG)
		REP(i, 1, n)
		{
			grand[i][j] = grand[grand[i][j-1]][j-1];
			tot[i][j] = tot[i][j-1] + tot[grand[i][j-1]][j-1];
			MAX[i][j] = max(MAX[i][j - 1], MAX[grand[i][j-1]][j-1]);
		}

	while (m --> 0)
	{
		register long long u = read<long long>(), v = read<long long>(), c1;
		if (depth[u] < depth[v]) swap(u, v);
		register long long d1, d2;
		calc(u, v, c1, d1);
		register long long a1 = c1, b1 = d1;
		calc(u, 1, c1, d1);
		c1 += a[v];chkmax(d1, b[v]);
		if (c1 < a1) a1 = c1, b1 = d1;
		else if (c1 == a1) chkmax(b1, d1);
		calc(1, v, c1, d1);
		c1 += a[u];chkmax(d1, b[u]);
		if (c1 < a1) a1 = c1, b1 = d1;
		else if (c1 == a1) chkmax(b1, d1);
		calc(1, 1, c1, d1);
		c1 += a[u] + a[v];
		chkmax(d1, max(b[u], b[v]));
		if (c1 < a1) a1 = c1, b1 = d1;
		else if (c1 == a1) chkmax(b1, d1);
		printf("%lld %lld\n", a1, b1);
	}

	return 0;
}
