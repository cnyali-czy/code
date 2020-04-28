#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}
inline int min(int x, int y) {if (x < y) return x;return y;}
namespace polynomial
{
#define poly vector <int>
#define i64 long long
	const int maxn = 1 << 21, MOD = 998244353, Inv2 = MOD + 1 >> 1;
	inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
	inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
	inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
	inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
	inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}
	int power_pow(i64 base, int b)
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
	namespace Less
	{
		int II;
		struct num
		{
			int x, y;
			inline num(int x = 0, int y = 0) : x(x), y(y) {}
			inline num operator * (num B) {return num(add(1ll * x * B.x % MOD, 1ll * II * y % MOD * B.y % MOD), add(1ll * x * B.y % MOD, 1ll * y * B.x % MOD));}
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

		mt19937 hh;
		int solve(int n)
		{
			if (n == 1) return 1;
			int a = MOD - 1;
			while (1)
			{
				II = sub(1ll * a * a % MOD, n);
				if (a && polynomial::power_pow(II, MOD - 1 >> 1) == MOD - 1) break;
				a = hh() % MOD;
			}
			int ans1 = power_pow(num(a, 1), MOD + 1 >> 1).x, ans2 = sub(0, ans1);
			return min(ans1, ans2);
		}
	}

	inline int deg(const poly &A) {return A.size() - 1;}
	unsigned i64 NTTtmp[maxn];
	int R[maxn], lastRN;
	vector <int> w[30][2];
	struct __init__
	{
		__init__()
		{
			REP(i, 0, 19)
			{
				int Wn = power_pow(3, (MOD - 1) / (1 << i + 1));
				int InvWn = inv(Wn);
				i64 w0 = 1, w1 = 1;
				REP(j, 0, (1 << i) - 1)
				{
					w[i][0].emplace_back(w0);(w0 *= Wn) %= MOD;
					w[i][1].emplace_back(w1);(w1 *= InvWn) %= MOD;
				}
			}
		}
	}__INIT__;
	void NTT(poly &a, int n, int flag)
	{
		if (a.size() ^ n) a.resize(n);
		bool fff = (flag > 0);
		if (lastRN ^ n)
		{
			lastRN = n;
			REP(i, 1, n - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
		}
		REP(i, 1, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
		REP(i, 0, n - 1) NTTtmp[i] = a[i];
		for (int ccc = 0, i = 2, i2 = 1; i <= n; i <<= 1, i2 <<= 1, ccc++)
			for (int k = 0; k < n; k += i)
				REP(l, 0, i2 - 1)
				{
					unsigned i64 x(NTTtmp[k + l]), y(1ll * w[ccc][fff][l] * NTTtmp[k + l + i2] % MOD);
					NTTtmp[k + l] = x + y;
					NTTtmp[k + l + i2] = MOD + x - y;
				}
		REP(i, 0, n - 1)
		{
			a[i] = NTTtmp[i] % MOD;
			if (a[i] < 0) a[i] += MOD;
		}
		if (flag < 0)
		{
			const int invn = inv(n);
			REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
		}
	}
	inline poly operator * (poly a, poly b)
	{
		int n(deg(a)), m(deg(b));
		int l = 1;
		while (l <= n + m) l <<= 1;
		NTT(a, l, 1);NTT(b, l, 1);
		REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
		NTT(a, l, -1);
		a.resize(n + m + 1);
		return a;
	}
	inline poly&operator *=(poly&a, poly b)
	{
		int n(deg(a)), m(deg(b));
		int l = 1;
		while (l <= n + m) l <<= 1;
		NTT(a, l, 1);NTT(b, l, 1);
		REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
		NTT(a, l, -1);
		a.resize(n + m + 1);
		return a;
	}
	inline poly Inv(const poly &F)
	{
		poly A(1, inv(F[0]));
		int l = 1, n(deg(F));
		for (int d = 2; d <= n + n; d <<= 1)
		{
			poly H(d, 0);
			REP(i, 0, min(n, d - 1)) H[i] = F[i];
			NTT(H, d + d, 1);
			NTT(A, d + d, 1);
			REP(i, 0, d + d - 1) A[i] = A[i] * (2 + MOD - 1ll * A[i] * H[i] % MOD) % MOD;
			NTT(A, d + d, -1);
			A.resize(d);
		}
		A.resize(n + 1);
		return A;
	}
	int invs[maxn], lastinvn = 1;
	void prepare_invs(int n)
	{
		invs[0] = invs[1] = 1;
		if (n <= lastinvn) return;
		REP(i, lastinvn + 1, n) invs[i] = 1ll * (MOD - invs[MOD % i]) * (MOD / i) % MOD;
	}
	inline poly Der(poly f)
	{
		int n(deg(f));
		REP(i, 0, n - 1) f[i] = (i + 1ll) * f[i + 1] % MOD;
		f.pop_back();
		return f;
	}
	inline poly Int(const poly &f)
	{
		int n(deg(f));
		prepare_invs(n);
		poly res(n + 2);
		res[0] = 0;
		REP(i, 1, n + 1) res[i] = 1ll * f[i-1] * invs[i] % MOD;
		return res;
	}
	poly ln(const poly &f)
	{
		int n(deg(f));
		poly res = Inv(f) * Der(f);
		res.resize(n + 2);
		return Int(res);
	}
	poly Sqrt(const poly &f)
	{
		poly A(1, Less::solve(f[0]));
		int n(deg(f));
		for (int d = 2; d / 2 <= n; d <<= 1)
		{
			poly H(d, 0);
			REP(i, 0, min(n, d - 1)) H[i] = f[i];
			A.resize(d);
			poly tmp = H * Inv(A);
			REP(i, 0, d - 1) A[i] = 1ll * Inv2 * (A[i] + tmp[i]) % MOD;
		}
		A.resize(n + 1);
		return A;
	}
	inline poly operator + (poly a, poly b)
	{
		if (a.size() < b.size()) swap(a, b);
		REP(i, 0, (int)b.size() - 1) inc(a[i], b[i]);
		return a;
	}
	inline poly operator - (poly a, poly b)
	{
		if (a.size() < b.size()) a.resize(b.size());
		REP(i, 0, (int)a.size() - 1) dec(a[i], b[i]);
		return a;
	}
	inline poly operator * (int k, poly a)
	{
		for (auto &i : a) i = 1ll * i * k % MOD;
		return a;
	}
	inline poly operator * (poly a, int k) {return k * a;}
	inline poly operator / (poly a, int k) {return inv(k) * a;}
	void cdqExp(const poly &f, poly &g, int l, int r)
	{
		if (l == r)
		{
			if (l) g[l] = 1ll * g[l] * invs[l] % MOD;
			else g[l] = 1;
			return;
		}
		int mid = l + r >> 1;
		cdqExp(f, g, l, mid);
		int L = 1;
		while (L <= r - l + 1) L <<= 1;
		poly A(L, 0), B(L, 0);
		REP(i, 0, mid - l) A[i] = g[i + l];
		REP(i, 0, r - l - 1) B[i] = f[i];
		NTT(A, L, 1);NTT(B, L, 1);
		REP(i, 0, L - 1) A[i] = 1ll * A[i] * B[i] % MOD;
		NTT(A, L, -1);
		REP(i, mid - l, r - l - 1) inc(g[i + l + 1], A[i]);
		cdqExp(f, g, mid + 1, r); }
	inline poly exp(poly f)
	{
		int n = deg(f);
		prepare_invs(n);
		poly res(n + 1, 0);
		cdqExp(Der(f), res, 0, n);
		return res;
	}
	int n, m;
	poly f, g;
	int main3803()
	{
		n = read<int>();f.resize(n + 1);
		m = read<int>();g.resize(m + 1);
		REP(i, 0, n) f[i] = read<int>();
		REP(i, 0, m) g[i] = read<int>();
		f = f * g;
		REP(i, 0, n + m) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
		return 0;
	}
	int main4238()
	{
		n = read<int>() - 1;f.resize(n + 1);
		REP(i, 0, n) f[i] = read<int>();
		f = Inv(f);
		REP(i, 0, n) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
		return 0;
	}
	int main4725()
	{
		n = read<int>() - 1;f.resize(n + 1);
		REP(i, 0, n) f[i] = read<int>();
		f = ln(f);
		REP(i, 0, n) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
		return 0;
	}
	int main4726()
	{
		n = read<int>() - 1;f.resize(n + 1);
		REP(i, 0, n) f[i] = read<int>();
		f = exp(f);
		REP(i, 0, n) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
		return 0;
	}
	int main5205()
	{
		n = read<int>() - 1;f.resize(n + 1);
		REP(i, 0, n) f[i] = read<int>();
		f = Sqrt(f);
		REP(i, 0, n) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
		return 0;
	}
}
int main()
{
#ifdef CraZYali
	file("polynomial-vec");
#endif
	return polynomial::main4726();
}
