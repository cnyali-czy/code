#define  REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, (b))
#define chkmin(a, b) a = min(a, (b))

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 250000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
long long w[maxn << 1];
inline void add(const int &x, const int &y, const long long &z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
}

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

namespace orzmalidaxian
{
	int fa[maxn], top[maxn], siz[maxn], hvy[maxn], depth[maxn], dfn[maxn], grand[maxn][20];
	long long dist[maxn][20];
	void dfs1(const int &x)
	{
		REP(i, 1, 19)
		{
			grand[x][i] = grand[grand[x][i-1]][i-1];
			dist[x][i] = min(dist[x][i-1], dist[grand[x][i-1]][i-1]);
		}
		dfn[x] = ++dfn[0];
		siz[x] = 1;
		for (register int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
		{
			grand[to[i]][0] = x;
			depth[to[i]] = depth[x] + 1;
			dist[to[i]][0] = w[i];
			fa[to[i]] = x;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
	}
	void dfs2(const int &x, const int &y)
	{
		top[x] = y;
		if (hvy[x])
		{
			dfs2(hvy[x], y);
			for (register int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x] && to[i] ^ hvy[x])
				dfs2(to[i], to[i]);
		}
	}

	inline int lca(int x, int y)
	{
		while (top[x] ^ top[y])
			if (depth[top[x]] < depth[top[y]]) y = fa[top[y]];
			else x = fa[top[x]];
		return depth[x] < depth[y] ? x : y;
	}
	inline long long dis(int x, int y)
	{
		long long res(1e18);
		if (depth[x] < depth[y]) swap(x, y);
		DREP(i, 19, 0)
			if (depth[grand[x][i]] > depth[y])
			{
				chkmin(res, dist[x][i]);
				x = grand[x][i];
			}
		return min(res, dist[x][0]);
	}
}
using orzmalidaxian :: dis;
using orzmalidaxian :: lca;
using orzmalidaxian :: dfn;
int stack[maxn], top, h[maxn];
inline bool cmp(const int &x, const int &y) {return dfn[x] < dfn[y];}

bool mark[maxn];

long long dp[maxn];
void solve(const int &x, const int &fa = -1)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		solve(to[i], x);
		if (mark[to[i]]) dp[x] += w[i];
		else dp[x] += min(dp[to[i]], w[i]);
	}
}

void clear(const int &x, const int &fa = -1)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		e--;
		clear(to[i], x);
	}
	mark[x] = dp[x] = bg[x] = 0;
}

int main()
{
#ifdef CraZYali
	file("2495");
#endif
	cin >> n;
	REP(i, 2, n)
	{
		register int x(read<int>()), y(read<int>()), z(read<int>());
		add(x, y, z);add(y, x, z);
	}
	orzmalidaxian::dfs1(1);
	orzmalidaxian::dfs2(1, 1);
	REP(i, 1, n) bg[i] = 0;e = 0;
	int q = read<int>();
	while (q--)
	{
		int k = read<int>();
		REP(i, 1, k) mark[h[i] = read<int>()] = 1;
		sort(h + 1, h + 1 + k, cmp);
		stack[top = 1] = 1;
		REP(i, 1 + (h[1] == 1), k)
		{
			register int l = lca(h[i], stack[top]);
			if (l ^ stack[top])
			{
				while (dfn[l] < dfn[stack[top-1]])
				{
					add(stack[top-1], stack[top], dis(stack[top-1], stack[top]));
					top--;
				}
				if (dfn[l] > dfn[stack[top-1]])
				{
					add(l, stack[top], dis(l, stack[top]));
					stack[top] = l;
				}
				else add(l, stack[top], dis(l, stack[top])), top--;
			}
			stack[++top] = h[i];
		}
		REP(i, 2, top) add(stack[i-1], stack[i], dis(stack[i-1], stack[i]));
		solve(1);
		/*
		REP(i, 1, k) printf("%d%c", h[i], i == k ? '\n' : ' ');
		REP(x, 1, n)
			for (int i = bg[x]; i; i = ne[i]) printf("%d %d %lld\n", x, to[i], w[i]);
		puts("----------");
		*/
		printf("%lld\n", dp[1]);
		clear(1);
	}
	return 0;
}
