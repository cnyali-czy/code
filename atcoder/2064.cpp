#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64
#define poly vector <int>

using namespace std;
const int maxn = 2e5 + 10, MOD = 924844033;

int bg[maxn], ne[maxn << 1], to[maxn << 1], e;
inline void add(int x, int y)
{
	e++;
	to[e] = y;
	ne[e] = bg[x];
	bg[x] = e;
}

int n;

int fac[maxn], invs[maxn], Invs[maxn];
inline void init(int n)
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
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}

int siz[maxn], fa[maxn];
void dfs(int x)
{
	siz[x] = 1;
	for (int i = bg[x]; i; i = ne[i]) if (to[i] ^ fa[x])
	{
		fa[to[i]] = x;
		dfs(to[i]);
		siz[x] += siz[to[i]];
	}
}
int ans[maxn];

const u64 LIM = 17e18;
inline int deg(const poly &f) {return (int)f.size() - 1;}
poly operator * (poly a, poly b)
{
	int n = deg(a), m = deg(b);
	static u64 c[maxn];
	REP(i, 0, n) if (a[i]) REP(j, 0, m) if (b[j])
	{
		c[i + j] += (u64) a[i] * b[j];
		if (c[i + j] >= LIM) c[i + j] %= MOD;
	}
	a.resize(n + m + 1);
	REP(i, 0, n + m)
	{
		a[i] = c[i] % MOD;
		c[i] = 0;
	}
	return a;
}

int main()
{
#ifdef CraZYali
	freopen("2064.in", "r", stdin);
	freopen("2064.out", "w", stdout);
#endif
	cin >> n;init(n);
	REP(i, 1, n - 1)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);add(y, x);
	}
	dfs(1);
	REP(j, 1, n) ans[j] = n * C(n, j) % MOD;
	poly F(1, 0);
	REP(x, 1, n) for (int i = bg[x]; i; i = ne[i])
	{
		int rs = to[i] == fa[x] ? n - siz[x] : siz[to[i]];
		REP(j, 1, rs) (ans[j] += MOD - C(rs, j)) %= MOD;
	}
	REP(i, 1, n) printf("%d\n", ans[i]);
	return 0;
}
