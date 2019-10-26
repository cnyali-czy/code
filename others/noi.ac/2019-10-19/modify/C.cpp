#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5e5 + 10;

template <typename T>
inline T read()
{
	register T ans(0), flag(1);
	register char c = getchar();
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

int n, m, w[maxn];
struct fenwick
{
	int qaq[maxn];
	inline void add(int x, int v)
	{
		while (x <= 500000)
		{
			qaq[x] += v;
			x += x & -x;
		}
	}
	inline int sum(int x)
	{
		int res(0);
		while (x > 0)
		{
			res += qaq[x];
			x -= x & -x;
		}
		return res;
	}
}fenw;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

vector <int> G[maxn];
inline void add(int x, int y)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}
int fa[maxn], d[maxn], l[maxn], r[maxn], z[maxn], dfs_clock;

void dfs(int u)
{
	l[u] = ++dfs_clock;
	z[u] = d[u] - fenw.sum(w[u]);
	fenw.add(w[u], 1);
	for (int v : G[u]) if (v ^ fa[u])
	{
		fa[v] = u;
		d[v] = d[u] + 1;
		dfs(v);
	}
	fenw.add(w[u], -1);
	r[u] = dfs_clock;
}
int y[maxn], ord[maxn];
long long ans[maxn];

int main()
{
#ifdef CraZYali
	file("C");
#endif
	cin >> n >> m;
	REP(i, 1, n) w[i] = read<int>();
	REP(i, 2, n) add(read<int>(), read<int>());
	dfs(1);
	iota(ord + 1, ord + 1 + n, 1);
	sort(ord + 1, ord + 1 + n, [&](int x, int y) {return w[x] > w[y];});
	for (register int i(1), j(1); i <= n; i = j)
	{
		while (j <= n && w[ord[i]] == w[ord[j]]) j++;
		REP(k, i, j - 1)
			y[ord[k]] = fenw.sum(r[ord[k]]) - fenw.sum(l[ord[k]] - 1);
		REP(k, i, j - 1)
			fenw.add(l[ord[k]], 1);
	}
	REP(i, 1, n) z[i] -= y[i];
	sort(z + 1, z + 1 + n);
	REP(i, 1, n) ans[0] += y[i];
	REP(i, 0, n - 1) ans[i + 1] = ans[i] + z[i + 1] + i;
	while (m--) printf("%lld\n", ans[read<int>()]);
	return 0;
}
