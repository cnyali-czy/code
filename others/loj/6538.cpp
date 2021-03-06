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
	const int maxn = 1 << 21, MOD = 998244353, Inv2 = MOD + 1 >> 1, Inv3 = (MOD + 1) / 3;
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
	int R[maxn], lastRN, Wn[40], InvWn[40];
	struct __init__
	{
		__init__()
		{
			REP(i, 0, 25)
			{
				Wn[i] = power_pow(3, (MOD - 1) >> i + 1);
				InvWn[i] = inv(Wn[i]);
			}
		}
	}__INIT__;
	void NTT(poly &a, int n, int flag)
	{
		if (a.size() ^ n) a.resize(n);
		if (lastRN ^ n)
		{
			lastRN = n;
			REP(i, 1, n - 1)
				R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
		}
		REP(i, 1, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
		REP(i, 0, n - 1) NTTtmp[i] = a[i];
		for (int i = 1, ccc = 0; i < n; i <<= 1, ccc++)
		{
			const int wn = (flag > 0 ? Wn[ccc] : InvWn[ccc]);
			for (int k = 0; k < n; k += i << 1)
				for (int l = 0, w = 1; l < i; l++, w = 1ll * w * wn % MOD)
				{
					unsigned i64 x(NTTtmp[k + l]), y(w * NTTtmp[k + l + i] % MOD);
					NTTtmp[k + l] = x + y;
					NTTtmp[k + l + i] = x - y + MOD;
				}
		}
		REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
		if (flag < 0)
		{
			const int Invn = inv(n);
			REP(i, 0, n - 1) a[i] = 1ll * a[i] * Invn % MOD;
		}
	}
	inline poly operator + (poly a, poly b)
	{
		if (a.size() < b.size()) swap(a, b);
		REP(i, 0, b.size() - 1)
		{
			a[i] += b[i];
			if (a[i] >= MOD) a[i] -= MOD;
		}
		return a;
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
	int N;
	int main()
	{
		N = read<int>();
		int l = 1;
		while (l <= N) l <<= 1;
		poly A(1, 1);
		for (int n = 2; n <= l; n <<= 1)
		{
//			for (auto i : A) cout << i << ' ' ;cout << endl;
			poly P2(n, 0), P3(n, 0);
			REP(i, 0, (n - 1) / 2) P2[i * 2] = A[i];
			REP(i, 0, (n - 1) / 3) P3[i * 3] = A[i];
			poly tmp = A;
			poly A2(A);
			NTT(A, n + n, 1);
			NTT(A2, n + n, 1);
			REP(i, 0, n + n - 1) A2[i] = 1ll * A[i] * A2[i] % MOD;
			NTT(A2, n + n, -1);
			A2.resize(n);
			poly A3(A2);
			NTT(A3, n + n, 1);
			REP(i, 0, n + n  - 1) A3[i] = 1ll * A[i] * A3[i] % MOD;
			NTT(A3, n + n, -1);
			A = tmp;
//			for (auto i : P2) cout << i << ' ';cout << endl;
//			for (auto i : P3) cout << i << ' ';cout << endl;
//			for (auto i : A2) cout << i << ' ';cout << endl;
//			for (auto i : A3) cout << i << ' ';cout << endl;
			poly Up(n, 0), Dw(n, 0);
			REP(i, 1, n - 1) Up[i] = 2ll * (P3[i - 1] - A3[i - 1] + MOD) % MOD;
			Up[0] = 6;
			REP(i, 1, n - 1) Dw[i] = 3ll * (MOD - P2[i - 1] + MOD - A2[i - 1]) % MOD;
			Dw[0] = 6;
//			for (auto i : Up) cout << i << ' ';cout << endl;
//			for (auto i : Dw) cout << i << ' ';cout << endl;
			A = Up * Inv(Dw);
			A.resize(n);
//			puts("");
		}
#ifdef CraZYali
		for (auto i : A) cout << i << ' ' ;cout << endl;
#endif
		cout << A[N] << endl;
		return 0;
	}
}
int main()
{
#ifdef CraZYali
	file("6538");
#endif
	return polynomial::main();
}
