#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxk = 1e4 + 10;

int k, p;i64 m;

i64 power_pow(i64 base, int b, const int MOD = p)
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
#define inv(x) power_pow(x, p - 2)
#define poly vector <int>
inline int deg(const poly &f) {return (int)f.size() - 1;}

poly Mod(poly f, const poly &g) // return f % g
{
	static const int MOD = p;
	int n(deg(f)), m(deg(g));
	if (m > n) return f;
	static int s[maxk << 1];
	REP(i, 0, n + 1) s[i] = 0;
	DEP(i, n, 0)
	{
		int L = max(m, i + 1), R = min(n, i + m);
		if (L <= R) (f[i] += s[L] - s[R + 1]) %= MOD;;
		if (i >= m) s[i] = s[i + 1] + f[i];
	}
	f.resize(m);
	REP(i, 0, m - 1) if (f[i] < 0) f[i] += MOD;
	return f;
}
#define u64 unsigned i64
namespace Poly
{
	const int maxn = 1 << 18, MOD = 998244353;
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
				const i64 wn = power_pow(3, (MOD - 1) >> ccc + 1, MOD);
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
			const int invn = power_pow(n, 998244353 - 2, 998244353);
			REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
		}
	}
}
using Poly :: NTT;
poly operator * (poly a, poly b)
{
	const static int MOD = p;
	int n = deg(a), m = deg(b);
	int len = 1;
	while (len <= n + m) len <<= 1;
	NTT(a, len, 1);
	NTT(b, len, 1);
	REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % 998244353;
	NTT(a, len, -1);
	a.resize(n + m + 1);
	REP(i, 0, n + m) a[i] = a[i] % MOD;
	return a;
}

int fac[333], invs[333], Invs[333];
void init()
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	const int MOD = p;
	REP(i, 2, p - 1)
	{
		fac[i] = i * fac[i - 1] % MOD;
		invs[i] = (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = invs[i] * Invs[i - 1] % MOD;
	}
}
inline int C(int n, int m)
{
	const static int MOD = p;
	if (n < m || m < 0) return 0;
	if (n < p && m < p) return fac[n] * Invs[m] * Invs[n - m] % MOD;
	return C(n % MOD, m % MOD) * C(n / MOD, m / MOD) % MOD;
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> k >> m >> p;
	int mm = m;
	init();
	if (k == 1)
	{
		cout << 1 << endl;
		return 0;
	}
	const int MOD = p;
	int ans = 0;

	poly tz(k + 1, 0);
	REP(i, 0, k - 1) tz[i] = p - 1;
	tz[k] = 1;

	poly Ans(2, 0), base(2, 0);Ans[1] = base[1] = 1;m--;
	while (m)
	{
		int len = 1;
		while (len <= (k - 1) + (k - 1)) len <<= 1;
		NTT(base, len, 1);
		if (m & 1)
		{
			NTT(Ans, len, 1);
			REP(i, 0, len - 1) Ans[i] = 1ll * Ans[i] * base[i] % 998244353;
			NTT(Ans, len, -1);for (auto &i : Ans) if (i >= MOD) i %= MOD;
			Ans.resize(k * 2 - 1);
			Ans = Mod(Ans, tz);
		}
		if (m >>= 1)
		{
			REP(i, 0, len - 1) base[i] = 1ll * base[i] * base[i] % 998244353;
			NTT(base, len, -1);for (auto &i : base) if (i >= MOD) i %= MOD;
			base.resize(k * 2 - 1);
			base = Mod(base, tz);
		}
	}
	Ans.resize(k);

	i64 res = 1;
	REP(i, 0, k - 1)
	{
		res -= (i == end_i);
		(ans += res * Ans[i] % MOD) %= MOD;
		(res <<= 1) %= MOD;
	}

	m = mm;
	static int g[300];
	g[0] = 1;REP(i, 1, m + 3)
	{
		int res = 0;
		REP(j, max(0, i - k), i - 1) res += g[j];
		g[i] = res % MOD;
	}
	REP(i, 0, 3 + m) printf("%d%c", g[i], i == end_i ?'\n' : ' ' );

	cout << (ans + MOD) % MOD << endl;
	return 0;
}
