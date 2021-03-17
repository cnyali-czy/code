#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 1e5 + 10, MOD = 998244353;

#define poly vector <int>
const u64 LIM = 17e18;

i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		if (b >>= 1) (base *= base) %= MOD;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

inline int deg(const poly &f) {return (int)f.size() - 1;}
inline void output(const poly &f)
{
	REP(i, 0, deg(f)) printf("%d%c", f[i], i == end_i ? '\n' : ' ' );
}
namespace Poly
{
	const int maxn = 1 << 20;
	u64 NTTtmp[maxn];
	int R[maxn];
	void NTT(poly &a, int n, int flag, bool NEED = 1)
	{
		if (a.size() ^ n) a.resize(n);
		if (flag < 0) reverse(a.begin() + 1, a.end());
		static int *w[30], pool[maxn << 1 | 10];
		static bool vis[30];
		w[0] = pool;
		REP(i, 0, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		REP(i, 0, n - 1) NTTtmp[i] = a[i];
		for (int i = 1, ccc = 0; i < n; i <<= 1, ccc++)
		{
			if (!vis[ccc])
			{
				vis[ccc] = 1;
				const i64 wn = power_pow(3, (MOD - 1) >> ccc + 1);
				if (i < maxn) w[ccc + 1] = w[ccc] + i;
				w[ccc][0] = 1;
				REP(j, 1, i - 1) w[ccc][j] = w[ccc][j - 1] * wn % MOD;
			}
			for (int k = 0; k < n; k += i + i)
				for (int l = 0; l < i; l++)
				{
					u64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % MOD);
					NTTtmp[k + l] = x + y;
					NTTtmp[k + l + i] = MOD + x - y;
				}
		}
		if (!NEED) return;
		REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
		if (flag < 0)
		{
			const int invn = inv(n);
			REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
		}
	}
}
using Poly :: NTT;
inline poly operator * (poly a, poly b)
{
	int l = 1, n = deg(a), m = deg(b);
	while (l <= n + m) l <<= 1;
	NTT(a, l, 1);NTT(b, l, 1);
	REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
	NTT(a, l, -1);
	a.resize(n + m + 1);
	return a;
}
inline poly operator + (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, (int)g.size() - 1) f[i] = (f[i] + g[i]) % MOD;
	return f;
}
inline poly operator - (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, (int)g.size() - 1) f[i] = (f[i] + MOD - g[i]) % MOD;
	return f;
}
poly fix(poly f, int d) {f.resize(d + 1);return f;}
poly Inv(poly f)
{
	int n = deg(f);
	int l = 1;
	while (l <= n) l <<= 1;
	poly a(1, inv(f[0]));
	for (int N = 2; N <= l; N <<= 1)
	{
		const int hf = N / 2;
		poly tf(N, 0), ta = a;
		REP(i, 0, min(n, N - 1)) tf[i] = f[i];

		NTT(ta, N, 1);
		NTT(tf, N, 1);
		REP(i, 0, N - 1) tf[i] = 1ll * ta[i] * tf[i] % MOD;
		NTT(tf, N, -1);
		(tf[0] += MOD - 1) %= MOD;

		poly tta(hf, 0);
		REP(i, hf, N - 1) tta[i - hf] = tf[i];
		NTT(tta, N, 1);
		REP(i, 0, N - 1) tta[i] = 1ll * tta[i] * ta[i] % MOD;
		NTT(tta, N, -1);

		//		tta = tta * a;
		a.resize(N);
		REP(i, hf, min(n, N - 1)) a[i] = (MOD - tta[i - hf]) % MOD;
	}
	a.resize(n + 1);
	return a;
}

int fac[maxn], invs[maxn], Invs[maxn];
void init(int n)
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
}

int n, fa[maxn];
int func[maxn];
vector <int> G[maxn];

inline int read()
{
	char c = getchar();int res = 0;
	while (!isdigit(c)) c = getchar();
	while ( isdigit(c))
	{
		res = res * 10 + (c - 48);
		c = getchar();
	}
	return res;
}

int siz[maxn], dfn[maxn], dfs_clock, back[maxn], hvy[maxn], top[maxn], son[maxn];

void dfs(int x)
{
	siz[x] = 1;
	for (int y : G[x])
	{
		son[x]++;
		dfs(y);
		siz[x] += siz[y];
		if (siz[y] > siz[hvy[x]]) hvy[x] = y;
	}
}
void dfs1(int x, int y)
{
	back[dfn[x] = ++dfs_clock] = x;
	top[x] = y;
	if (!hvy[x]) return;
	dfs1(hvy[x], y);
	for (int z : G[x]) if (z ^ hvy[x]) dfs1(z, z);
}
inline bool is(int x, int y) {return dfn[x] <= dfn[y] && dfn[y] <= dfn[x] + siz[x] - 1;}// x is y's anc

const poly X{0, 1};
poly st[maxn];int m = 0;
#define mid (l + r >> 1)
poly cdq(int l, int r) {return l == r ? st[l] : (cdq(l, l + r >> 1) * cdq(l + r + 2 >> 1, r));}
poly dp2(int x)
{
	if (!G[x].size()) return X;

	poly fk = dp2(hvy[x]);

	vector <poly> t;
	for (int y : G[x]) if (y ^ hvy[x]) /*fk = fk * dp2(y)*/t.emplace_back(dp2(y));
	
	if (t.size())
	{
		m = 0;
		for (auto i : t) st[++m] = i;
		fk = fk * cdq(1, m);
	}
	return fk + X;
}
poly g[maxn], f[maxn];int a[maxn];

int to[2][2];

vector <poly> fuck(int l, int r)
{
	if (l == r)
	{
		return {g[a[l]], poly(1, 1), poly(1, 0), poly(1, 1)};
//		return g[a[l]] + X;
	}
	auto R = fuck(mid + 1, r), L = fuck(l, mid);
	vector <poly> res{poly(1, 0), poly(1, 0), poly(1, 0), poly(1, 0)};
	REP(i, 0, 1) REP(j, 0, 1) REP(k, 0, 1)
		res[to[i][k]] = res[to[i][k]] + R[to[i][j]] * L[to[j][k]];
	return res;
	
//	return fuck(l, mid) * fuck(mid + 1, r);	
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	to[0][0] = 0;to[1][0] = 1;to[0][1] = 2;to[1][1] = 3;
	cin >> n;
	init(n);
	REP(i, 2, n) G[fa[i] = read()].emplace_back(i);
	REP(i, 1, n) func[i] = read();
	dfs(1);dfs1(1, 1);

//	poly res = fix(dp2(1), n);
/*
	REP(i, 1, n) printf("%d%c", hvy[i], i == end_i ? '\n' : ' ' );
	REP(i, 1, n) printf("%d%c", top[i], i == end_i ? '\n' : ' ' );
	REP(i, 1, n) printf("%d%c", dfn[i], i == end_i ? '\n' : ' ' );
*/
	REP(i, 1, n) if (hvy[i]) g[i] = poly(1, 1);else g[i] = poly(1, 0);
	DEP(I, n, 1)
	{
		int x = back[I];
		if (x == top[x])
		{
			int m = 0;
			for (int y = x; y; y = hvy[y])
			{
				a[++m] = y;
				int k = 0;
				for (int z : G[y]) if (z ^ hvy[y]) st[++k] = f[z];
				if (k) g[y] = cdq(1, k);
			}
		
			poly res = fuck(1, m)[1] * X;
//			poly res(1, 0);
//			DEP(i, m, 1) res = res * g[a[i]] + X;
//			output(res);
//			output(fuck(1, m)[1] * X);
//			puts("");

			f[x] = res;

//			if (fa[x]) g[fa[x]] = g[fa[x]] * f[x];
		}
	}
	poly res = fix(f[1], n);
//	output(res);

	i64 ans = 0;
	REP(i, 1, n) (ans += 1ll * func[i] * res[i] % MOD * fac[i]) %= MOD;
	cout << ans << endl;
	return 0;
}
