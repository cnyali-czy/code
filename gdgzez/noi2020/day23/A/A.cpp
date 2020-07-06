
#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#define i64 long long
#define int i64
using namespace std;
const int maxn = 1e5 + 10;

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

struct Tree
{
	int bg[maxn], ne[maxn << 1], to[maxn << 1], w[maxn << 1], e;
	i64 dis[maxn];
	int dep[maxn], st[maxn << 1][20], dfn[maxn], dfs_clock;
	void clear() 
	{
		memset(bg, 0, sizeof bg);
		e = 0;
	}
	Tree() {clear();}
	inline void add(int x, int y, int z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
	void dfs(int x, int fa = 0)
	{
		dfs_clock++;
		dfn[x] = dfs_clock;
		st[dfs_clock][0] = x;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dis[to[i]] = dis[x] + w[i];
			dep[to[i]] = dep[x] + 1;
			dfs(to[i], x);
			st[++dfs_clock][0] = x;
		}
	}
	int lg[maxn << 1];
	void init()
	{
		dep[1] = dis[1] = 0;
		dfs(1);
		REP(i, 2, n + n) lg[i] = lg[i >> 1] + 1;
		DEP(i, dfs_clock, 1)
			REP(j, 1, 19) if (i + (1 << j) - 1 <= dfs_clock)
			{
				int d1 = dep[st[i][j - 1]], d2 = dep[st[i + (1 << j - 1)][j - 1]];
				if (d1 < d2)	st[i][j] = st[i][j - 1];
				else			st[i][j] = st[i + (1 << j - 1)][j - 1];
			}else break;
	}
	inline int lca(int l, int r)
	{
		l = dfn[l], r = dfn[r];
		if (l > r) swap(l, r);
		int k = lg[r - l + 1];
		int d1 = dep[st[l][k]], d2 = dep[st[r - (1 << k) + 1][k]];
		if (d1 < d2)	return st[l][k];
		else			return st[r - (1 << k) + 1][k];
	}
	inline int dist(int x, int y)
	{
		return dis[x] + dis[y] - dis[lca(x, y)] * 2;
	}
}T0, T1;
#define fo(i, x) for (int i = T0.bg[x], y = T0.to[i]; i; y = T0.to[i = T0.ne[i]]) 
int siz[maxn], Max[maxn], rt, allnode;
bool vis[maxn];
void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	fo(i, x) if (y ^ fa && !vis[y])
	{
		findrt(y, x);
		siz[x] += siz[y];
		chkmax(Max[x], siz[y]);
	}
	chkmax(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
int st[maxn], top;
i64 ans[maxn];
bool great[maxn];
i64 dis[maxn];
void getall(int x, int fa = 0)
{
	st[++top] = x;
	fo(i, x) if (!vis[y] && y ^ fa)
	{
		dis[y] = dis[x] + T0.w[i];
		getall(y, x);
	}
}

#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)
#define ls p << 1
#define rs p << 1 | 1

int good[maxn], gd, back[maxn];
i64 Min[maxn << 2], tag[maxn << 2];
const i64 inf = 1e15;
void build(int p, int l, int r)
{
	tag[p] = 0;
	if (l == r) Min[p] = great[back[l]] ? dis[back[l]] + T1.dist(1, back[l]) : inf;
	else
	{
		build(lson);
		build(rson);
		Min[p] = min(Min[ls], Min[rs]);
	}
}
void maintain(int p, i64 val)
{
	tag[p] += val;
	Min[p] += val;
}
void pushdown(int p)
{
	maintain(ls, tag[p]);
	maintain(rs, tag[p]);
	tag[p] = 0;
}
void update(int p, int l, int r, int L, int R, i64 val)
{
	if (L <= l && r <= R) maintain(p, val);
	else
	{
		if (tag[p]) pushdown(p);
		if (L <= mid) update(lson, L, R, val);
		if (R >  mid) update(rson, L, R, val);
		Min[p] = min(Min[ls], Min[rs]);
	}
}
i64 query(int p, int l, int r, int L, int R)
{
	if (L <= l && r <= R) return Min[p];
	else
	{
		if (tag[p]) pushdown(p);
		if (R <= mid) return query(lson, L, R);
		if (L >  mid) return query(rson, L, R);
		return min(query(lson, L, R), query(rson, L, R));
	}
}
namespace Vtree
{
	int stk[maxn], Top;
	int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
	i64 w[maxn << 1];
	inline void add(int x, int y, i64 z)
	{
		e++;
		to[e] = y;
		ne[e] = bg[x];
		bg[x] = e;
		w[e] = z;
	}
	inline void Add(int x, int y)
	{
		i64 z = T1.dist(x, y);
		add(x, y, z);
		add(y, x, z);
	}
	int dfn[maxn], siz[maxn], dfs_clock;
	void dfs(int x, int fa = 0)
	{
		dfn[x] = ++dfs_clock;
		back[dfs_clock] = x;
		siz[x] = 1;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs(to[i], x);
			siz[x] += siz[to[i]];
		}
	}
	void calc(int x, int fa = 0)
	{
		if (great[x])
		{
			i64 tmp = inf;
			if (1 <= dfn[x] - 1)	chkmin(tmp, query(1, 1, gd, 1, dfn[x] - 1));
			if (dfn[x] + 1 <= gd)	chkmin(tmp, query(1, 1, gd, dfn[x] + 1, gd));
			/*
			i64 ccc = inf;
			REP(i, 1, top) if (st[i] ^ x)
			{
				auto a1 = T1.dist(st[i], x) + dis[st[i]];
				auto a2 = query(1, 1, gd, dfn[st[i]], dfn[st[i]]);
				chkmin(ccc, a1);
				if (a1 ^ a2) fprintf(stderr, "%lld %lld\n", T1.dist(st[i], x) + dis[st[i]], query(1, 1, gd, dfn[st[i]], dfn[st[i]]));
			}
			cerr << ccc << ' ' << tmp << endl;
			*/
			chkmin(ans[x], dis[x] + tmp);
		}
		//		cout << x << ' ' << dis[x] << ' ' << tmp << endl;
		//		REP(i, 1, gd) printf("%d%c", query(1, 1, gd, dfn[i], dfn[i]), i == end_i ? '\n' : ' ');
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			maintain(1, w[i]);
			update(1, 1, gd, dfn[to[i]], dfn[to[i]] + siz[to[i]] - 1, -2 * w[i]);
			calc(to[i], x);
			maintain(1, -w[i]);
			update(1, 1, gd, dfn[to[i]], dfn[to[i]] + siz[to[i]] - 1, 2 * w[i]);
		}
	}
	void work()
	{
		if (top < 2) return;
		e = 0;
		stk[Top = 1] = 1;
		good[gd = 1] = 1;
		bg[1] = 0;
		sort(st + 1, st + 1 + top, [&](int x, int y){return T1.dfn[x] < T1.dfn[y];});
		REP(i, 1 + (st[1] == 1), top)
		{
			int l = T1.lca(st[i], stk[Top]);
			if (l ^ stk[Top])
			{
				while (T1.dfn[l] < T1.dfn[stk[Top - 1]])
				{
					Add(stk[Top - 1], stk[Top]);
					Top--;
				}
				if (l ^ stk[Top - 1])
				{
					good[++gd] = l;
					bg[l] = 0;
					Add(l, stk[Top]);
					stk[Top] = l;
				}
				else Add(l, stk[Top--]);
			}
			stk[++Top] = st[i];
			good[++gd] = st[i];
			bg[st[i]] = 0;
		}
		while (Top > 1)
		{
			Add(stk[Top - 1], stk[Top]);
			Top--;
		}
		REP(i, 1, top) great[st[i]] = 1;
		dfs_clock = 0;
		dfs(1);
		build(1, 1, gd);
		calc(1);
		REP(i, 1, top) great[st[i]] = 0;
		/*
		   cerr << endl;
		   REP(i, 1, top) printf("%d%c", st[i], i == end_i ? '\n' : ' ');
		   printf("Tree : \n");
		   REP(i, 1, gd) printf("%d%c", good[i], i == end_i ? '\n' : ' ');
		   REP(i, 1, gd) printf("%d%c", dfn[good[i]], i == end_i ? '\n' : ' ');
		   REP(x, 1, n) for (int i = bg[x]; i; i = ne[i]) printf("%d %d %lld\n", x, to[i], w[i]);
		   puts("");
		   */
	}
};

void dfs(int x, int fa = 0)
{
	vis[x] = 1;
	top = 0;
	dis[x] = 0;
	getall(x, fa);
	/*
	   REP(i, 1, top)
	   REP(j, i + 1, top)
	   {
	   int x = st[i], y = st[j];
	   i64 res = dis[x] + dis[y] + T1.dist(x, y);
	   chkmin(ans[x], res);
	   chkmin(ans[y], res);
	   }
	   */
	Vtree :: work();
	fo(i, x) if (y ^ fa && !vis[y])
	{
		allnode = siz[y];
		rt = 0;
		findrt(y, x);
		dfs(rt, x);
	}
}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	n = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		T0.add(x, y, z);T0.add(y, x, z);
	}
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), z(read<int>());
		T1.add(x, y, z);T1.add(y, x, z);
	}
	T0.init();T1.init();
	memset(ans, 127, sizeof ans);
	allnode = n;
	findrt(1);
	dfs(rt);
	i64 Ans = 0;
	REP(i, 1, n) Ans ^= ans[i];
	/*
	   REP(i, 1, n) REP(j,1 , n) printf("%d%c", T0.lca(i,j),j==n?'\n':' ');puts(""); 
	   REP(i, 1, n) REP(j,1 , n) printf("%d%c", T0.dist(i,j),j==n?'\n':' ');puts(""); 
	   REP(i, 1, n) REP(j,1 , n) printf("%d%c", T1.lca(i,j),j==n?'\n':' ');puts(""); 
	   REP(i, 1, n) REP(j,1 , n) printf("%d%c", T1.dist(i,j),j==n?'\n':' ');puts(""); 
	   */
#ifdef CraZYali
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	REP(i, 1, n) cout << ans[i] << endl;
#endif
	cout << Ans << endl;
	return 0;
}
