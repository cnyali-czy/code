#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 1e5 + 10;

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

int n, a[maxn], A[maxn], b[maxn], m;

i64 ans[maxn];

int allnode, rt;
int siz[maxn], Max[maxn];
bool vis[maxn];
void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		Max[x] = max(Max[x], siz[to[i]]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
int dep[maxn], stk[maxn], mina[maxn], top, blg[maxn], cnt;
void dfs2(int x, int y = 0, int fa = 0)
{
	blg[x] = y;
	stk[++top] = x;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa && !vis[to[i]])
	{
		mina[to[i]] = min(mina[x], a[to[i]]);
		dep[to[i]] = dep[x] + 1;
		dfs2(to[i], fa ? y : ++cnt, x);
	}
}

namespace fenwick
{
	int s[maxn], dfn[maxn], c;
	void add(int x, int y)
	{
		while (x > 0)
		{
			if (dfn[x] ^ c) dfn[x] = c, s[x] = 0;
			s[x] = max(s[x], y);
			x &= (x - 1);
		}
	}
	int qry(int x)
	{
		int res = 0;
		while (x <= m)
		{
			if (dfn[x] == c) res = max(res, s[x]);
			x += x & -x;
		}
		return res;
	}
	void clear() {c++;}
}

struct func
{
	i64 k, b;
	func() {}
	func(i64 k, i64 b) : k(k), b(b) {}
	inline i64 operator [] (i64 x) {return k * x + b;}
};
namespace LC
{
	const int maxN = 2e7;
	struct node
	{
		int ls, rs;
		func f;
		node() {ls = rs = 0;}
	}t[maxN];
#define lson t[p].ls, l, mid
#define rson t[p].rs, mid + 1, r
#define mid (l + r >> 1)
	int cur;
	void clear()
	{
		REP(i, 1, cur) t[i].ls = t[i].rs = 0;
		cur = 0;
	}
	void update(int &p, int l, int r, func f)
	{
		if (!p)
		{
			t[p = ++cur].f = f;
			return;
		}
		i64 Newval = f[mid], Oldval = t[p].f[mid];
		if (Newval > Oldval) swap(t[p].f, f);
		if (l == r) return;
		if (f.k < t[p].f.k && f[l] > t[p].f[l]) update(lson, f);
		if (f.k > t[p].f.k && f[r] > t[p].f[r]) update(rson, f);
	}
	i64 query(int p, int l, int r, int pos)
	{
		if (!p) return 0;
		return max(t[p].f[pos], pos <= mid ? query(lson, pos) : query(rson, pos));
	}
}

void calc(int x, int ax, int d)
{
	top = 0;
	dep[x] = d;
	mina[x] = ax;
	cnt = 0;
	dfs2(x);
	sort(stk + 1, stk + 1 + top, [&](int x, int y) {return mina[x] < mina[y];});
	m = 0;
	REP(i, 1, top) b[++m] = mina[stk[i]];
	sort(b + 1, b + 1 + m);m = unique(b + 1, b + 1 + m) - b - 1;
	REP(i, 1, top) A[stk[i]] = lower_bound(b + 1, b + 1 + m, mina[stk[i]]) - b;

	static int Cnt[maxn], pool[maxn << 1], *st[maxn];
	REP(i, 1, top) Cnt[blg[stk[i]]]++;
	int *cur = pool;
	REP(i, 0, cnt) st[i] = cur, cur += Cnt[i], Cnt[i] = 0;
	REP(i, 1, top)
	{
		int u = stk[i];
		st[blg[u]][Cnt[blg[u]]++] = u;
	}

	fenwick :: clear();
	REP(i, 0, cnt)
	{
		REP(j, 0, Cnt[i] - 1)
		{
			int u = st[i][j];
			ans[u] = max(ans[u], (dep[u] + fenwick :: qry(A[u]) + 1ll) * mina[u]);
		}
		REP(j, 0, Cnt[i] - 1)
		{
			int u = st[i][j];
			fenwick :: add(A[u], dep[u]);
		}
	}
	fenwick :: clear();
	DEP(i, cnt, 0)
	{
		REP(j, 0, Cnt[i] - 1)
		{
			int u = st[i][j];
			ans[u] = max(ans[u], (dep[u] + fenwick :: qry(A[u]) + 1ll) * mina[u]);
		}
		REP(j, 0, Cnt[i] - 1)
		{
			int u = st[i][j];
			fenwick :: add(A[u], dep[u]);
		}
	}
	
	static int rt1[maxn], rt2[maxn];
	LC :: clear();
	int M = cnt + 5, md = 0;
	REP(i, 0, M) rt1[i] = rt2[i] = 0;
	REP(i, 1, top) md = max(md, dep[stk[i]]);
	md += 5;
	REP(i, 1, top)
	{
		int u = stk[i], B = blg[u];
		func f(mina[u], (1ll + dep[u]) * mina[u]);
		i64 val = 0;
		for (int x = B - 1 + 1; x > 0; x &= (x - 1))
			val = max(val, LC :: query(rt1[x], 0, md, dep[u]));
		for (int x = B + 1 + 1; x <= M; x += x & -x)
			val = max(val, LC :: query(rt2[x], 0, md, dep[u]));

		ans[u] = max(ans[u], val);

		for (int x = B + 1; x > 0; x &= (x - 1))
			LC :: update(rt2[x], 0, md, f);
		for (int x = B + 1; x <= M; x += x & -x)
			LC :: update(rt1[x], 0, md, f);
	}
}
void dfs(int x)
{
	vis[x] = 1;
	calc(x, a[x], 0);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		allnode = siz[to[i]];
		rt = 0;
		findrt(to[i]);
		dfs(rt);
	}
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n) ans[i] = a[i] = b[i] = read<int>();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	allnode = n;
	findrt(1);
	dfs(rt);
	REP(i, 1, n) printf("%lld%c", ans[i], i == end_i ? '\n' : ' ');
	return 0;
}
