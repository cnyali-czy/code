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

int bg[maxn], ne[maxn], to[maxn], e;
//vector <int> G[maxn];
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

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

int siz[maxn], dfn[maxn], dfs_clock, back[maxn], hvy[maxn], top[maxn];
void dfs(int x)
{
	siz[x] = 1;
	for (int i = bg[x], y = to[i]; i; y = to[i = ne[i]])
	{
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
	for (int i = bg[x], z = to[i]; i; z = to[i = ne[i]])
		if (z ^ hvy[x]) dfs1(z, z);
}

const poly X{0, 1};
int st[maxn], m;
poly g[maxn], f[maxn];
poly cdq1(int l, int r)
{
	if (l == r) return f[st[l]];
	int tot = 0;REP(i, l, r) tot += f[st[i]].size();
	int cur = 0, mid = r - 1;
	REP(i, l, r - 1)
	{
		cur += f[st[i]].size();
		if (cur >= tot - cur) {mid = i;break;}
	}
	return cdq1(l, mid) * cdq1(mid + 1, r);
	return l == r ? f[st[l]] : (cdq1(l, mid) * cdq1(mid + 1, r));
}

int a[maxn];
#define fi first
#define se second
pair <poly, poly> cdq2(int l, int r)
// mul, sum mul
{
	if (l == r) return make_pair(g[a[l]], g[a[l]]);

	int mid = l + r >> 1;
	auto L = cdq2(l, mid), R = cdq2(mid + 1, r);
	int len = 1, N = deg(L.fi) + deg(R.fi);
	while (len <= N) len <<= 1;

	poly t1 = L.se;L.se.resize(len);
	NTT(L.fi, len, 1);NTT(R.fi, len, 1);NTT(R.se, len, 1);
	REP(i, 0, len - 1) L.se[i] = 1ll * L.fi[i] * R.se[i] % MOD;
	NTT(L.se, len, -1);L.se = fix(L.se, N) + t1;
	REP(i, 0, len - 1) L.fi[i] = 1ll * L.fi[i] * R.fi[i] % MOD;
	NTT(L.fi, len, -1);L.fi.resize(N + 1);
	/*
	L.se = L.fi * R.se + L.se;
	L.fi = L.fi * R.fi;
	*/
	return L;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
#endif
	cin >> n;
	init(n);
	REP(i, 2, n) add(fa[i] = read(), i);
	REP(i, 1, n) func[i] = read();
	dfs(1);dfs1(1, 1);

	REP(i, 1, n) if (hvy[i]) g[i] = poly(1, 1);else g[i] = poly(1, 0);
	g[0] = X;
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
				for (int i = bg[y], z = to[i]; i; z = to[i = ne[i]]) if (z ^ hvy[y]) st[++k] = z;
				if (k) g[y] = cdq1(1, k);
			}
			f[x] = cdq2(0, m).se;
		}
	}
	poly res = fix(f[1], n);

	i64 ans = 0;
	REP(i, 1, n) (ans += 1ll * func[i] * res[i] % MOD * fac[i]) %= MOD;
	cout << ans << endl;
	return 0;
}
