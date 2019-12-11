#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#include <ctime>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 1e5 + 10, maxq = 1e5 + 10, lim = 1e6;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
long long k[maxn], b[maxn];
int l[maxn], r[maxn];
int dfn[maxn], back[maxn];

long long ans[maxq];
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

#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
namespace seg
{
	const int maxN = 2e7;

	int Stack[maxN], top;
	inline void init()
	{
		REP(i, 1, maxN - 5) Stack[++top] = i;
	}
	int cur, e[maxN], ls[maxN], rs[maxN];
	inline int newnode() {return Stack[top--];}
	inline int gank(long long qaq) {return (qaq > 0) - (qaq < 0);}

	inline long long f(int id, int x)
	{
		if (!id || x < l[id] || x > r[id]) return 0;
		return k[id] * x + b[id];
	}
	void insert(int &p, int l, int r, int id)
	{
		if (!p) p = newnode();
		if (!e[p])
		{
			e[p] = id;
			return;
		}
		if (f(e[p], mid) <= f(id, mid)) swap(e[p], id);
		int L(max(l, ::l[id])), R(min(r, ::r[id]));
		bool flagl(0), flagr(0);
		if (f(id, L) > f(e[p], L))
			if (L <= mid) flagl = 1;
			else flagr = 1;
		if (f(id, R) > f(e[p], R))
			if (R <= mid) flagl = 1;
			else flagr = 1;
		if (flagl) insert(lson, id);
		if (flagr) insert(rson, id);
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
	void clear(int &p)
	{
		if (!p) return;
		clear(ls[p]);
		clear(rs[p]);
		Stack[++top] = p;
		e[p] = 0;
		p = 0;
	}
}
#undef mid
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
void dfs2(int x, int y)
{
	back[dfn[x] = ++dfn[0]] = x;
	dog[y].emplace_back(x);
	top[x] = y;
	if (hvy[x])
	{
		dfs2(hvy[x], y);
		for (int i = bg[x]; i; i = ne[i])
			if (to[i] ^ hvy[x] && to[i] ^ fa[x]) dfs2(to[i], to[i]);
	}
}

inline long long doit(int i, int x)
{
	if (l[i] <= x && x <= r[i]) return k[i] * x + b[i];
	return 0;
}
vector <pair <int, pair <int, int> > > qaq[maxn][2];
int p[maxn][2];
void cdq(int l, int r)
{
	int mid = l + r >> 1;
	if (l == r)
	{
		int siz0(qaq[l][0].size()), siz1(qaq[l][1].size());
		while (p[l][0] < siz0 && qaq[l][0][p[l][0]].first == r)
		{
			chkmax(ans[qaq[l][0][p[l][0]].second.second], doit(back[l], qaq[l][0][p[l][0]].second.first));
			p[l][0]++;
		}
		while (p[l][1] < siz1 && qaq[l][1][p[l][1]].first == l)
		{
			chkmax(ans[qaq[l][1][p[l][1]].second.second], doit(back[l], qaq[l][1][p[l][1]].second.first));
			p[l][1]++;
		}
		return;
	}
	cdq(l, mid);cdq(mid + 1, r);
	bool flagl(0), flagr(0);
	REP(i, l, mid)
		if (p[i][0] < qaq[i][0].size() && qaq[i][0][p[i][0]].first <= r)
		{
			flagl = 1;
			break;
		}
	REP(i, mid + 1, r)
		if (p[i][1] < qaq[i][1].size() && qaq[i][1][p[i][1]].first >= l)
		{
			flagr = 1;
			break;
		}
	int lrt(0), rrt(0);
	if (flagl)
		DREP(i, mid, l)
		{
			seg::insert(lrt, 0, lim, back[i]);
			int siz0(qaq[i][0].size());
			while (p[i][0] < siz0 && qaq[i][0][p[i][0]].first <= r)
			{
				chkmax(ans[qaq[i][0][p[i][0]].second.second], seg::query(lrt, 0, lim, qaq[i][0][p[i][0]].second.first));
				p[i][0]++;
			}
		}
	if (flagr)
		REP(i, mid + 1, r)
		{
			seg::insert(rrt, 0, lim, back[i]);
			int siz1(qaq[i][1].size());
			while (p[i][1] < siz1 && qaq[i][1][p[i][1]].first >= l)
			{
				chkmax(ans[qaq[i][1][p[i][1]].second.second], seg::query(rrt, 0, lim, qaq[i][1][p[i][1]].second.first));
				p[i][1]++;
			}
		}
	seg::clear(lrt);
	seg::clear(rrt);
}
vector <pair <int, int> > ask[maxn];
signed main()
{
#ifdef CraZYali
	freopen("unknow.in", "r", stdin);
	freopen("unknow.out", "w", stdout);
#endif
	seg::init();
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
	REP(i, 1, q)
	{
		int u(read<int>()), v(read<int>()), x(read<int>());
		while (top[u] ^ top[v])
		{
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			ask[u].emplace_back(x, i);
			u = fa[top[u]];
		}
		if (dep[u] > dep[v]) swap(u, v);
		qaq[dfn[u]][0].emplace_back(dfn[v], make_pair(x, i));
		qaq[dfn[v]][1].emplace_back(dfn[u], make_pair(x, i));
	}
	REP(i, 1, n) if (top[i] == i)
	{
		int rt(0);
		for (auto j : dog[i])
		{
			seg::insert(rt, 0, lim, j);
			for (auto k : ask[j])
				chkmax(ans[k.second], seg::query(rt, 0, lim, k.first));
		}
		seg::clear(rt);
	}
	REP(i, 1, n)
	{
		sort(qaq[i][0].begin(), qaq[i][0].end());
		sort(qaq[i][1].begin(), qaq[i][1].end());
		reverse(qaq[i][1].begin(), qaq[i][1].end());
	}
	cdq(1, n);
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
#endif
	REP(i, 1, q) printf("%lld\n", ans[i]);
	return 0;
}
