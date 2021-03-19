#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)

#include <vector>
#include <cmath>
#include <iostream>
#include <cstdio>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 300 + 5, MOD = 1e9 + 7;

inline bool judge(i64 x, i64 y)
{
	i64 z = sqrt(1ll * x * y);
	return z * z == x * y;
}
int n, a[maxn];

int fa[maxn], siz[maxn];
int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
void uni(int x, int y) {fa[find(x)] = find(y);}

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
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}

#define poly vector <int>
inline int deg(const poly &f) {return (int)f.size() - 1;}
const u64 LIM = 17e18;
poly operator * (poly a, poly b)
{
	static u64 res[maxn];
	int n = deg(a), m = deg(b);
	REP(i, 0, n) if (a[i]) REP(j, 0, m) if (b[j])
	{
		res[i + j] += (u64)a[i] * b[j];
		if (res[i + j] >= LIM) res[i + j] %= MOD;
	}
	a.resize(n + m + 1);
	REP(i, 0, n + m)
	{
		a[i] = res[i] % MOD;
		res[i] = 0;
	}
	return a;
}

int main()
{
#ifdef CraZYali
	freopen("4448-new.in", "r", stdin);
	freopen("4448-new.out", "w", stdout);
#endif
	cin >> n;init(n);
	REP(i, 1, n) scanf("%d", a + i);
	REP(i, 1, n) fa[i] = i;
	REP(i, 1, n) REP(j, i + 1, n) if (judge(a[i], a[j])) uni(i, j);
	REP(i, 1, n) siz[find(i)]++;

	i64 xs = 1;
	poly g(1, 1);
	REP(i, 1, n) if (fa[i] == i)
	{
		int m = siz[i];
		(xs *= fac[m]) %= MOD;
		poly t(m + 1, 0);
		REP(j, 1, m) t[j] = C(m - 1, j - 1) * Invs[j] % MOD;
		g = g * t;
	}
	REP(i, 0, n) g[i] = 1ll * g[i] * fac[i] % MOD * fac[n - i] % MOD;
	
	i64 ans = 0;
	REP(i, 0, n)
	{
		i64 cur = 1ll * g[i] * Invs[n - i] % MOD;
		if (n - i & 1) cur = MOD - cur;
		ans += cur;
	}
	cout << ans % MOD * xs % MOD << endl;

	return 0;
}
