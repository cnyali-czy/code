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

#pragma optimize("Ofast")
#pragma optimize("avx")
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;
const int MOD = 998244353, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
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

void NTT(int a[], int n, int flag)
{
	static const int maxn = 256;
	static int R[maxn];
	static unsigned i64 NTTtmp[maxn];
	if (flag < 0) reverse(a + 1, a + n);
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
				unsigned i64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % MOD);
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
inline char nc()
{
    static char buf[200000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,200000,stdin),p1==p2)?EOF:*p1++;
}
	template <typename T>
inline T read()
{
	T ans = 0;
	char c = nc();
	while (!isdigit(c)) c = nc();
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = nc();
	}
	return ans;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

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
	Md = max(Md, d);
//	REP(i, 0, min(k, d)) mem[i] += C(d, i);
	cnt[d]++;
	for (int i = bg[x]; i; i = ne[i]) if (!vis[to[i]] && to[i] ^ fa)
		dfs2(to[i], d + 1, x);
}
int X[maxn];
int L;
inline int min(int x, int y) {return x < y ? x : y;}

ui64 real[105], G[2][256];
void calc(int rx)
{
	static int rMd, g[256];
	static ui64 rm[256];
	rMd = 0;
	for (int E = bg[rx]; E; E = ne[E]) if (!vis[to[E]])
	{
		int x = to[E];
		REP(i, 0, md) mem[i] = 0;
		Md = 0;
		dfs2(x, 1, rx);
		md = min(Md, k);
		rMd = max(rMd, Md);
		REP(i, 1, Md)
		{
			int v = cnt[i];cnt[i] = 0;
			register i64 f = 1ll * fac[i] * v % MOD;
			REP(j, 0, min(i, md))
			{
				mem[j] += f * Inv[i - j];
				if (mem[j] >= LIM) mem[j] %= MOD;
			}
		}
		REP(i, 0, md)
		{
			if (mem[i] >= MOD) mem[i] %= MOD;
			(mem[i] *= Inv[i]) %= MOD;
			rm[i] += mem[i];
		}
		if (md > 15)
		{
			REP(i, 0, md) g[i] = mem[i];
			NTT(g, L, 1);REP(i, 0, L - 1)
			{
				G[1][i] += 1ll * g[i] * g[i];
				if (G[1][i] >= LIM) G[1][i] %= MOD;
				g[i] = 0;
			}
		}
		else
		{
			REP(i, 1, k)
			{
				ui64 r = 0;
				REP(j, 0, min(md, i)) if (mem[i - j]) r += mem[j] * mem[i - j];
				if (r >= MOD) r %= MOD;
				real[i] += MOD - r;
			}
		}
	}

	rm[0]++;
	REP(i, 0, md) mem[i] = 0;
	Md = rMd, md = min(Md, k);
	REP(i, 0, md)
	{
		if (rm[i] >= MOD) rm[i] %= MOD;
		mem[i] = rm[i];rm[i] = 0;
	}
	if (md > 15)
	{
		REP(i, 0, md) g[i] = mem[i];
		NTT(g, L, 1);REP(i, 0, L - 1)
		{
			G[0][i] += 1ll * g[i] * g[i];
			if (G[0][i] >= LIM) G[0][i] %= MOD;
			g[i] = 0;
		}
	}
	else
	{
		REP(i, 1, k)
		{
			ui64 r = 0;
			REP(j, 0, min(md, i)) if (mem[i - j]) r += mem[j] * mem[i - j];
			if (r >= MOD) r %= MOD;
			real[i] += r;
		}
	}
}
void dfs(int x)
{
#ifdef CraZYali
	static int dfn = 0;
	++dfn;
	if (dfn % 20000 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", dfn, n, dfn * 100. / n);
#endif
	vis[x] = 1;
	calc(x);
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
	n = read<int>();k = read<int>();
	L = 1;while (L <= k + k) L <<= 1;
	init();
	static int id[maxn], NNN;
	REP(i, 1, n - 1)
	{
		int x = read<int>(), y = read<int>();
		if (!id[x]) id[x] = ++NNN;x = id[x];
		if (!id[y]) id[y] = ++NNN;y = id[y];
		add(x, y);add(y, x);
	}
	REP(i, 0, k) X[i] = 1ll * str[k][i] * fac[i] % MOD;
	allnode = n;
	findrt(n);
	dfs(rt);
	static int tG[2][256];
	REP(i, 0, L - 1)
	{
		tG[0][i] = G[0][i] % MOD;
		tG[1][i] = G[1][i] % MOD;
	}
	NTT(tG[0], L, -1);NTT(tG[1], L, -1);
	REP(i, 1, k)
	{
		real[i] += tG[0][i] + MOD - tG[1][i];
		ans = (ans + real[i] % MOD * X[i]) % MOD;
	}
	cout << (ans % MOD * inv2 % MOD + MOD) % MOD << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
