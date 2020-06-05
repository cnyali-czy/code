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
#include <set>
#define getchar getchar_unlocked
using namespace std;
const int maxn = 2e5 + 10, maxN = maxn << 2, inf = 2e9;
#define i64 long long
int bg[maxn], ne[maxn], to[maxn], e;
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

int n, q;

int A[maxn], blg[maxn], k, rt[maxn];
set <pair <int, int> > S;

int fa[maxn], top[maxn], siz[maxn], hvy[maxn], dep[maxn], dfn[maxn], dfs_clock;
void dfs1(int x)
{
	dep[x] = dep[fa[x]] + 1;
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i])
	{
		dfs1(to[i]);
		siz[x] += siz[to[i]];
		if (siz[to[i]] > siz[hvy[x]]) hvy[x] = to[i];
	}
}
void dfs2(int x, int y)
{
	dfn[x] = ++dfs_clock;
	top[x] = y;
	if (!hvy[x]) return;
	dfs2(hvy[x], y);
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ hvy[x])
		dfs2(to[i], to[i]);
}

struct fenwick
{
	i64 s[maxn];
	fenwick() {memset(s, 0, sizeof s);}
	void add(int x, int y)
	{
		while (x <= n)
		{
			s[x] += y;
			x += x & -x;
		}
	}
	i64 sum(int l, int r)
	{
		l--;
		i64 ans = 0;
		while (r > l) ans += s[r], r &= (r - 1);
		while (l > r) ans -= s[l], l &= (l - 1);
		return ans;
	}
}f1;
bool flag;
i64 w[maxn], qaq[maxn];
i64 query(int x, int y)
{
	if (blg[x] ^ blg[y]) return flag = 0;
	/*
	if (x == y)
	{
		int z = fa[x];
		if (!z) return -1;
		return f1.sum(dfn[z], dfn[x]) + f2.sum(fa[z] ? dfn[fa[z]] : dfn[z], dfn[z]);
	}
	*/
	i64 ans = 0;
	int X = x, Y = y, z;
	while (top[x] ^ top[y])
	{
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		ans += f1.sum(dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	ans += f1.sum(dfn[x], dfn[y]);
	z = x;
	if (X == z || Y == z)
	{
//		cout << "SHIT: " ;
//		if (X == Y) cout << "SHIT2: ";
		if (!fa[z]) return flag = 0;
		int jp;
		if (X == z) jp = Y;
		else jp = X;
		z = fa[z];
		return ans - qaq[jp] + qaq[z] + w[z] + qaq[fa[z]];
//		cerr << X << ' '<< Y << ' ' <<  z << ' ' << ans << endl;
	}
	return ans - qaq[X] - qaq[Y] + qaq[fa[z]] + qaq[z];
}

namespace ST
{
	int Max[maxn][20], lg[maxn];
	void init()
	{
		REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
		REP(i, 1, n) Max[i][0] = A[i];
		REP(j, 1, 19)
			REP(i, 1, n - (1 << j) + 1)
			Max[i][j] = max(Max[i][j-1], Max[i + (1 << j-1)][j-1]);
	}
	inline int getmax(int l, int r)
	{
		if (l > r) return -inf;
		int k = lg[r - l + 1];
		return max(Max[l][k], Max[r - (1 << k) + 1][k]);
	}
}

int main()
{
#ifdef CraZYali
	file("set");
#endif
	n = read<int>();q = read<int>();
	REP(i, 1, n) A[i] = read<int>();
	REP(i, 1, n) w[i] = read<int>();
	ST :: init();
	/*
	DEP(i, n, 1)
	{
		if (i == 1) cout << (it -> first) << ' ' << (it -> second) << endl;
		if (it == S.end())
		{
			rt[++k] = i;
			blg[i] = k;
		}
		else
		{
			fa[i] = it -> first;
			add(fa[i], i);
			blg[i] = blg[fa[i]];
		}
		S.emplace(i, A[i]);
	}
	*/
	DEP(i, n, 1)
	{
		int l = i + 1, r = n, res = -1;
		while (l <= r)
		{
//			cerr << l << ' ' << r << endl;
			int mid = l + r >> 1;
			if (ST :: getmax(i + 1, mid) > A[i]) {res = mid;r = mid - 1;}
			else l = mid + 1;
		}
		if (res == -1)
		{
			rt[++k] = i;
			blg[i] = k;
		}
		else
		{
			fa[i] = res;
			add(fa[i], i);
			blg[i] = blg[fa[i]];
		}
	}
//	REP(i, 1, n) printf("%d ", fa[i]);puts("");fflush(stdout);
//	REP(i, 1, n) printf("%d%c", dfn[i], i == n ? '\n' : ' ');
	REP(i, 1, k)
	{
		dfs1(rt[i]);
		dfs2(rt[i], rt[i]);
	}
	/*
	REP(i, 1, n) printf("%d%c", dfn[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", top[i], i == n ? '\n' : ' ');
	REP(i, 1, n) printf("%d%c", fa[i], i == n ? '\n' : ' ');
	REP(x, 1, n)
		for (int i = bg[x]; i; i = ne[i]) printf("%d %d\n", x, to[i]);
		*/
	REP(i, 1, n) f1.add(dfn[i], w[i]);
	while (q--)
	{
		int opt = read<int>(), x = read<int>(), y = read<int>();
		if (opt == 1)
		{
			qaq[x] += y;w[x] += y;
			f1.add(dfn[x], y + y);
//			for (int i = bg[x]; i; i = ne[i]) f1.add(dfn[to[i]], y);
		}
		else
		{
			flag = 1;
			i64 ans = query(x, y);
			if (!flag) puts("?");
			else printf("%lld\n", ans);
		}
	}
	return 0;
}
