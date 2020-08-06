/*
	Problem:	500.cpp
	Time:		2020-08-02 22:03
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <random>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;
const int MOD = 998244353, inv3 = (MOD + 1) / 3, inv2 = MOD + 1 >> 1;
#define poly vector <int> 
#define i64 long long
#define ui64 unsigned i64

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

const int maxn = 1 << 21;
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
	bool fff = (flag > 0);
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

poly Inv(poly f)
{
	int n = deg(f);
	int l = 1;
	while (l <= n) l <<= 1;
	poly a(1, inv(f[0]));
	for (int N = 2; N <= l; N <<= 1)
	{
		poly tmp(f.begin(), f.begin() + min(N, n + 1));
		NTT(a, N + N, 1);
		NTT(tmp, N + N, 1);
		REP(i, 0, N + N - 1) a[i] = 1ll * a[i] * (2 + MOD - 1ll * a[i] * tmp[i] % MOD) % MOD;
		NTT(a, N + N, -1);
		a.resize(N);
	}
	a.resize(n + 1);
	return a;
}
poly Der(poly f)
{
	int n = deg(f);
	REP(i, 0, n - 1)
		f[i] = (i + 1ll) * f[i + 1] % MOD;
	f.resize(n);
	return f;
}
int invs[maxn], last;
void prepare(int n)
{
	if (!last)
	{
		invs[0] = invs[1] = 1;
		last = 1;
	}
	if (last < n)
	{
		REP(i, last + 1, n) invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		last = n;
	}
}
poly Int(poly f)
{
	int n = deg(f);
	prepare(n + 1);
	f.push_back(0);
	DEP(i, n + 1, 1)
		f[i] = 1ll * invs[i] * f[i - 1] % MOD;
	f[0] = 0;
	return f;
}
poly Ln(poly f)
{
	int n = deg(f);
	poly res = Int(Der(f) * Inv(f));
	res.resize(n + 1);
	return res;
}
poly Exp(poly f)
{
	int n = deg(f);
	int l = 1;
	while (l <= n) l <<= 1;
	poly a(1, 1);
	for (int N = 2; N <= l; N <<= 1)
	{
		poly tmp(f.begin(), f.begin() + min(N, n + 1));
		a.resize(N);
		poly ln = Ln(a);
		NTT(a, N + N, 1);
		NTT(ln, N + N, 1);
		NTT(tmp, N + N, 1);
		REP(i, 0, N + N - 1) a[i] = a[i] * (1ll + MOD - ln[i] + tmp[i]) % MOD;
		NTT(a, N + N, -1);
	}
	a.resize(n + 1);
	return a;
}
namespace Less
{
	int II;
	struct num
	{
		int x, y;
		inline num(int x = 0, int y = 0) : x(x), y(y) {}
		inline num operator * (num B) {return num((1ll * x * B.x + 1ll * II * y % MOD * B.y) % MOD, (1ll * x * B.y + 1ll * y * B.x) % MOD);}
		inline num operator *=(num B) {return *this = *this * B;}
	};

	num power_pow(num base, int b)
	{
		num ans(1);
		while (b)
		{
			if (b & 1) ans *= base;
			base *= base;
			b >>= 1;
		}
		return ans;
	}
	int solve(int n)
	{
		int a = MOD - 1;
		while (1)
		{
			II = (1ll * a * a + MOD - n) % MOD;
			if (a && ::power_pow(II, MOD - 1 >> 1) == MOD - 1) break;
			a = rand() % MOD;
		}
		int ans1 = power_pow(num(a, 1), MOD + 1 >> 1).x, ans2 = (MOD - ans1) % MOD;
		return min(ans1, ans2);
	}
}
poly Sqrt(poly f)
{
	int n = deg(f);
	int l = 1;
	while (l <= n) l <<= 1;
	poly a(1, Less :: solve(f[0]));
	for (int N = 2; N <= l; N <<= 1)
	{
		poly tmp(f.begin(), f.begin() + min(N, n + 1));
		a.resize(N);
		tmp = tmp * Inv(a);
		REP(i, 0, N - 1) a[i] = 1ll * (a[i] + tmp[i]) * inv2 % MOD;
	}
	a.resize(n + 1);
	return a;
}
inline poly operator ^ (poly f, int x)
{
	f = Ln(f);
	REP(i, 0, (int)f.size() - 1) f[i] = 1ll * f[i] * x % MOD;
	return Exp(f);
}
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
inline poly operator + (poly f, int x) {(f[0] += x) %= MOD;return f;}
inline poly operator + (int x, poly f) {(f[0] += x) %= MOD;return f;}
inline poly operator - (poly f, int x) {f[0] = (f[0] + MOD - x) % MOD;return f;}

poly f, a;
void cdq(int l, int r)
{
	if (r - l + 1 <= 128)
	{
		REP(i, l, r)
		{
			if (!i) a[i] = 1;
			else a[i] = 1ll * a[i] * invs[i] % MOD;
			REP(j, i + 1, r) a[j] = (a[j] + 1ll * a[i] * f[j - i]) % MOD;
		}
		return;
	}
	int mid = l + r >> 1;
	cdq(l, mid);
	int len = 1;
	while (len <= r - l + 1) len <<= 1;
	poly A(mid - l + 1), B(r - l + 1);
	REP(i, l, mid)		A[i - l] = a[i];
	REP(i, 0, r - l)	B[i] = f[i];
	NTT(A, len, 1);NTT(B, len, 1);
	REP(i, 0, len - 1) A[i] = 1ll * A[i] * B[i] % MOD;
	NTT(A, len, -1);
	REP(i, mid + 1, r) (a[i] += A[i - l]) %= MOD;
	cdq(mid + 1, r);
}
poly Exp_log2(const poly &f)
{
	int n = deg(f);
	prepare(n);
	::f.resize(n + 1);
	a.clear();a.resize(n + 1);
	REP(i, 0, n) ::f[i] = 1ll * i * f[i] % MOD;
	cdq(0, n);
	return a;
}
namespace work
{
	const int maxn = 2.5e5 + 10, maxq = 1e6 + 10;
	int fac[maxn << 1], Inv[maxn << 1], N;
	void init(int n)
	{
		N = n;
		fac[0] = 1;
		REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;
		Inv[n] = inv(fac[n]);
		DEP(i, n - 1, 0) Inv[i] = Inv[i + 1] * (i + 1ll) % MOD;
	}
	int calc(const poly &f, int x)
	{
		i64 res = 0;
		DEP(i, (int)f.size() - 1, 0) res = (res * x + f[i]) % MOD;
		return res;
	}
	poly Construct_G(poly f, int c) // construct g(x) = f(x + c)
	{
		if (!c || c == MOD) return f;
		static int bin[maxn], ibin[maxn];
		int n = deg(f);f.resize(n + n + 1);
		poly g(n + 1), h(n + n + 1, 0);
		REP(i, 0, n) h[i] = Inv[n - i];
		bin[0] = 1;
		REP(i, 1, n) bin[i] = 1ll * c * bin[i - 1] % MOD;
		ibin[n] = inv(bin[n]);
		DEP(i, n - 1, 0) ibin[i] = 1ll * c * ibin[i + 1] % MOD;
		REP(i, 0, n) f[i] = 1ll * f[i] * fac[i] % MOD * bin[i] % MOD;
		f = f * h;
		REP(i, 0, n) g[i] = 1ll * Inv[i] * ibin[i] % MOD * f[n + i] % MOD;
		return g;
	}
	poly Construct_H(poly g, int k)//h(x) = g(kx)
	{
		int n = deg(g);
		int bk = 1;
		REP(i, 0, n)
		{
			g[i] = 1ll * bk * g[i] % MOD;
			bk = 1ll * bk * k % MOD;
		}
		return g;
	}
	int n, q, q0, a, b, c;
	poly f;
	int bina[maxq + maxn], ibina[maxq + maxn];
	void inita(int n)
	{
		bina[0] = 1;
		REP(i, 1, n) bina[i] = 1ll * a * bina[i - 1] % MOD;
		ibina[n] = inv(bina[n]);
		DEP(i, n - 1, 0) ibina[i] = 1ll * a * ibina[i + 1] % MOD;
	}
	namespace fastpow
	{
		const int w = 31600;
		int s1[w + 5], s2[w + 5];
		int is1[w + 5], is2[w + 5];
		void init()
		{
			s1[0] = 1;
			REP(i, 1, w) s1[i] = 1ll * s1[i - 1] * a % MOD;
			s2[0] = 1;
			REP(i, 1, w) s2[i] = 1ll * s2[i - 1] * s1[w] % MOD;

			const int inva = inv(a);is1[0] = 1;
			REP(i, 1, w) is1[i] = 1ll * is1[i - 1] * inva % MOD;
			const int invs1w = inv(s1[w]);is2[0] = 1;
			REP(i, 1, w) is2[i] = 1ll * is2[i - 1] * invs1w % MOD;
		}
		int powa(int n) {return 1ll * s1[n % w] * s2[n / w] % MOD;}
		int ipowa(int n) {return 1ll * is1[n % w] * is2[n / w] % MOD;}
	}
	inline int ac2(int n) {return fastpow :: powa(n * (n - 1ll) / 2 % (MOD - 1));}
	inline int iac2(int n) {return fastpow :: ipowa(n * (n - 1ll) / 2 % (MOD - 1));}
	int main()
	{
		n = read<int>();q = read<int>();
		f.resize(n + 1);
		REP(i, 0, n) f[i] = read<int>();
		q0 = read<int>();a = read<int>();b = read<int>();
		fastpow :: init();
		init(n + n);
		c = inv(a - 1) * b % MOD;
		(q0 += c) %= MOD;
//		poly g = Construct_G(f, MOD - c);//g(x) = f(x - c)
//		poly h = Construct_H(g, q0);//h(x) = g(q0' x)
		poly h = Construct_H(Construct_G(f, MOD - c), q0);
		inita(q + n);

		poly t(q + n + 1, 0);
		REP(i, 0, q + n) t[i] = ac2(q + n - i);
		poly res(n + 1, 0);
		REP(i, 0, n) res[i] = 1ll * h[i] * iac2(i) % MOD;
		res = res * t;

		int ans = 0;
		REP(i, 1, q) ans ^= 1ll * res[q + n - i] * iac2(i) % MOD;
		cout << ans << endl;
		return 0;
	}
}

int main()
{
#ifdef CraZYali
	file("500");
#endif
	return work :: main();
}
