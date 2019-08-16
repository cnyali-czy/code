#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;
const int maxn = 100000 + 10, maxm = 100000 + 10, maxq = 100000 + 10, block_siz = 800;

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

int n, m, q, c[maxn];

int st[maxn], ed[maxn], back[maxn << 1], dfs_clock, top[maxn], fa[maxn], siz[maxn], hvy[maxn], depth[maxn];
void dfs1(int x)
{
	back[st[x] = ++dfs_clock] = x;
	siz[x] = 1;
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x])
		{
			fa[to[i]] = x;
			depth[to[i]] = depth[x] + 1;
			dfs1(to[i]);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
		}
	back[ed[x] = ++dfs_clock] = x;
}
void dfs2(int x, int y)
{
	top[x] = y;
	if (hvy[x]) dfs2(hvy[x], y);
	for (int i = bg[x]; i ; i = ne[i])
		if (to[i] ^ fa[x] && to[i] ^ hvy[x]) dfs2(to[i], to[i]);
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
int belong[maxn << 1];
struct query
{
	int l, r, t, spj, id;
	query(){}
	query(int _l, int _r, int _t, int _id, int _spj = 0) : l(_l), r(_r), t(_t), id(_id), spj(_spj) {}
	
}qlist[maxq];
inline bool operator < (query A, query B) {return belong[A.l] < belong[B.l] || (belong[A.l] == belong[A.l] && belong[A.r] < belong[B.r]) || (belong[A.l] == belong[B.l] && belong[A.r] == belong[B.r] && A.t < B.t);}
int cur, Q;
pair <int, int> cz[maxq];

long long ans, cnt[maxm], v[maxn], w[maxn];
bool vis[maxn];
int l, r, T;
inline void timego()
{
	T++;
	int x = cz[T].first, &b = cz[T].second, &a = c[x];
	
	if (!vis[x]) swap(a, b);
	else
	{
		ans -= w[(cnt[a]--)] * v[a];
		swap(a, b);
		ans += w[(++cnt[a])] * v[a];
	}
}
inline void timeback()
{
	int x = cz[T].first, &b = cz[T].second, &a = c[x];
	
	if (!vis[x]) swap(a, b);
	else
	{
		ans -= w[(cnt[a]--)] * v[a];
		swap(a, b);
		ans += w[(++cnt[a])] * v[a];
	}
	T--;
}
inline void add(int x)
{
	if (!vis[x]) ans += w[(++cnt[c[x]])] * v[c[x]];
	else ans -= w[(cnt[c[x]]--)] * v[c[x]];
	vis[x] ^= 1;
}
inline void del(int x)
{
	if (vis[x]) ans -= w[(cnt[c[x]]--)] * v[c[x]];
	else ans += w[(++cnt[c[x]])] * v[c[x]];
	vis[x] ^= 1;
}
bool needoutput[maxq];
long long realans[maxq];

signed main()
{
#ifdef CraZYali
	freopen("4074.in", "r", stdin);
	freopen("4074.out", "w", stdout);
#endif
	cin >> n >> m >> q;
	REP(i, 1, m) v[i] = read<int>();
	REP(i, 1, n) w[i] = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	REP(i, 1, n) c[i] = read<int>();
	dfs1(1);
	dfs2(1, 1);
	REP(i, 1, q)
	{
		int opt(read<int>()), x(read<int>()), y(read<int>());
		if (opt == 0) cz[++cur] = make_pair(x, y);
		else
		{
			needoutput[i] = 1;
			if (st[x] > st[y]) swap(x, y);
			int l(lca(x, y));
			if (x ^ l && y ^ l) qlist[++Q] = query(ed[x], st[y], cur, i, l);
			else qlist[++Q] = query(st[x], st[y], cur, i);
		}
	}
	REP(i, 1, n + n) belong[i] = i / block_siz;
	sort(qlist + 1, qlist + 1 + Q);
	REP(i, 1, Q)
	{
		while (T < qlist[i].t) timego();
		while (T > qlist[i].t) timeback();
		while (l < qlist[i].l) del(back[l++]);
		while (l > qlist[i].l) add(back[--l]);
		while (r < qlist[i].r) add(back[++r]);
		while (r > qlist[i].r) del(back[r--]);
		if (qlist[i].spj) add(qlist[i].spj);
		realans[qlist[i].id] = ans;
		if (qlist[i].spj) del(qlist[i].spj);
	}
	REP(i, 1, q) if (needoutput[i]) printf("%lld\n", realans[i]);
	return 0;
}
