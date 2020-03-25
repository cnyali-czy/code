/*
	Problem:	6241.cpp
	Time:		2020-03-23 20:37
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
const int maxn = 1e5 + 10;

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

namespace run
{
	int n, head[N], tot;
	struct edge {
		int nxt, v;
	} e[N << 1];
	inline void addedge (int u, int v)
	{
		e[++tot] = (edge) {head[u], v};
		head[u] = tot;
	}
	int now, mn[N], mx[N], a[N], b[N], A, B, sz[N];
	bool flag;
	inline void dfs (int u, int fa)
	{
		sz[u] = 1;
		edge (i, u)
		{
			if (v == fa) continue;
			dfs(v, u);
			sz[u] += sz[v];
		}

		mx[u] = 1; mn[u] = 0;
		edge (i, u)
		{
			if (v == fa) continue;
			mx[u] += mx[v];
			mn[u] += mn[v];
		}

		mx[u] = std::min(mx[u], now - b[u]);
		mn[u] = std::max(a[u], mn[u]);
		if (mn[u] > mx[u] || mn[u] > now) flag = 0;
	}
	inline bool check ()
	{
		flag = 1;
		dfs(1, 0);
		return flag && mn[1] <= now && now <= mx[1];
	}
	int main ()
	{
		int T = read();
		while (T--)
		{
			n = read();
			clr(head); clr(a); clr(b); tot = 0;
			fo (i, 2, n)
			{
				int u = read(), v = read();
				addedge(u, v); addedge(v, u);
			}
			A = read();
			while (A--) 
			{
				int u = read();
				a[u] = std::max(read(), a[u]);
			}
			B = read();
			while (B--)
			{
				int u = read();
				b[u] = std::max(read(), b[u]);
			}
			int l = 0, r = n;
			while (l < r)
			{
				now = l + r >> 1;
				if (check()) r = now;
				else l = now + 1;
			}
			now = l;
			if (!check()) printf("-1\n"); 
			else printf("%d\n", l);
		}
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("6241");
#endif
	return 0;
}
