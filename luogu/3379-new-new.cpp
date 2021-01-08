/*
	Problem:	3379-new-new.cpp
	Time:		2020-11-03 15:30
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 5e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
	
	template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n, m, rt;
namespace lca
{
	int id[maxn << 1], A[maxn << 1], N;
	int st[19][maxn], dfs_clock, dep[maxn], fir[maxn];
	void dfs(int x, int fa = 0)
	{
		dep[x] = dep[fa] + 1;
		A[fir[x] = ++dfs_clock] = x;
		id[fir[x]] = x;
//		st[0][fir[x] = ++dfs_clock] = x;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs(to[i], x);
			A[++dfs_clock] = x;
		}
	}
	const int w = 10;
	int Lg[1 << w];
	inline int lg(int x)
	{
		if (x >> w) return w + Lg[x >> w];
		return Lg[x];
	}
	void init()
	{
		REP(i, 2, (1 << w) - 1) Lg[i] = Lg[i >> 1] + 1;
		dfs(rt);
		st[0][N = 1] = A[1];
		REP(i, 2, dfs_clock)
		{
			if (dep[A[i]] < dep[st[0][N]]) st[0][N] = A[i];
			if (id[i])
			{
				st[0][++N] = A[i];
				fir[id[i]] = N;
			}
		}
		REP(j, 1, 18)
			REP(i, 1, N - (1 << j) + 1)
			{
				int u = st[j - 1][i], v = st[j - 1][i + (1 << j - 1)];
				st[j][i] = dep[u] < dep[v] ? u : v;
			}
	}
	int query(int x, int y)
	{
		if (x == y) return x;
		int l = fir[x], r = fir[y];
		if (l > r) swap(l, r);
		r--;
		int k = lg(r - l + 1);
		x = st[k][l], y = st[k][r - (1 << k) + 1];
		return dep[x] < dep[y] ? x : y;
	}
}

int main()
{
#ifdef CraZYali
	file("3379-new-new");
#endif
	n = read<int>();m = read<int>();rt = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	lca :: init();
	while (m--) printf("%d\n", lca :: query(read<int>(), read<int>()));
	return 0;
}
