#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <stack>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10, maxN = 5e6;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
#define getchar getchar_unlocked
int read()
{
	int ans(0);
	char c(getchar());
	while (!isdigit(c)) c = getchar();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
#define i64 long long
int n, q;

int rt, w[maxn], ww[maxn];
i64 Ans[maxn];

int opt[maxn], l[maxn], r[maxn];
int blg[maxn], block;
i64 sum[maxn];
int dfn[maxn], dfs_clock, id[maxn], fa[maxn];
void dfs0(int x)
{
	dfn[x] = ++dfs_clock;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfs0(to[i]);
	}
}
bool need[maxn];

struct SHIT
{
	int l, r, v, id;
	SHIT(int l = 0, int r = 0, int v = 0, int id = 0) : l(l), r(r), v(v), id(id) {}
};
vector <SHIT> Qry[maxn];
namespace fenwick
{
	int c[maxn];
	void add(int x, int y = 1)
	{
		while (x <= n)
		{
			c[x] += y;
			x += x & -x;
		}
	}
	int sum(int l, int r)
	{
		int y = 0;
		l--;
		while (r > l) y += c[r], r &= (r - 1);
		while (l > r) y -= c[l], l &= (l - 1);
		return y;
	}
}
void dfs(int x)
{
	fenwick :: add(x);
	for (auto i : Qry[x])
		Ans[i.id] += 1ll * fenwick :: sum(i.l, i.r) * i.v;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
		dfs(to[i]);
	fenwick :: add(x, -1);
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	n = read();q = read();
	REP(i, 1, n) w[i] = ww[i] = read();
	REP(i, 1, n)
	{
		int x(read()), y(read());
		if (!x) rt = y;
		else add(x, y), add(y, x);
	}
	dfs0(1);
	REP(i, 1, n) id[i] = i;
	sort(id + 1, id + 1 + n, [](int x, int y) {return dfn[x] < dfn[y];});
	block = max(5., pow(1. * q * n / log2(n + 1), 1. / 3));
	vector <pair <int, int> > tmp;
	REP(i, 1, q)
	{
		blg[i] = (i - 1) / block + 1;
		if (blg[i] ^ blg[i - 1])
		{
			tmp.clear();
			REP(j, 1, n) sum[j] = 0;
			DEP(j, n, 1)
			{
				int k = id[j];
				sum[k] += w[k];
				sum[fa[k]] += sum[k];
			}
			sum[0] = 0;
			REP(j, 2, n) sum[j] += sum[j - 1];
		}
		int opt = read(), l = read(), r = read();
		if (opt == 1)
		{
			r -= w[l];
			w[l] += r;
			tmp.emplace_back(l, r);
		}
		else
		{
			need[i] = 1;
			Ans[i] = sum[r] - sum[l - 1];
			for (auto k : tmp) Qry[k.first].emplace_back(l, r, k.second, i);
		}
	}
	dfs(rt);
	REP(i, 1, q) if (need[i]) printf("%lld\n", Ans[i]);
	return 0;
}
