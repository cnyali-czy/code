#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 30000 + 10;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
long long k[maxn], b[maxn], l[maxn], r[maxn], ans;
inline char Getchar(){
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
	template <typename T>
inline T read()
{
	register T ans(0);
	register char c(Getchar());
	while (!isdigit(c)) c = Getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = Getchar();
	}
	return ans;
}
inline void chkmin(int &x, int y) {if (x > y) x = y;}
inline void chkmax(long long &x, long long y) {if (x < y) x = y;}

int n, q;
int fa[maxn], dep[maxn], siz[maxn], hvy[maxn], top[maxn];

namespace seg
{
	const int maxN = 2e7;

	int cur, e[maxN], ls[maxN], rs[maxN];
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

	inline int gank(long long qaq) {return (qaq > 0) - (qaq < 0);}

	inline long long f(int id, int x)
	{
		if (!id || x < l[id] || x > r[id]) return 0;
		return k[id] * x + b[id];
	}

	void insert(int &p, int l, int r, int L, int R, int id)
	{
		if (!p) p = ++cur;
		if (L <= l && r <= R)
			if (!e[p]) e[p] = id;
			else
			{
				long long me = f(id, mid), hh_val = f(e[p], mid);
				switch (gank(me - hh_val))
				{
					case 1:
						if (l ^ r)
							switch (gank(k[id] - k[e[p]]))
							{
								case 1:
									insert(lson, L, R, e[p]);
									break;
								case -1:
									insert(rson, L, R, e[p]);
									break;
							}
						e[p] = id;
						break;
					case 0:
						if (l ^ r)
							switch (gank(k[id] - k[e[p]]))
							{
								case 1:
									insert(rson, L, R, e[p]);
									break;
								case -1:
									insert(lson, L, R, e[p]);
									break;
							}
						chkmin(e[p], id);
						break;
					case -1:
						if (l ^ r)
							switch (gank(k[id] - k[e[p]]))
							{
								case 1:
									insert(rson, L, R, id);
									break;
								case -1:
									insert(lson, L, R, id);
									break;
							}
						break;
				}
			}
		else
		{
			if (L <= mid)   insert(lson, L, R, id);
			if (R >  mid)   insert(rson, L, R, id);
		}
	}
	long long query(int p, int l, int r, int x)
	{
		if (l == r) return f(e[p], x);
		else
		{
			long long me = f(e[p], x), hh_val;
			if (x <= mid)	hh_val = query(lson, x);
			else			hh_val = query(rson, x);
			if (me > hh_val) return me;
			return hh_val;
		}
	}
}
void dfs1(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		dep[to[i]] = dep[x] + 1;
		fa[to[i]] = x;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}

vector <int> dog[maxn];
int pos[maxn], blg[maxn], L[maxn], R[maxn], cur, rtblg[maxn], block[maxn];
const int lim = 1e6;
void dfs2(int x, int y)
{
	pos[x] = dog[y].size();
	dog[y].emplace_back(x);
	top[x] = y;
	if (hvy[x])
	{
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i])
			if (to[i] ^ hvy[x] && to[i] ^ fa[x]) dfs2(to[i], to[i]);
	}
}

inline void doit(int i, int x)
{
	if (l[i] <= x && x <= r[i]) chkmax(ans, k[i] * x + b[i]);
}
inline void work(int u, int v, int x) // v is an an... of u
{
	if (blg[u] == blg[v])
	{
		REP(i, pos[v], pos[u])
			doit(dog[top[u]][i], x);
		return;
	}
	REP(i, pos[v], R[blg[v]]) doit(dog[top[u]][i], x);
	REP(i, L[blg[u]], pos[u]) doit(dog[top[u]][i], x);
	if (blg[u] - blg[v] > 1)
		REP(i, blg[v] + 1, blg[u] - 1)
			chkmax(ans, seg::query(rtblg[i], 0, lim, x));
}

signed main()
{
#ifdef CraZYali
	freopen("unknow.in", "r", stdin);
	freopen("unknow.out", "w", stdout);
#endif
	n = read<int>();
	q = read<int>();
	REP(i, 1, n)
	{
		k[i] = read<long long>();
		b[i] = read<long long>();
		l[i] = read<long long>();
		r[i] = read<long long>();
	}
	REP(i, 2, n)
	{
		int u(read<int>()), v(read<int>());
		add(u, v);add(v, u);
	}
	dfs1(1);
	dfs2(1, 1);
	REP(i, 1, n) if (i == top[i])
	{
		int _n = dog[i].size();
		block[i] = sqrt(_n);
		int l(0), r(block[i]-1);
		while (l < _n)
		{
			chkmin(r, _n - 1);
			++cur;
			L[cur] = l;
			R[cur] = r;
			REP(j, l, r) blg[dog[i][j]] = cur;
			l = r + 1;
			r += block[i];
		}
	}
	REP(i, 1, n) seg::insert(rtblg[blg[i]], 0, lim, l[i], r[i], i);

	while (q--)
	{
		int u(read<int>()), v(read<int>()), x(read<int>());
		ans = 0;
		if (top[u] == top[v])
		{
			if (dep[u] < dep[v]) swap(u, v);
			work(u, v, x);
			printf("%lld\n", ans);
			continue;
		}
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			work(u, top[u], x);
			u = fa[top[u]];
		}
		if (dep[u] < dep[v]) swap(u, v);
		work(u, v, x);
		printf("%lld\n", ans);
	}
	return 0;
}
