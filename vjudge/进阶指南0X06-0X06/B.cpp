#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long

using namespace std;
const int maxn = 40000 + 10, maxm = maxn;

int n, m, k;
int bg[maxn], ne[maxm << 1], to[maxm << 1], w[maxm << 1], e;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

int grand[maxn][20], depth[maxn], dis[maxn], LOG;
void clear() {e = 0;REP(i, 1, n) bg[i] = dis[i] = depth[i] = 0;}

template <typename T> T read()
{
	T ans = 0, p = 1;
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

void get_depth(int x)
{
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ grand[x][0])
		{
			dis[to[i]] = dis[x] + w[i];
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			get_depth(to[i]);
		}
}

int lca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	DREP(i, LOG, 0)
		if (depth[grand[x][i]] >= depth[y]) x = grand[x][i];
	if (x == y) return x;
	else
	{
		DREP(i, LOG, 0)
			if (grand[x][i] ^ grand[y][i]) x = grand[x][i], y = grand[y][i];
		return grand[x][0];
	}
}
int dist(int x, int y) {return dis[x] + dis[y] - dis[lca(x, y)] * 2;}

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();m = read<int>();
		clear();
		REP(i, 2, n)
		{
			int x(read<int>()), y(read<int>()), z(read<int>());
			add(x, y, z);add(y, x, z);
		}
		depth[1] = 1;
		get_depth(1);
		LOG = log2(n);
		REP(j, 1, LOG)
			REP(i, 1, n)
			grand[i][j] = grand[grand[i][j-1]][j-1];
		while (m --> 0) printf("%lld\n", dist(read<int>(), read<int>()));
	}
	return 0;
}
