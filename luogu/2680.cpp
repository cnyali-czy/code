#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

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
const int maxn = 300000 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e = 1;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int m, n, k, LOG;

int grand[maxn][19], depth[maxn] = {0, 1};

void pre_grand(int x)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			pre_grand(to[i]);
		}
}

int lca[maxm];

int get_lca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0)
		if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	else
	{
		DREP(i, LOG, 0)
			if (grand[x][i] ^ grand[y][i])
			{
				x = grand[x][i];
				y = grand[y][i];
			}
		return grand[x][0];
	}
}

pair <int, int> Q[maxm];

int dist[maxn];

void dfs(int x, int y)
{
	dist[x] = y;
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0]) dfs(to[i], y + w[i]);
}

#define get_dist() dfs(1, 0)

int x, y, z;

int ans = 1e9;
/*
void pre_dist(int x)
{
	for (register int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			dist[to[i]][0] = w[i];
			pre_dist(to[i]);
		}
}
*/
void calc()
{
	register int Max = -1;

	get_dist();

	REP(i, 1, m) chkmax(Max, dist[Q[i].first] + dist[Q[i].second] - 2 * dist[lca[i]]);
	chkmin(ans, Max);
}

int main()
{
#ifdef CraZYali
	freopen("2680.in", "r", stdin);
	freopen("2680.out", "w", stdout);
#endif
	cin >> n >> m;
	LOG = log(n) / log(2);
	REP(i, 2, n)
	{
		x = read<int>();y = read<int>(); z = read<int>();
		add(x, y, z);add(y, x, z);
	}
	REP(i, 1, m) Q[i] = make_pair(read<int>(), read<int>());

	pre_grand(1);
	REP(j, 1, LOG)
		REP(i, 1, n)
			grand[i][j] = grand[grand[i][j-1]][j-1];

	REP(i, 1, n) lca[i] = get_lca(Q[i].first, Q[i].second);
	
	get_dist();

	REP(E, 1, n - 1)
	{
		register int W = w[E << 1];
		w[E << 1] = w[E << 1 | 1] = 0;
		calc();
		w[E << 1] = w[E << 1 | 1] = W;
	}
	
/*
	REP(E, 1, n - 1)
	{
		register int W = w[E << 1];
		w[E << 1] = w[E << 1 | 1] = 0;
		calc();
		w[E << 1] = w[E << 1 | 1] = W;
	}
*/
	cout << ans;
	return 0;
}
