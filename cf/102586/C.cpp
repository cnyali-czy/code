#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#define i64 long long
#define u64 unsigned i64

using namespace std;
const int maxn = 500 + 5, MOD = 998244353;

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

i64 n, m, K;
int p[maxn], s;

struct Matrix
{
	int a[maxn][maxn];
//	Matrix () {memset(a, 0, sizeof a);}
}bas;
const u64 LIM = 17e18;
Matrix operator * (Matrix A, const Matrix &B)
{
	static u64 res[maxn][maxn];
	REP(i, 0, n) REP(k, 0, n) if (A.a[i][k])
	{
		register u64 qaq = A.a[i][k];
		REP(j, 0, n) if (B.a[k][j])
		{
			res[i][j] += qaq * B.a[k][j];
			if (res[i][j] >= LIM) res[i][j] %= MOD;
		}
	}
	REP(i, 0, n) REP(j, 0, n)
	{
		if (res[i][j] >= MOD) res[i][j] %= MOD;
		A.a[i][j] = res[i][j];res[i][j] = 0;
	}
	return A;
}

namespace Polynomial
{
#define poly vector <int>
	int deg(const poly &f) {return f.size() - 1;}
	poly operator * (poly a, poly b)
	{
		int n(deg(a)), m(deg(b));
		static u64 res[maxn << 1];
		REP(i, 0, n) if (a[i])
		{
			u64 qaq = a[i];
			REP(j, 0, m) if (b[j])
			{
				res[i + j] += qaq * b[j];
				if (res[i + j] >= LIM) res[i + j] %= MOD;
			}
		}
		a.resize(n + m + 1);
		REP(i, 0, n + m)
		{
			if (res[i] >= MOD) res[i] %= MOD;
			a[i] = res[i];res[i] = 0;
		}
		return a;
	}
	poly Mod(poly f, const poly &g)
	{
		int n(deg(f)), m(deg(g));
		if (m > n) return f;
		const i64 Inv = inv(g[m]);
		DEP(i, n, m) if (f[i])
		{
			const i64 qaq = Inv * f[i] % MOD;
			REP(j, 0, m)
				f[j - m + i] = (f[j - m + i] - g[j] * qaq) % MOD;
		}
		f.resize(m);
		REP(i, 0, m - 1) if (f[i] < 0) f[i] += MOD;
		return f;
	}
	poly f, binf[61];
	Matrix bin[maxn];
	void init()
	{
		f.resize(n + 2);
		f[n + 1] = 1;
		f[n + 0] = MOD - p[1] - 1;
		f[n - 1] = p[1];
		if ((n + 1) & 1)
		{
			f[n + 1] = MOD - f[n + 1];
			f[n + 0] = MOD - f[n + 0];
			f[n - 1] = MOD - f[n - 1];
		}
		REP(i, 1, n - 1)
		{
			int val = p[n - i + 1];
			if (n + 1 & 1) val = MOD - val;
			(f[i - 1] += val) %= MOD;
			(f[i] += MOD - val) %= MOD;
		}

		REP(i, 0, n) bin[0].a[i][i] = 1;
		REP(i, 1, n) bin[i] = bas * bin[i - 1];
		binf[0] = poly(2, 0);binf[0][1] = 1;
		REP(i, 1, 60)
			binf[i] = Mod(binf[i - 1] * binf[i - 1], f);
	}
	Matrix pow(i64 b)
	{
		poly res(1, 1);
		REP(i, 0, 60) if (b >> i & 1)
			res = Mod(res * binf[i], f);

		static Matrix ans;
		static u64 DOG[maxn][maxn];
		REP(i, 0, deg(res)) if (res[i])
		{
			u64 qaq = res[i];
			REP(j, 0, n) REP(k, 0, n) if (bin[i].a[j][k])
			{
				DOG[j][k] += qaq * bin[i].a[j][k];
				if (DOG[j][k] >= LIM) DOG[j][k] %= MOD;
			}
		}
		REP(i, 0, n) REP(j, 0, n)
		{
			if (DOG[i][j] >= MOD) DOG[i][j] %= MOD;
			ans.a[i][j] = DOG[i][j];DOG[i][j] = 0;
		}
		return ans;
	}
}
int g[maxn][maxn], f[maxn];

int main()
{
#ifdef CraZYali
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif
	cin >> n >> m >> K;
	REP(i, 1, n)
	{
		scanf("%d", p + i);
		s += p[i];
	}
	const i64 is = inv(s);
	REP(i, 1, n) p[i] = is * p[i] % MOD;

	REP(i, 0, n - 1) bas.a[i + 1][i] = 1;
	REP(i, 0, n - 1) bas.a[i][n - 1] = p[n - i];
	bas.a[n][n] = 1;

	Polynomial :: init();

	Matrix sky = Polynomial :: pow(m - n);
	REP(i, 1, n - 1)
	{
		g[i][i] = MOD - 1;
		g[i][n] = 1;
		REP(j, 1, n) if (i ^ j)
		{
			if (i > j) (g[i][i - j] += p[j]) %= MOD;
			else
			{
				REP(k, 1, n)
					g[i][k] = (g[i][k] + 1ll * sky.a[k][i - j + n] * p[j]) % MOD;
			}
		}
		g[i][n] = MOD - g[i][n];
	}
	//solve
	REP(i, 1, n - 1)
	{
		if (!g[i][i])
		{
			REP(j, i + 1, n - 1) if (g[j][i])
			{
				swap(g[i], g[j]);
				break;
			}
		}
		if (!g[i][i])
		{
			cerr << "???\n";
			continue;
		}
		const i64 Inv = inv(g[i][i]);
		REP(j, i + 1, n - 1) if (g[j][i])
		{
			const i64 qaq = Inv * g[j][i] % MOD;
			REP(k, i, n)
				g[j][k] = (g[j][k] - qaq * g[i][k]) % MOD;
		}
	}
	DEP(i, n - 1, 1)
	{
		i64 RHS = g[i][n];
		REP(j, i + 1, n - 1)
			(RHS -= 1ll * g[i][j] * f[j]) %= MOD;
		f[i] = RHS * inv(g[i][i]) % MOD;
	}
	f[n] = 1;
	REP(i, 1, n - 1) (f[i] += MOD) %= MOD;
	if (K <= n - 1) printf("%d\n", f[K]);
	else
	{
		Matrix dog = Polynomial :: pow(K - (n - 1));
		i64 ans = 0;
		REP(k, 1, n)
			(ans += 1ll * dog.a[k][n - 1] * f[k]) %= MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
