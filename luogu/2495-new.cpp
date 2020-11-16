/*
	Problem:	2495-new.cpp
	Time:		2020-11-16 20:19
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 2.5e5 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;

int nd[maxn], cs[maxn], ct;
inline void add(int x, int y, int z)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
	w[e] = z;
	if (!nd[x]) nd[cs[++ct] = x] = 1;
}
void clear()
{
	REP(i, 1, ct)
	{
		int x = cs[i];
		nd[x] = bg[x] = 0;
	}
	ct = e = 0;
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;

namespace lca
{
	int st[20][maxn << 1], dfs_clock, dep[maxn], fir[maxn], wfa[20][maxn], anc[20][maxn];
	void dfs(int x, int fa = 0)
	{
		dep[x] = dep[fa] + 1;
		st[0][fir[x] = ++dfs_clock] = x;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			wfa[0][to[i]] = w[i];
			anc[0][to[i]] = x;
			dfs(to[i], x);
			st[0][++dfs_clock] = x;
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
		dfs(1);
		REP(i, 2, (1 << w) - 1) Lg[i] = Lg[i >> 1] + 1;
		REP(j, 1, 19)
		{
			const int b2 = (1 << j - 1);
			REP(i, 1, dfs_clock - (1 << j) + 1)
			{
				int u = st[j - 1][i], v = st[j - 1][i + b2];
				st[j][i] = dep[u] < dep[v] ? u : v;
			}
			REP(i, 1, n)
			{
				anc[j][i] = anc[j - 1][anc[j - 1][i]];
				wfa[j][i] = min(wfa[j - 1][i], wfa[j - 1][anc[j - 1][i]]);
			}
		}
	}
	int lca(int x, int y)
	{
		int l = fir[x], r = fir[y];
		if (l > r) swap(l, r);
		int k = lg(r - l + 1);
		x = st[k][l], y = st[k][r - (1 << k) + 1];
		return dep[x] < dep[y] ? x : y;
	}
	int minw(int x, int y)
	{
		if (dep[x] < dep[y]) swap(x, y);
		int res = 1e9;
		for (; x != y; x = anc[0][x])res=min(res,wfa[0][x]);return res;
		DEP(i, 19, 0) if (dep[anc[i][x]] > dep[y])
		{
			res = min(res, wfa[i][x]);
			x = anc[i][x];
		}
		return min(res, wfa[0][x]);
	}
}
inline void Add(int x, int y) {add(x, y, lca :: minw(x, y));}

bool is[maxn];
int a[maxn];
i64 f[maxn];
void dfs(int x, int fa = 0)
{
	f[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
	{
		dfs(to[i], x);
		if (is[to[i]]) f[x] += w[i];
		else f[x] += min((i64)w[i], f[to[i]]);
	}
}

int main()
{
#ifdef CraZYali
	file("2495-new");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>(), z = read<int>();
		add(x, y, z);add(y, x, z);
	}
	lca :: init();
	int q = read<int>();
	while (q--)
	{
		clear();
		int k = read<int>();
		REP(i, 1, k) is[a[i] = read<int>()] = 1;
		sort(a + 1, a + 1 + k, [&](int x, int y) {return lca :: fir[x] < lca :: fir[y];});
		static int stk[maxn], top;
		stk[top = 1] = 1;
		REP(i, 1 + (a[1] == 1), k)
		{
			while (top)
			{
				int l = lca :: lca(a[i], stk[top]);
				if (l == stk[top]) break;
				if (lca :: fir[stk[top - 1]] < lca :: fir[l])
				{
					Add(l, stk[top]);
					stk[top] = l;
					break;
				}
				add(stk[top - 1], stk[top], lca :: minw(stk[top - 1], stk[top]));
				top--;
			}
			stk[++top] = a[i];
		}
		REP(i, 1, top - 1) add(stk[i], stk[i + 1], lca :: minw(stk[i], stk[i + 1]));
		dfs(1);
		
		printf("%lld\n", f[1]);
		REP(i, 1, k) is[a[i]] = 0;
	}
	return 0;
}
