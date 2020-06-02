#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

inline void chkmax(int &x, int y) {if (x < y) x = y;}

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 7e4 + 10;

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
int u[maxn], v[maxn];

namespace lca
{
	const int maxn = ::maxn << 1;
	int p[maxn], dfs_clock, st[maxn][20], dep[maxn], pos[maxn];
	void dfs(int x, int fa = 0)
	{
		st[pos[x] = ++dfs_clock][0] = dep[x];
		for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa)
		{
			dep[to[i]] = dep[x] + 1;
			dfs(to[i], x);
			st[++dfs_clock][0] = dep[x];
		}
	}
	int lg[maxn];
	void init()
	{
		dfs(1);
		REP(i, 2, dfs_clock) lg[i] = lg[i >> 1] + 1;
		REP(j, 1, 19)
			REP(i, 1, dfs_clock - (1 << j) + 1)
			st[i][j] = min(st[i][j-1], st[i + (1 << j - 1)][j-1]);
	}
	int qry(int x, int y)
	{
		int l = pos[x], r = pos[y];
		if (l > r) swap(l, r);
		int k = lg[r - l + 1];
		return min(st[l][k], st[r - (1 << k) + 1][k]);
	}
	inline int dist(int x, int y) {return dep[x] + dep[y] - 2 * qry(x, y);}
}
using lca::dist;


vector <pair <int, int> > V[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
#define mid (l + r >> 1)

void insert(int p, int l, int r, int L, int R, int x, int y)
{
	if (L <= l && r <= R) V[p].emplace_back(x, y);
	else
	{
		if (L <= mid) insert(lson, L, R, x, y);
		if (R >  mid) insert(rson, L, R, x, y);
	}
}
int fa[maxn], siz[maxn];
int find(int x) {return x == fa[x] ? x : find(fa[x]);}

stack <pair <int, int> > S, Suv;
int ans;
void Upd(int x, int y)
{
	int d1 = dist(x, v[y]), d2 = dist(u[y], x), dd = dist(u[y], v[y]);
	if (d1 >= d2 && d1 >= dd) u[y] = x;
	if (d1 <  d2 && d2 >= dd) v[y] = x;
}
void uni(int x, int y)
{
	int xx = x, yy = y;
	x = find(x);y = find(y);
	if (siz[x] > siz[y]) swap(x, y);
	S.emplace(x, fa[x]);
	Suv.emplace(u[y], v[y]);
	fa[x] = y;
	siz[y] += siz[x];
	Upd(u[x], y);Upd(v[x], y);
	chkmax(ans, dist(u[y], v[y]));
}
void undo()
{
	int x = S.top().first, y = S.top().second;
	S.pop();
	int u = Suv.top().first, v = Suv.top().second;
	Suv.pop();
	::u[fa[x]] = u;::v[fa[x]] = v;
	siz[fa[x]] -= siz[x];
	fa[x] = y;
}

int Ans[maxn];
void dfs(int p, int l, int r)
{
	int lstans = ans;
	for (auto i : V[p])
		uni(i.first, i.second);
	int curans = ans;
	if (l == r)
	{
//		printf("pos = %d\n", l);
//		REP(i, 1, n) printf("%d%c", find(i), i == n ? '\n' : ' ');
//		REP(i, 1, n) if (i == fa[i]) printf("%d %d %d\n", i, u[i], v[i]);
//		cout << "ans = " << ans << endl << endl;
		Ans[l] = ans;
	}
	else
	{
		dfs(lson);ans = curans;
		dfs(rson);ans = lstans;
	}
	REP(i, 1, V[p].size()) undo();
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();m = read<int>();
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>()), l(read<int>()), r(read<int>());
		add(x, y);add(y, x);
		insert(1, 1, n, l, r, x, y);
	}
	REP(i, 1, n) siz[fa[i] = i] = 1, u[i] = v[i] = i;
	lca :: init();
	dfs(1, 1, n);
	while (m--) printf("%d\n", Ans[read<int>()]);
	return 0;
}
