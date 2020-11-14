#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;
const int MOD = 998244353, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
#define poly vector <int> 
#define i64 long long
#define ui64 unsigned i64
const ui64 LIM = 17e18;

int n, k;
i64 power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)

void NTT(poly &a, int n, int flag)
{
	static const int maxn = 1 << 21;
	static ui64 NTTtmp[maxn];
	static int R[maxn];
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
				ui64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % MOD);
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i] = MOD + x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
	if (flag < 0)
	{
		const int invn = inv(n);
		REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
	}
}
inline int deg(const poly &a) {return a.size() - 1;}
poly sqr(poly f)
{
	int len = 1, n = deg(f);
	while (len <= n + n) len <<= 1;
	NTT(f, len, 1);
	REP(i, 0, len - 1) f[i] = 1ll * f[i] * f[i] % MOD;
	NTT(f, len, -1);
	f.resize(k + 1);
	return f;
}
void output(poly a)
{
	REP(i, 0, (int)a.size() - 1) printf("%d%c", a[i], i == end_i ? '\n' : ' ');
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

inline poly operator + (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, (int)g.size() - 1) (f[i] += g[i]) %= MOD;
	return f;
}
inline poly operator - (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, (int)g.size() - 1) f[i] = (f[i] + MOD - g[i]) % MOD;
	return f;
}

const int maxn = 1e6 + 10;
int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}
int fac[maxn], Inv[maxn], str[105][105];
void init()
{
	int N = max(n, k);
	fac[0] = 1;
	REP(i, 1, N) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[N] = inv(fac[N]);
	DEP(i, N - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
	str[0][0] = 1;
	REP(i, 1, k) REP(j, 1, i) str[i][j] = (str[i - 1][j - 1] + 1ll * j * str[i - 1][j]) % MOD;
}
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[n - m] % MOD * Inv[m] % MOD;}

bool vis[maxn];
int allnode, siz[maxn], Max[maxn], rt;
void findrt(int x, int fa = 0)
{
	siz[x] = 1;Max[x] = 0;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
	{
		findrt(to[i], x);
		siz[x] += siz[to[i]];
		Max[x] = max(Max[x], siz[to[i]]);
	}
	Max[x] = max(Max[x], allnode - siz[x]);
	if (Max[x] < Max[rt] || !rt) rt = x;
}
ui64 mem[105];
int md, Md, cnt[maxn];
i64 ans;
void dfs2(int x, int d, int fa = 0)
{
	md = max(md, min(k, d));
	Md = max(Md, d);
	cnt[d]++;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
		dfs2(to[i], d + 1, x);
}
int X[maxn];
void calc(int x, int d, int flag)
{
	REP(i, 0, md) mem[i] = 0;
	md = Md = 0;
	dfs2(x, d);
	REP(i, d, Md)
	{
		int v = cnt[i];cnt[i] = 0;
		REP(j, 0, min(i, md)) mem[j] += C(i, j) * v;
	}
	REP(i, 0, md) if (mem[i] >= MOD) mem[i] %= MOD;
	ui64 res = 0;
	if (md > 10)
	{
		poly g(md + 1, 0);
		REP(i, 0, md) g[i] = mem[i];
		g = sqr(g);
		REP(i, 1, k)
		{
			res += 1ll * X[i] * g[i];
			if (res >= LIM) res %= MOD;
		}
	}
	else
	{
		REP(i, 1, k)
		{
			ui64 r = 0;
			REP(j, 0, min(md, i)) if (mem[i - j]) r += mem[j] * mem[i - j];
			if (r >= MOD) r %= MOD;
			res += X[i] * r;
		}
	}
	if (res >= MOD) res %= MOD;
	if (flag > 0) ans += res;
	else ans -= res;
}
void dfs(int x)
{
#ifdef CraZYali
	static int dfn = 0;
	++dfn;
	if (dfn % 20000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", dfn, n, dfn * 100. / n);
#endif
	vis[x] = 1;
	calc(x, 0, 1);
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]])
	{
		calc(to[i], 1, -1);
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
	n = read<int>();k = read<int>();
	init();
	REP(i, 2, n)
	{
		int x = read<int>(), y = read<int>();
		add(x, y);add(y, x);
	}
	REP(i, 0, k) X[i] = 1ll * str[k][i] * fac[i] % MOD;
	allnode = n;
	findrt(n);
	dfs(rt);
	cout << (ans % MOD * inv2 % MOD + MOD) % MOD << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
