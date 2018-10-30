#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 3e5 + 10, maxm = maxn;
int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
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

int m, n, k, LOG;
int u[maxm], v[maxm], lca[maxm], len[maxm];

int grand[maxn][20], depth[maxn], dist[maxn], fa[maxn], dfn[maxn], dfs_clock, wt[maxn];
void dfs(int x)
{
	dfn[x] = ++dfs_clock;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			fa[to[i]] = x;
			dist[to[i]] = dist[x] + w[i];
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			dfs(to[i]);
		}
		else wt[x] = w[i];
}
int getlca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0) if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	else
	{
		DREP(i, LOG, 0)
			if (grand[x][i] ^ grand[y][i]) x = grand[x][i], y = grand[y][i];
		return grand[x][0];
	}
}

int cnt[maxn], Max;

void dfs3(int x, int fa = -1)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa) {dfs3(to[i], x);cnt[x] += cnt[to[i]];}
}

bool check(int Mid)
{
	REP(i, 0, n) cnt[i] = 0;
	REP(i, 1, m)
		if (len[i] > Mid)
		{
			cnt[0]++;
			cnt[u[i]]++;cnt[v[i]]++;cnt[lca[i]] -= 2;
		}
	if (!cnt[0]) return 1;
	int res = -1e9;
	dfs3(1);
	REP(i, 1, n) if (cnt[i] == cnt[0]) chkmax(res, wt[i]);//, cout << "YES : " << i << ' ' << fa[i] << endl;
	return Max - res <= Mid;
}

int main()
{
#ifdef CraZYali
	freopen("2680.in", "r", stdin);
	freopen("2680.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 2, n)
	{
		register int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}
	depth[1] = 1;
	dfs(1);
	LOG = log2(n);
	REP(j, 1, LOG)
		REP(i, 1, n) grand[i][j] = grand[grand[i][j-1]][j-1];

	REP(i, 1, m) u[i] = read<int>(), v[i] = read<int>(), lca[i] = getlca(u[i], v[i]), len[i] = dist[u[i]] + dist[v[i]] - 2 * dist[lca[i]], chkmax(Max, len[i]);

	register int l = 0, r = Max, ans;
	while (l <= r)
	{
		register int Mid = l + r >> 1;
		if (check(Mid))
		{
			ans = Mid;
			r = Mid - 1;
		}
		else l = Mid + 1;
	}
	cout << ans;
	return 0;
}
