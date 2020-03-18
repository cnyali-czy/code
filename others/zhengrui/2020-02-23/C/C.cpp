/*
	Problem:	C.cpp
	Time:		2020-02-23 10:27
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#include <set>
#include <ext/pb_ds/priority_queue.hpp>
#include <queue>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1e5 + 10, maxm = 2e5 + 10;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
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

int n, m, k, q;
bool col[maxn];
namespace tree
{
	inline int min(const int &x, const int &y) {if (x < y) return x;return y;}
	namespace lca
	{
		int st[maxn << 1][20], dfn, lg[maxn << 1], dep[maxn], fir[maxn];
		void dfs(int x, int fa = 0)
		{
			st[++dfn][0] = dep[x];
			fir[x] = dfn;
			for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
			{
				dep[to[i]] = dep[x] + 1;
				dfs(to[i], x);
				st[++dfn][0] = dep[x];
			}
		}
		inline int qry(int x, int y)
		{
			int l(fir[x]), r(fir[y]);if (l > r) swap(l, r);
			int k = lg[r - l + 1];
			return min(st[l][k], st[r - (1 << k) + 1][k]);
		}
		inline int dist(int x, int y) {return dep[x] + dep[y] - 2 * qry(x, y);}
		void init()
		{
			dfs(1);
			REP(i, 2, dfn) lg[i] = lg[i >> 1] + 1;
			REP(j, 1, 19)
				REP(i, 1, dfn + 1 - (1 << j))
				st[i][j] = min(st[i][j-1], st[i + (1 << j-1)][j-1]);
		}
	}
	using lca::dist;
	struct bit
	{
		int n, *c;
		inline void init(int _n)
		{
			n = _n + 1;
			c = new int[n + 1];
			REP(i, 0, n) c[i] = 0;
		}
		void add(int x, int y) {for (; x <= n; x += x & -x) c[x] += y;}
		int sum(int x) {int res = 0;for (chkmin(x, n); x > 0; x &= (x - 1)) res += c[x];return res;}
	}g[maxn], f[maxn];

	int siz[maxn], Max[maxn], rt, allnode;
	bool vis[maxn];
	void findrt(int x, int fa = 0)
	{
		siz[x] = 1;Max[x] = 0;
		for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
		{
			findrt(to[i], x);
			siz[x] += siz[to[i]];
			chkmax(Max[x], siz[to[i]]);
		}
		chkmax(Max[x], allnode - siz[x]);
		if (!rt || Max[x] < Max[rt]) rt = x;
	}

	int par[maxn];

	void dfs(int x)
	{
		vis[x] = 1;
		for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
		{
			rt = 0;
			allnode = siz[to[i]];
			findrt(to[i]);
			par[rt] = x;
			f[rt].init(allnode);g[rt].init(allnode);
			dfs(rt);
		}
	}

	void update(int x)
	{
		for (int i = x; i; i = par[i])
		{
			g[i].add(dist(x, i) + 1, 1);
			if (par[i]) f[i].add(dist(par[i], x) + 1, 1);
		}
		col[x] = 1;
	}
	int query(int x, int k)
	{
		int res = 0;
		for (int i = x; i; i = par[i])
		{
			res += g[i].sum(k - dist(i, x) + 1);
			if (par[i]) res -= f[i].sum(k - dist(par[i], x) + 1);
		}
		return res;
	}

	int main()
	{
		REP(i, 2, n)
		{
			int x(read<int>()), y(read<int>());
			add(x, y);add(y, x);
		}
		lca::init();
		allnode = n;
		findrt(1);
		f[rt].init(n);g[rt].init(n);
		dfs(rt);
		q = read<int>();
		while(q--)
		{
			int opt(read<int>()), x(read<int>());
			if (opt == 1) update(x);
			else
			{
				int l = 0, r = n;
				while (l < r)
				{
					int mid = l + r >> 1;
					if (query(x, mid)) r = mid;
					else l = mid + 1;
				}
				cout << r << '\n';
			}
		}
		return 0;
	}
}

namespace bf
{
	int q[maxn], head, tail, d[maxn];
	int bfs(int S)
	{
		REP(i, 1, n) d[i] = -1;
		d[S] = 0;
		q[head = tail = 0] = S;
		while (head <= tail)
		{
			int x = q[head++];
			if (col[x]) return d[x];
			for (int i = bg[x]; i; i = ne[i]) if (d[to[i]] == -1)
				d[q[++tail] = to[i]] = d[x] + 1;
		}
		return 114514;
	}
	void work()
	{
		while (m--)
		{
			int x(read<int>()), y(read<int>());
			add(x, y);add(y, x);
		}
		::q = read<int>();
		while (::q--)
		{
			int opt = read<int>(), x = read<int>();
			if (opt == 1) col[x] = 1;
			else printf("%d\n", bfs(x));
		}
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m >> k;
	if (n <= 1000) bf::work();
	else return tree::main();
	return 0;
}
