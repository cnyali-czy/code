#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 500 + 5, MOD = 1e9 + 7;

vector <int> G[maxn];
inline void Add(int x, int y)
{
	G[x].emplace_back(y);
	G[y].emplace_back(x);
}

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int fac[maxn + maxn], inv[maxn + maxn], c[maxn + maxn][maxn + maxn];
struct __init__
{
	__init__(const int n = sizeof(fac) / sizeof(int) - 1)
	{
		fac[0] = 1;
		inv[0] = inv[1] = 1;
		c[0][0] = 1;
		REP(i, 1, n)
		{
			fac[i] = mul(fac[i - 1], i);
			if (i > 1) inv[i] = mul(MOD - MOD / i, inv[MOD % i]);
			REP(j, 0, i) c[i][j] = add(c[i-1][j], j ? c[i-1][j-1] : 0);
		}
	}
}__INIT__;

int n, f[maxn], mem[maxn][maxn], siz[maxn], d[maxn][maxn];

void dfs(int u)
{
	f[u] = 1;
	for (int v : G[u]) if (d[1][u] < d[1][v])
	{
		dfs(v);
		siz[u] += siz[v];
		f[u] = mul(f[u], mul(f[v], c[siz[u]][siz[v]]));
	}
	siz[u]++;
}
int go[maxn][maxn], lca[maxn][maxn], u, v, w[maxn];
int calc(int U,int V)
{
	if (!U) return 0;if (!V) return 1;
	if (mem[U][V]) return mem[U][V];
	int p = mul(siz[V], inv[siz[U] + siz[V]]);
	return mem[U][V] = add(mul(p, calc(U, go[V][v])), mul(MOD + 1 - p, calc(go[U][u], V)));
}
i64 solve(int u,int v)
{
	int l = lca[u][v];
	if (l == u) return 0;
	if (l == v) return 1;
	::u = u; ::v = v;
	REP(i, 1, n) REP(j, 1, n) mem[i][j] = 0;
	return calc(go[l][u], go[l][v]);
}

int main()
{
#ifdef CraZYali
	file("C");
#endif
	n = read<int>();
	REP(i, 1, n) REP(j, 1, n) d[i][j] = 1e8;
	REP(i, 2, n)
	{
		int x(read<int>()), y(read<int>());
		Add(x, y);
		d[x][y] = d[y][x] = 1;
	}
	REP(i, 1, n) d[i][i] = 0;
	REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) chkmin(d[i][j], d[i][k] + d[k][j]);
	REP(i, 1, n) REP(j, 1, n) if (i ^ j) REP(k, 1, n) if (d[i][k] == 1 && d[k][j] + 1 == d[i][j]) go[i][j] = k;
	REP(i, 1, n) REP(j, 1, n)
	{
		int k = i;
		while (k ^ j && d[1][go[k][j]] < d[1][k]) k = go[k][j];
		lca[i][j] = k;
	}
	dfs(1);
	int ans = 0;
	REP(i, 1, n) REP(j, 1, i - 1) inc(ans, solve(i, j));
	cout << mul(ans, f[1]) << '\n';
	return 0;
}
