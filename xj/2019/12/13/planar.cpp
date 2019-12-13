#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cassert>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

using namespace std;
const int maxn = 5e5 + 10;

	template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}
vector <int> G[maxn];
//unordered_set <int> con[maxn];
int n, m, t, tot, T, ans;
map <int, int> mp[maxn], id[maxn];
int f[2][maxn];
int find(int x, int f[]) {return x == f[x] ? f[x] : f[x] = find(f[x], f);}
inline void uni(int x, int y, int f[])
{
	f[find(x, f)] = find(y, f);
}
int blg[maxn], dfn, deg[maxn], it[maxn];
bool vis[maxn];
int q[2][maxn], head[2], tail[2];
map <int, int> con[maxn];
int Next(int i)
{
	while (head[i] <= tail[i])
	{
		int x(q[i][head[i]]);
		while (it[x] < deg[x])
		{
			int k = G[x][it[x]++];
			if (!vis[k] && con[x][k]) return k;
		}
		head[i]++;
	}
	return -1;
}
void color(int x, int y)
{
	q[0][head[0] = tail[0] = 1] = x;
	q[1][head[1] = tail[1] = 1] = y;
	dfn++;
	vis[x] = vis[y] = 1;
	while (head[0] <= tail[0] && head[1] <= tail[1])
	{
		x = Next(0);
		y = Next(1);
		if (!~x || !~y) break;
		vis[q[0][++tail[0]] = x] = 1;
		vis[q[1][++tail[1]] = y] = 1;
	}
	if (!~x)
		REP(i, 1, tail[0]) blg[q[0][i]] = dfn;
	else
		REP(i, 1, tail[1]) blg[q[1][i]] = dfn;
	REP(I, 0, 1)
		REP(i, 1, tail[I])
		it[q[I][i]] = vis[q[I][i]] = 0;
}
void cut(int x, int y)
{
	con[x][y] = con[y][x] = 0;
	int i(id[x][y]), j(id[y][x]);
	int _x(find(i, f[0])), _y(find(j, f[0]));
	if (_x == _y)
	{
		tot++;
		color(x, y);
	}
	else f[0][_x] = _y;
}
int main()
{
#ifdef CraZYali
	freopen("planar.in", "r", stdin);
	freopen("planar.out", "w", stdout);
#endif
	n = read<int>();
	T = read<int>();
	REP(i, 1, n) f[1][i] = i;
	REP(i, 1, n)
	{
		G[i].resize(deg[i] = read<int>());
		REP(j, 0, deg[i] - 1)
		{
			int x(read<int>());
			uni(i, x, f[1]);
			G[i][mp[i][x] = j] = x;
			con[i][x] = 1;
		}
	}
	REP(i, 1, n) if (f[1][i] == i)
		blg[i] = ++dfn;
	tot = dfn;
	REP(i, 1, n)
		blg[i] = blg[find(i, f[1])];
	REP(i, 1, n)
		for (auto k : G[i]) if (!id[i].count(k))
		{
			id[i][k] = ++t;
			int x(i), y(k);
			while (1)
			{
				int it = (mp[y][x] + 1) % deg[y];
				x = y;
				y = G[y][it];
				if (id[x][y]) break;
				id[x][y] = t;
			}
		}
	REP(i, 1, t) f[0][i] = i;
	while (T--)
	{
		char c(getchar());
		while (c ^ '-' && c ^ '?') c = getchar();
		int x(read<int>() ^ ans), y(read<int>() ^ ans);
		assert(c == '-' || c == '?');
		assert(1 <= x && x <= n && 1 <= y && y <= n);
#ifdef DDEBUG
		x ^= ans;
		y ^= ans;
#endif
		if (c == '-')
		{
			cut(x, y);
			ans = tot;
		}
		else ans = (blg[x] == blg[y]);
		printf("%d\n", ans);
	}
	return 0;
}
