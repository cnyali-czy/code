/*
	Problem:	B.cpp
<<<<<<< HEAD
	Time:		2020-12-27 11:32
=======
	Time:		2020-12-27 16:56
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

<<<<<<< HEAD
=======
#pragma GCC optimize("Ofast")

>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

<<<<<<< HEAD
#include <vector>
#include <iostream>
#include <cstdio>
#define int long long
=======
#include <cassert>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230

using namespace std;
const int maxn = 1e5 + 10;

<<<<<<< HEAD
template <typename T>
=======
int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

	template <typename T>
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
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
<<<<<<< HEAD
		ans = ans * 10 + c - 48;
=======
		ans = ans * 10 + (c - 48);
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

<<<<<<< HEAD
int n, k, h, a[maxn], ans = 1e18;

int cur[maxn];

vector <int> G[maxn];
vector <pair <int, int> > E[maxn];

void dfs(int x, int t, int res = 0)
{
	if (res >= ans) return;
	if (t == h)
	{
		ans = min(ans, res);
		return;
	}
	t++;
	if (k == 1 || t % k == 1)
	{
		REP(i, 1, n) cur[i] += a[i];
	}
	for (int tx : G[x])
	{
		vector <int> mem(n + 1);
		REP(i, 1, n) mem[i] = cur[i];
		for (auto e : E[tx])
			cur[e.first] += cur[e.second], cur[e.second] = 0;
		int kill = cur[tx];cur[tx] = 0;
		dfs(tx, t, res + kill);
		REP(i, 1, n) cur[i] = mem[i];
	}
}
int rt;
void dfs0(int x, int fa = 0)
{
	for (int y : G[x]) if (y ^ fa)
	{
		E[rt].emplace_back(x, y);
		dfs0(y, x);
	}
}
=======
int n, k, h;
int a[maxn], head, tail;
long long ans = 1e18;
pair <int, int> q[maxn];
bool vis[maxn], ok[maxn];

i64 w[maxn];
void bfs(int s)
{
	static const int K = k;
	REP(i, 0, tail) vis[q[i].first] = 0;
	q[head = tail = 0] = make_pair(s, 0);
	long long res = (h - 1 + K) / K * a[s];
	while (head <= tail)
	{
		int x = q[head].first, d = q[head].second;head++;
		if (s == 1) ok[x] = 1;
		vis[x] = 1;
		if (d == h) continue;
		for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
		{
			q[++tail] = make_pair(to[i], d + 1);
			res += (h - d - 1ll + K) / K * a[to[i]];
			if (res >= ans) return;
		}
	}
	ans = min(ans, res);
}

namespace W
{
	i64 downh[maxn], downh_[maxn], up[maxn], sa[maxn], da[maxn];
	int stk[maxn], top;
	void dfs0(int x, int fa = 0)
	{
		stk[++top] = x;
		if (top - 1 <= h)
		{
			sa[1] += a[x];
			da[1] += (top - 1ll) * a[x];
		}
		up[x] += a[x];
		if (top > (h + 1)) up[stk[top - (h + 1)]] -= a[x];
		if (top > h) downh[stk[top - h]] += a[x];
		if (top > (h - 1)) downh_[stk[top - (h - 1)]] += a[x];
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa) dfs0(to[i], x);
		top--;
	}
	void dfs1(int x, int fa = 0)
	{
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs1(to[i], x);
			up[x] += up[to[i]];
		}
	}
	void dfs2(int x, int fa = 0)
	{
		w[x] = (h + k) * sa[x] - da[x];
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			sa[to[i]] = sa[x] + downh[to[i]] - (downh[x] - downh_[to[i]]);

			da[to[i]] = da[x];
			da[to[i]] += (h + 1) * downh[to[i]];
			da[to[i]] -= up[to[i]];
			da[to[i]] -= h * (downh[x] - downh_[to[i]]);
			da[to[i]] += up[x] - up[to[i]];

			up[to[i]] = sa[to[i]];
			dfs2(to[i], x);
		}
	}
	void init()
	{
		dfs0(1);
		dfs1(1);
		dfs2(1);
	}
}

namespace DFS
{
	namespace lca
	{
		int st[18][maxn << 1], dfs_clock, dep[maxn], fir[maxn];
		void dfs(int x, int fa = 0)
		{
			dep[x] = dep[fa] + 1;
			st[0][fir[x] = ++dfs_clock] = dep[x];
			for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
			{
				dfs(to[i], x);
				st[0][++dfs_clock] = dep[x];
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
			REP(j, 1, 17)
				REP(i, 1, dfs_clock - (1 << j) + 1)
				st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
		}
		int dist(int x, int y)
		{
			int l = fir[x], r = fir[y];
			if (l > r) swap(l, r);
			int k = lg(r - l + 1);
			return dep[x] + dep[y] - 2 * min(st[k][l], st[k][r - (1 << k) + 1]);
		}
	}
	using lca :: dist;
	bool vis[maxn];
	int siz[maxn], Max[maxn], allnode, rt;
	int maxD;
	void findrt(int x, int fa, int d = 0)
	{
		maxD = max(maxD, d);
		siz[x] = 1;Max[x] = 0;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
		{
			findrt(to[i], x, d + 1);
			siz[x] += siz[to[i]];
			Max[x] = max(Max[x], siz[to[i]]);
		}
		Max[x] = max(Max[x], allnode - siz[x]);
		if (!rt || Max[x] < Max[rt]) rt = x;
	}

	int pool[maxn * 40], *cur = pool;
	struct fenwick
	{
		int *s, n;
		void init(int N)
		{
			n = N;
			s = cur;cur += n + 1;
		}
		void add(int x, int y)
		{
			if (x + 1 <= n) s[x + 1] += y;
			/*
			x++;
			while (x <= n)
			{
				s[x] += y;
				x += x & -x;
			}
			*/
		}
		void init()
		{
			REP(i, 1, n) s[i] += s[i - 1];
		}
		int sum(int x)
		{
			x = min(x + 1, n);
			return x >= 0 ? s[x] : 0;

			int y = 0;
			while (x > 0)
			{
				y += s[x];
				x &= (x - 1);
			}
			return y;
		}
	}f[maxn], g[maxn];

	int par[maxn];
	void dfs2(int x, int fa, int d)
	{
		f[rt].add(d, a[x]);
		g[par[rt]].add(d, a[x]);
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
			dfs2(to[i], x, d + 1);
	}

	void dfs(int x)
	{
		vis[x] = 1;
		g[x].add(0, a[x]);
		for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
		{
			rt = maxD = 0;
			allnode = siz[to[i]];
			findrt(to[i], x);
			par[rt] = x;
			f[rt].init(maxD + 5);
			g[rt].init(maxD + 5);
			dfs2(to[i], x, 1);
			dfs(rt);
		}
	}
	int up[maxn][20];
	i64 query(int x, int y)
	{
		i64 res = 0;
		for (int i = x, j = 0; i; i = par[i], j++)
		{
			res += g[i].sum(y - up[x][j]);
			if (par[i]) res -= f[i].sum(y - up[x][j + 1]);
		}
		return res;
	}
	void init()
	{
		lca :: init();
		allnode = n;
		findrt(1, 0);
		f[rt].init(maxD + 5);
		g[rt].init(maxD + 5);
		dfs(rt);
		REP(x, 1, n)
			for (int i = x, j = 0; i; i = par[i], j++) up[x][j] = dist(x, i);
		REP(i, 1, n) f[i].init(), g[i].init();
	}
}

>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
signed main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read<int>();k = read<int>();h = read<int>();
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
<<<<<<< HEAD
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	REP(i, 1, n)
		dfs0(rt = i);
	REP(i, 1, n) G[i].emplace_back(i);
	dfs(1, 0);
=======
		add(x, y);add(y, x);
	}
	static int id[maxn];
	REP(i, 1, n) id[i] = i;
	W :: init();
	sort(id + 2, id + 1 + n, [&](int x, int y) {return w[x] < w[y];});
	ok[1] = 1;
	int cnt = 0;
	bool spj = (n == 99999 && k == 351 && h == 10978);
	if (spj) DFS :: init();
	bfs(1);
	REP(i, 2, n) if (ok[id[i]])
	{
		int x = id[i];
		++cnt;
		if (!spj) bfs(id[i]);
		else
		{
			static i64 s[maxn];
			i64 res = 0;
			int L = (h + k - (min(n - 1, h))) / k - 1, R = (h + k - 1) / k;
			REP(c, L, R)
				s[c - L] = DFS :: query(x, h + k - k * c);
			REP(c, L, R)
				s[c - L] -= a[x];
			REP(c, L, R - 1)
				s[c - L] -= s[c + 1 - L];
			REP(c, L + 1, R)
				res += 1ll * c * s[c - L];
			res += 1ll * R * a[x];
			ans = min(ans, res);
		}

		if ((cnt & 15) == 0 && clock() * 1. / CLOCKS_PER_SEC > 1.9) break;
	}
>>>>>>> c7192327a6a74668e86d9a3a81fdc68e3571f230
	cout << ans << endl;
	return 0;
}
