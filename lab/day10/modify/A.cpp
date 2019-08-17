#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 1e5 + 10, maxm = maxn;

int bg[maxn], ne[maxm << 1], to[maxm << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

template <typename T> inline T read()
{
	T ans(0), p(1);
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

int n = 1, m;
int val[maxm];

struct opt
{
	int type, a, b;
}o[maxm];

int st[maxn], ed[maxn], back[maxn<<1], dfn[maxn], dfs_clock, ww[maxn], fa[maxn], top[maxn], siz[maxn], hvy[maxn], depth[maxn];
void dfs1(int x)
{
	back[st[x] = ++dfs_clock] = x;
	siz[x] = 1;
	for (int i = bg[x]; i ; i = ne[i])
	{
		depth[to[i]] = depth[x] + 1;
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
	back[ed[x] = ++dfs_clock] = x;
}
void dfs2(int x, int y)
{
	ww[dfn[x] = ++dfs_clock] = val[x];
	top[x] = y;
	if (hvy[x]) dfs2(hvy[x], y);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ hvy[x]) dfs2(to[i], to[i]);
}
inline int lca(int x, int y)
{
	while (top[x] ^ top[y])
	{
		if (depth[top[x]] < depth[top[y]]) swap(x, y);
		x = fa[top[x]];
	}
	return depth[x] < depth[y] ? x : y;
}
int belong[maxn<<1];
double ans[maxn];

int cnt[maxn], l, r, T;
long long sigma, sigma2, N;
#define bar ((double)sigma  / N)
#define S2 ((sigma2 + bar * bar * N - bar * sigma * 2) / N)

inline void add(long long c) {if (c && !cnt[c]++) sigma += c, sigma2 += c * c, N++;}
inline void del(long long c) {if (c && !--cnt[c]) sigma -= c, sigma2 -= c * c, N--;}
struct query
{
	int l, r, t, id, spj;
	query(int _l = 0, int _r = 0, int _id = 0, int _spj = 0, int _t = 0) : l(_l), r(_r), id(_id), spj(_spj), t(_t){}
}q[maxm];
inline bool operator < (query A, query B) {return belong[A.l] < belong[B.l] || (belong[A.l] == belong[B.l] && belong[A.r] < belong[B.r]) || (belong[A.l] == belong[B.l] && belong[A.r] == belong[B.r] && A.t < B.t);}
namespace path
{
	bool vis[maxn];
	inline void opt(int x)
	{
		if (vis[x]) del(val[x]);
		else add(val[x]);
		vis[x] ^= 1;
	}
	int Q;
	inline void work()
	{
		REP(i, 1, m)
			if (o[i].type == 2)
			{
				int x(o[i].a), y(o[i].b), l(lca(x, y));
				if (st[x] > st[y]) swap(x, y);
				if (l ^ x && l ^ y) q[++Q] = query(ed[x], st[y], i, l);
				else q[++Q] = query(st[x], st[y], i);
			}
		const int block_siz = ceil(sqrt(2 * n));
		REP(i, 1, n+n) belong[i] = i / block_siz;
		sort(q + 1, q + 1 + Q);
		REP(i, 1, Q)
		{
			while (l < q[i].l) opt(back[l++]);
			while (l > q[i].l) opt(back[--l]);
			while (r < q[i].r) opt(back[++r]);
			while (r > q[i].r) opt(back[r--]);
			if (q[i].spj) opt(q[i].spj);
			ans[q[i].id] = S2;
			if (q[i].spj) opt(q[i].spj);
		}
	}
}
int ade02[maxn], cur;
bool inside[maxn];
inline void timego()
{
	int x = ade02[++T];
	inside[dfn[x]] = 1;
	if (l <= dfn[x] && dfn[x] <= r) add(val[x]);
}
inline void timeback()
{
	int x = ade02[T--];
	inside[dfn[x]] = 0;
	if (l <= dfn[x] && dfn[x] <= r) del(val[x]);
}
inline void Add(int x) {if (inside[x]) add(ww[x]);}
inline void Del(int x) {if (inside[x]) del(ww[x]);}
inline void output()
{
	REP(i,1,100000)if(cnt[i])printf("%d ",i);putchar(10);
	printf("%d %lld %lld %lf\n", N, sigma, sigma2, S2);
}
namespace subtree
{
	int Q;
	void work()
	{
		inside[1] = 1;
		REP(i, 1, m)
			if (o[i].type == 1) ade02[++cur] = o[i].a;
			else if (o[i].type == 3) q[++Q] = query(dfn[o[i].a], dfn[o[i].a] + siz[o[i].a] - 1, i, 0, cur);
		if (!Q) return;
		const int block_siz = ceil(pow(1. * n * Q, 1. / 3));
		REP(i, 1, n) belong[i] = i / block_siz;
		sort(q + 1, q + 1 + Q);
		sigma = sigma2 = N = l = r = 0;
		memset(cnt, 0, sizeof(cnt));
		REP(i, 1, Q)
		{
			while (T < q[i].t) timego();
			while (T > q[i].t) timeback();
			while (l < q[i].l) Del(l++);
			while (l > q[i].l) Add(--l);
			while (r < q[i].r) Add(++r);
			while (r > q[i].r) Del(r--);
			ans[q[i].id] = S2;
		}
	}
}

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> m >> val[1];
	REP(i, 1, m)
	{
		int type(read<int>()), a(read<int>());
		if (type == 1)
		{
			++n;
			o[i] = opt{type, a};
			val[a] = read<int>();
			add(fa[a] = read<int>(), a);
		}
		else if (type == 2) o[i] = opt{type, a, read<int>()};
		else o[i] = opt{type, a};
	}
	dfs1(1);dfs_clock = 0;
	dfs2(1, 1);
	path::work();
	subtree::work();
	REP(i, 1, m)
		if (o[i].type > 1) printf("%.10lf\n", ans[i]);
	return 0;
}
