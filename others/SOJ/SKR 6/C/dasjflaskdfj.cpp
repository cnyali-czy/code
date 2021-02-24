/*
	Problem:	C.cpp
	Time:		2021-02-23 13:30
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long

using namespace std;
const int maxn = 500 + 10, maxl = 2.5e5 + 10, MOD = 998244353;

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
		ans = ans * 10 + (c - 48);
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

#define poly vector <int> 
#define ui64 unsigned i64

namespace Poly
{
	const int maxn = 1 << 19;
	ui64 NTTtmp[maxn];
	int R[maxn];
	void NTT(poly &a, int n, int flag)
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
}
using Poly :: NTT;
inline int deg(const poly &a) {return (int)a.size() - 1;}
void output(poly a, const char Split = ' ', const char End = '\n')
{
	REP(i, 0, (int)a.size() - 1) printf("%d%c", a[i], i == end_i ? End : Split);
}
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
int fac[maxl], invs[maxl], Inv[maxl];
void init(int n)
{
	fac[0] = invs[0] = Inv[0] = 1;
	fac[1] = invs[1] = Inv[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Inv[i] = 1ll * invs[i] * Inv[i - 1] % MOD;
	}
}
inline i64 C(int n, int m) {return 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}
inline poly operator + (poly f, poly g)
{
	if (f.size() < g.size()) f.resize(g.size());
	REP(i, 0, (int)g.size() - 1) (f[i] += g[i]) %= MOD;
	return f;
}

int n, L;

struct Matrix
{
	int a[maxn][maxn];
	Matrix() {memset(a, 0, sizeof a);}
};
inline Matrix operator * (const Matrix &A, const Matrix &B)
{
	static Matrix res;
	REP(i, 1, n) REP(j, 1, n) res.a[i][j] = 0;
	REP(i, 1, n) REP(k, 1, n) if (A.a[i][k]) REP(j, 1, n) if (B.a[k][j]) res.a[i][j] = (res.a[i][j] + 1ll * A.a[i][k] * B.a[k][j]) % MOD;
	return res;
}

i64 det(const Matrix &B)
{
	static int a[maxn][maxn];
	REP(i, 1, n) REP(j, 1, n) a[i][j] = B.a[i][j];
	i64 res = 1;
	REP(i, 1, n)
	{
		if (!a[i][i])
		{
			REP(j, i + 1, n) if (a[j][i])
			{
				res = MOD - res;
				REP(k, i, n) swap(a[i][k], a[j][k]);
				break;
			}
		}
		if (!a[i][i]) return 0;
		(res *= a[i][i]) %= MOD;
		const i64 Inv = inv(a[i][i]);
		REP(j, i + 1, n) if (a[j][i])
		{
			const i64 qaq = a[j][i] * Inv % MOD;
			REP(k, i, n) a[j][k] = (a[j][k] - a[i][k] * qaq) % MOD;
		}
	}
	return (res + MOD) % MOD;
}

poly cdq(int l, int r)
{
	if (l == r)
	{
		poly res(2, 0);
		if (l) res[0] = MOD - l;
		res[1] = 1;
		return res;
	}
	int mid = l + r >> 1;
	return cdq(l, mid) * cdq(mid + 1, r);
}
poly Mod(poly f, const poly &g) // return f % g
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
poly Div(poly f, const poly &g) // return f / g
{
	int n(deg(f)), m(deg(g));
	const i64 Inv = inv(g[m]);
	poly res(n - m + 1, 0);
	DEP(i, n, m) if (f[i])
	{
		const i64 qaq = Inv * f[i] % MOD;
		res[i - m] = qaq;
		REP(j, 0, m)
			f[j - m + i] = (f[j - m + i] - g[j] * qaq) % MOD;
	}
	return res;
}

struct Graph
{
	int n, m;Matrix A;
	void init()
	{
		n = read<int>();m = read<int>();
		REP(i, 1, m)
		{
			int x = read<int>(), y = read<int>();
			A.a[x][y]++;A.a[y][x]++;
		}
	}

	int pre[maxn];
	poly solve()
	{
		::n = n;
		double S = clock();
		poly P = cdq(0, n);
		poly f(1, 0);
		REP(i, 0, n)
		{
			poly h(2, 0);if (i) h[0] = MOD - i;h[1] = 1;
			poly rP = Div(P, h);

			Matrix T = A;
			if (i) REP(j, 1, n) (T.a[j][j] += MOD - i) %= MOD;
			i64 xs = det(T);
			REP(j, 0, n) if (i ^ j)
				if (i < j) (xs *= (MOD - invs[j - i])) %= MOD;
				else (xs *= invs[i - j]) %= MOD;
			REP(j, 0, n) rP[j] = rP[j] * xs % MOD;
			f = f + rP;
			if (i % 10 == 0) fprintf(stderr, "Done det %d / %d = %.2lf%%\n", i, n, i * 100. / n);
		}

		poly ans(L + 1, 0);
		Matrix b;
		REP(i, 1, n) b.a[i][i] = 1;
		REP(i, 0, n)
		{
			i64 res = 0;
			REP(j, 1, n) res += b.a[j][j];
			pre[i] = res % MOD;
			if (i < n) b = b * A;
		}
		poly c(1, 1);
		REP(i, 0, L)
		{
			i64 res = 0;
			REP(j, 0, min(deg(c), n)) (res += 1ll * c[j] * pre[j]) %= MOD;
			ans[i] = res % MOD * Inv[i] % MOD;
			c.emplace_back(0);
			DEP(i, deg(c), 1) c[i] = c[i - 1];c[0] = 0;c = Mod(c, f);
			if (i % 10 == 0) fprintf(stderr, "Done %d / %d = %.2lf%%\n", i, L, i * 100. / L);
		}
		return ans;
	}
}g1, g2;

int main()
{
#ifdef CraZYali
	file("C");
#endif
	L = read<int>() ;
	init(L);
	g1.init();poly f1 = g1.solve();
	g2.init();poly f2 = g2.solve();
	poly ans = f1 * f2;
	REP(i, 0, L) printf("%lld\n", 1ll * fac[i] * ans[i] % MOD);
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
