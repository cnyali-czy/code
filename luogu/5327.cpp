#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10, maxN = 2e7;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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
namespace lca
{
	const int maxn = ::maxn << 1;
	int p[maxn], dfs_clock, st[maxn][20], dep[maxn], pos[maxn], dfn[maxn], fa[maxn];
	void dfs(int x, int fa = 0)
	{
		lca :: fa[x] = fa;
		dfn[x] = ++dfn[0];
		dep[x] = dep[fa] + 1;
		st[pos[x] = ++dfs_clock][0] = x;
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dfs(to[i], x);
			st[++dfs_clock][0] = x;
		}
	}
	int lg[maxn];
	void init()
	{
		dfs(1);
		REP(i, 2, dfs_clock) lg[i] = lg[i >> 1] + 1;
		REP(j, 1, 19)
			REP(i, 1, dfs_clock - (1 << j) + 1)
			st[i][j] = dep[st[i][j-1]] < dep[st[i + (1 << j - 1)][j-1]] ? st[i][j-1] : st[i + (1 << j - 1)][j-1];
	}
	int qry(int x, int y)
	{
		if (!x || !y) return 0;
		int l = pos[x], r = pos[y];
		if (l > r) swap(l, r);
		int k = lg[r - l + 1];
		x = st[l][k];y = st[r - (1 << k) + 1][k];
		return dep[x] < dep[y] ? x : y;
	}
}
using lca :: dfn;
int ls[maxN], rs[maxN], s[maxN], f[maxN], c[maxN], t[maxN], rt[maxn], cur ;
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r
#define mid (l + r >> 1)

void pushup(int p)
{
	f[p] = f[ls[p]] + f[rs[p]] - lca :: dep[lca :: qry(s[rs[p]], t[ls[p]])];
	s[p] = s[ls[p]] ? s[ls[p]] : s[rs[p]];
	t[p] = t[rs[p]] ? t[rs[p]] : t[ls[p]];
}
inline int query(int p)
{
	return f[p] - lca :: dep[lca :: qry(s[p], t[p])];
}
void insert(int &p, int l, int r, int pos, int val)
{
	if (!p) p = ++cur;
	if (l == r)
	{
		c[p] += val;
		f[p] = c[p] ? lca :: dep[pos] : 0;
		s[p] = t[p] = c[p] ? pos : 0;
	}
	else
	{
		if (dfn[pos] <= mid)	insert(lson, pos, val);
		else					insert(rson, pos, val);
		pushup(p);
	}
}
void merge(int &x, int y, int l, int r)
{
	if (!x || !y) return void(x |= y);
	if (l == r)
	{
		c[x] += c[y];
		f[x] |= f[y];
		s[x] |= s[y];
		t[x] |= t[y];
		return;
	}
	merge(ls[x], ls[y], l, mid);
	merge(rs[x], rs[y], mid + 1, r);
	pushup(x);
}

vector <int> del[maxn];

long long ans;
void dfs(int x)
{
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ lca :: fa[x]) dfs(to[i]);
	for (auto i : del[x]) insert(rt[x], 1, n, i, -1);
	ans += query(rt[x]);
	if (lca :: fa[x]) merge(rt[lca :: fa[x]], rt[x], 1, n);
}

int main()
{
#ifdef CraZYali
	file("5327");
#endif
	n = read<int>();m = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		add(x, y);add(y, x);
	}
	lca :: init();
	while (m--)
	{
		int x(read<int>()), y(read<int>()), l(lca :: qry(x, y));
		insert(rt[x], 1, n, x, 1);insert(rt[x], 1, n, y, 1);
		insert(rt[y], 1, n, x, 1);insert(rt[y], 1, n, y, 1);
		del[l].emplace_back(x);del[l].emplace_back(y);
		del[lca :: fa[l]].emplace_back(x);del[lca :: fa[l]].emplace_back(y);
	}
	dfs(1);
	cout << ans / 2 << endl;
	return 0;
}
