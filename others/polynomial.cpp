/*
	Problem:	polynomial.cpp
	Time:		2020-03-17 15:48
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;

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
unsigned long long very_big, very_shit;
	template <typename T>
inline T read_MOD(int MOD)
{
	very_big = very_shit = 0;
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = MOD - 1;
		c = getchar();
	}
	int ccc = 0;
	while (isdigit(c))
	{
		ccc++;
		ans = ans * 10ll % MOD + c - 48;
		very_shit = very_shit * 10 % (MOD - 1) + c - 48;
		if (ccc <= 10) very_big = very_big * 10 + c - 48;
		c = getchar();
	}
	return (MOD + ans * flag) % MOD;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

#define prime_g 3
#define MOD 998244353
#define inv2 499122177
#define inv3 332748118
inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline int upd(i64 x) {if (x <= -MOD || x >= MOD) x %= MOD;if (x < 0) x += MOD;return x;}
inline int power_pow(i64 base, int b)
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
		inline num operator * (num B) {return num(add(mul(x, B.x), mul(II, mul(y, B.y))), add(mul(x, B.y), mul(y, B.x)));}
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
		int a = MOD - 1;
		while (1)
		{
			II = sub(1ll * a * a % MOD, n);
			if (a && ::power_pow(II, MOD - 1 >> 1) == MOD - 1) break;
			a = hh() % MOD;
		}
		int ans1 = power_pow(num(a, 1), MOD + 1 >> 1).x, ans2 = sub(0, ans1);
		return min(ans1, ans2);
	}
}
namespace polynomial
{
	const int maxn = 1 << 20;
	int R[maxn], lastRN;
	unsigned i64 NTTtmp[maxn];
	void NTT(int a[], int n, int flag)
	{
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
	void Mul(int A[], int n, int B[], int m, int C[]) // deg(A) = n, deg(B) = m
	{
		static int tmpA[maxn], tmpB[maxn];
		int l = 1;
		while (l <= n + m) l <<= 1;
		copy(A, A + n + 1, tmpA);REP(i, n + 1, l - 1) tmpA[i] = 0;
		copy(B, B + m + 1, tmpB);REP(i, m + 1, l - 1) tmpB[i] = 0;
		NTT(tmpA, l, 1);NTT(tmpB, l, 1);
		REP(i, 0, l - 1) C[i] = 1ll * tmpA[i] * tmpB[i] % MOD;
		NTT(C, l, -1);
		REP(i, n + m + 1, l - 1) C[i] = 0;
	}
	void getInv(int A[], int n, int C[]) //deg(A) = n
	{
		static int F[maxn];
		int l = 1;
		while (l <= n) l <<= 1;
		REP(i, 0, l + l - 1) F[i] = C[i] = 0;
		C[0] = inv(A[0]);
		for (int N = 2; N <= l; N <<= 1)
		{
			copy(A, A + N, F);
			NTT(F, N + N, 1);NTT(C, N + N, 1);
			REP(i, 0, N + N - 1) C[i] = C[i] * (2ll + MOD - 1ll * C[i] * F[i] % MOD) % MOD;
			NTT(C, N + N, -1);
			REP(i, N, N + N - 1) C[i] = 0;
		}
		REP(i, n + 1, l - 1) C[i] = 0;
	}
	int invs[maxn], lastinvn = 1;
	void prepare_invs(int n)
	{
		invs[0] = invs[1] = 1;
		REP(i, lastinvn + 1, n)
			invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		chkmax(lastinvn, n);
	}
	void getLn(int A[], int n, int ln[])
	{
		static int df[maxn], Inv[maxn];
		prepare_invs(n);
		REP(i, 0, n - 1) df[i] = A[i + 1] * (i + 1ll) % MOD;df[n] = 0;
		getInv(A, n, Inv);
		int l = 1;
		while (l <= n + n) l <<= 1;
		REP(i, n + 1, l - 1) df[i] = Inv[i] = 0;
		NTT(df, l, 1);NTT(Inv, l, 1);
		REP(i, 0, l - 1) ln[i] = 1ll * df[i] * Inv[i] % MOD;
		NTT(ln, l, -1);
		REP(i, n + 1, l - 1) ln[i] = 0;
		DEP(i, n, 1) ln[i] = 1ll * ln[i - 1] * invs[i] % MOD;
		ln[0] = 0;
	}
	void getExp(int A[], int n, int C[])
	{
		static int F[maxn], ln[maxn];
		int l = 1;
		while (l <= n) l <<= 1;
		REP(i, 0, l + l - 1) C[i] = F[i] = 0;
		C[0] = 1;
		for (int N = 2; N <= l; N <<= 1)
		{
			copy(A, A + N, F);
			getLn(C, N - 1, ln);
			NTT(C, N + N, 1);
			NTT(ln, N + N, 1);
			NTT(F, N + N, 1);
			REP(i, 0, N + N - 1) C[i] = C[i] * (MOD + 1ll - ln[i] + F[i]) % MOD;
			NTT(C, N + N, -1);
			REP(i, N, N + N - 1) C[i] = 0;
		}
		REP(i, n + 1, l - 1) C[i] = 0;
	}
	void cdqExp(int f[], int g[], int l, int r)
	{
		if (r - l + 1 <= 128)
		{
			REP(i, l, r)
			{
				if (!i) g[i] = 1;
				else g[i] = 1ll * g[i] * invs[i] % MOD;
				REP(j, i + 1, r)
					g[j] = (g[j] + 1ll * g[i] * f[j - i]) % MOD;
			}
			return;
		}
		int mid = l + r >> 1;
		cdqExp(f, g, l, mid);
		int L = 1;
		while (L <= r - l + 1) L <<= 1;
		static int A[maxn], B[maxn];
		REP(i, 0, mid - l) A[i] = g[i + l];REP(i, mid - l + 1, L - 1) A[i] = 0;
		REP(i, 0, r - l) B[i] = f[i];REP(i, r - l + 1, L - 1) B[i] = 0;
		NTT(A, L, 1);NTT(B, L, 1);
		REP(i, 0, L - 1) A[i] = 1ll * A[i] * B[i] % MOD;
		NTT(A, L, -1);
		REP(i, mid + 1, r) (g[i] += A[i - l]) %= MOD;
		cdqExp(f, g, mid + 1, r);
	}
	void getExp_log2(int A[], int n, int C[])
	{
		prepare_invs(n);
		static int f[maxn];
		REP(i, 0, n) f[i] = 1ll * i * A[i] % MOD;
		REP(i, 0, n) C[i] = 0;
		cdqExp(f, C, 0, n);
	}
	void pow_simple(int A[], int n, int k, int C[])
	{
		static int B[maxn];
		getLn(A, n, B);
		REP(i, 0, n) B[i] = 1ll * B[i] * k % MOD;
		getExp(B, n, C);
	}
	void pow_simple_log2(int A[], int n, int k, int C[])
	{
		static int B[maxn];
		getLn(A, n, B);
		REP(i, 0, n) B[i] = 1ll * B[i] * k % MOD;
		getExp_log2(B, n, C);
	}
	void getSqrt(int A[], int n, int C[])
	{
		static int F[maxn], Inv[maxn];
		int l = 1;
		while (l <= n) l <<= 1;
		REP(i, 0, l + l - 1) C[i] = F[i] = 0;
		C[0] = (A[0] == 1 ? 1 : Less::solve(A[0]));
		for (int N = 2; N <= l; N <<= 1)
		{
			copy(A, A + N, F);
			getInv(C, N - 1, Inv);
			NTT(F, N + N, 1);
			NTT(Inv, N + N, 1);
			REP(i, 0, N + N - 1) F[i] = 1ll * F[i] * Inv[i] % MOD;
			NTT(F, N + N, -1);
			REP(i, 0, N - 1) C[i] = 1ll * inv2 * (C[i] + F[i]) % MOD;
			REP(i, N, N + N - 1) C[i] = 0;
		}
		REP(i, n + 1, l - 1) C[i] = 0;
	}
	void Divide(int F[], int n, int G[], int m, int D[], int R[])
	{
		static int tF[maxn], tG[maxn], Inv[maxn];
		copy(F, F + 1 + n, tF);reverse(tF, tF + 1 + n);
		copy(G, G + 1 + m, tG);reverse(tG, tG + 1 + m);
		int l = 1;
		while (l <= n - m + n - m) l <<= 1;
		REP(i, m + 1, l - 1) tG[i] = 0;
		REP(i, n - m + 1, l - 1) tF[i] = tG[i] = 0;
		getInv(tG, n - m, Inv);
		NTT(Inv, l, 1);NTT(tF, l, 1);
		REP(i, 0, l - 1) D[i] = 1ll * Inv[i] * tF[i] % MOD;
		NTT(D, l, -1);
		REP(i, n - m + 1, l - 1) D[i] = 0;
		reverse(D, D + n - m + 1);
		l = 1;
		while (l <= n) l <<= 1;
		copy(G, G + 1 + m, tG);REP(i, m + 1, l - 1) tG[i] = 0;
		copy(D, D + 1 + n - m, tF);REP(i, n - m + 1, l - 1) tF[i] = 0;
		NTT(tG, l, 1);NTT(tF, l, 1);
		REP(i, 0, l - 1) tG[i] = 1ll * tG[i] * tF[i] % MOD;
		NTT(tG, l, -1);
		REP(i, 0, m - 1) R[i] = (F[i] - tG[i] + MOD) % MOD;
	}
	void pow(int A[], int n, int k, int C[])
	{
		REP(i, 0, n) C[i] = 0;
		int s = 0;
		while (s <= n && !A[s]) s++;
		if (s == n + 1 || 1ll * s * k > n) return;
		int qaq = A[s], iq = inv(qaq), pw = power_pow(qaq, very_shit);
		REP(i, s, n) A[i] = 1ll * A[i] * iq % MOD;
		pow_simple(A + s, n - s, k, C + s * k);
		REP(i, s * k, n) C[i] = 1ll * C[i] * pw % MOD;
	}
	void pow_log2(int A[], int n, int k, int C[])
	{
		REP(i, 0, n) C[i] = 0;
		int s = 0;
		while (s <= n && !A[s]) s++;
		if (s == n + 1 || 1ll * s * k > n) return;
		int qaq = A[s], iq = inv(qaq), pw = power_pow(qaq, very_shit);
		REP(i, s, n) A[i] = 1ll * A[i] * iq % MOD;
		pow_simple_log2(A + s, n - s, k, C + s * k);
		REP(i, s * k, n) C[i] = 1ll * C[i] * pw % MOD;
	}
	void cdqFFT(int A[], int B[], int l, int r)
	{
		if (l == r)
		{
			if (!l) A[l] = 1;
			return;
		}
		int mid = l + r >> 1;
		int L = 1;
		while (L <= r - l + 1) L <<= 1;
		cdqFFT(A, B, l, mid);
		static int F[maxn], G[maxn];
		REP(i, 0, mid - l) F[i] = A[i + l];
		REP(i, mid - l + 1, L - 1) F[i] = 0;
		REP(i, 0, r - l) G[i] = B[i];
		REP(i, r - l + 1, L - 1) G[i] = 0;
		NTT(F, L, 1);NTT(G, L, 1);
		REP(i, 0, L - 1) F[i] = 1ll * F[i] * G[i] % MOD;
		NTT(F, L, -1);
		REP(i, mid + 1, r) (A[i] += F[i - l]) %= MOD;
		cdqFFT(A, B, mid + 1, r);
	}
	namespace FastCalc
	{
		const int maxn = 1 << 18;
		int A[maxn], B[maxn], *QAQ[maxn], n, m, res[maxn], nowN;
		const int End = 250;
#define ls p << 1
#define rs p << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
		void Init(int p, int l, int r)
		{
			if (l == r)
			{
				QAQ[p] = new int[2];
				QAQ[p][0] = B[l];
				QAQ[p][1] = MOD - 1;
				return;
			}
			int L = 1, mid = l + r >> 1;
			while (L <= r - l + 1) L <<= 1;
			int F[L], G[L];
			Init(lson);Init(rson);
			REP(i, 0, mid - l + 1) F[i] = QAQ[ls][i];
			REP(i, mid - l + 2, L - 1) F[i] = 0;
			REP(i, 0, r - mid) G[i] = QAQ[rs][i];
			REP(i, r - mid + 1, L - 1) G[i] = 0;
			NTT(F, L, 1);NTT(G, L, 1);
			REP(i, 0, L - 1) F[i] = 1ll * F[i] * G[i] % MOD;
			NTT(F, L, -1);
			QAQ[p] = new int[r - l + 2];
			REP(i, 0, r - l + 1) QAQ[p][i] = F[i];
		}
		int calc(int F[], int n, int x)
		{
			int res = 0;
			DEP(i, n, 0) res = (1ll * res * x + F[i]) % MOD;
			return res;
		}
		void Work(int F[], int n, int p, int l, int r)
		{
			if (r - l + 1 <= End)
			{
				REP(i, l, r) res[i] = calc(F, n, B[i]);
//				REP(i, l, r) cout << calc(F, n, B[i]) << '\n';
				return;
			}
			int L = 1;
			while (L <= r - l + 1) L <<= 1;
			int tmp1[L], tmp2[L], mid = l + r >> 1;
			Divide(F, n, QAQ[ls], mid - l + 1, tmp1, tmp2);
			Work(tmp2, mid - l, lson);
			Divide(F, n, QAQ[rs], r - mid, tmp1, tmp2);
			Work(tmp2, r - mid - 1, rson);
		}
		int main()
		{
			n = read<int>();m = read<int>();
			REP(i, 0, n) A[i] = read<int>();
			REP(i, 1, m) B[i] = read<int>();
			Init(1, 1, m);
			Work(A, n, 1, 1, m);
			REP(i, 1, m) printf("%d\n", res[i]);
			return 0;
		}
		int Main(int a[], int nn, int mm)//get 1 ... m
		{
			n = nn;m = mm;
			REP(i, 0, n) A[i] = a[i];
			REP(i, 1, m) B[i] = i;
			Init(1, 1, m);
			Work(A, n, 1, 1, m);
			return 0;
		}
	}
	int linear_recurrence(int f[], int n, int a[], int k)
	{
		static int g[maxn], A[maxn], B[maxn], tmp[maxn], R[maxn];
		int l = 1;
		while (l <= k + k) l <<= 1;
		REP(i, 0, l - 1) g[i] = A[i] = B[i] = 0;
		g[k] = 1;
		REP(i, 0, k - 1) if (a[k - i]) g[i] = MOD - a[k - i];
		B[1] = 1;A[0] = 1;
		while (n)
		{
			if (n & 1)
			{
				copy(B, B + l, tmp);
				//ans *= base
				NTT(A, l, 1);NTT(tmp, l, 1);
				REP(i, 0, l - 1) A[i] = 1ll * A[i] * tmp[i] % MOD;
				NTT(A, l, -1);
				Divide(A, k - 1 + k - 1, g, k, tmp, R);
				REP(i, 0, k) A[i] = R[i];
				if (n == 1) break;
				REP(i, k + 1, l - 1) A[i] = 0;
			}
			//base *= base
			NTT(B, l, 1);
			REP(i, 0, l - 1) B[i] = 1ll * B[i] * B[i] % MOD;
			NTT(B, l, -1);
			Divide(B, k - 1 + k - 1, g, k, tmp, R);
			REP(i, 0, k) B[i] = R[i];
			REP(i, k + 1, l - 1) B[i] = 0;
			n >>= 1;
		}
		int ans = 0;
		REP(i, 0, k - 1) ans = (ans + 1ll * A[i] * f[i]) % MOD;
		return ans;
	}
	int A[maxn], B[maxn], n, m, C[maxn], D[maxn], _R[maxn];
	int main3803()
	{
		n = read<int>();m = read<int>();
		REP(i, 0, n) A[i] = read<int>();
		REP(i, 0, m) B[i] = read<int>();
		Mul(A, n, B, m, C);
		REP(i, 0, n + m) printf("%d%c", C[i], i == n + m ? '\n' : ' ');
		return 0;
	}
	int main4238()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		getInv(A, n, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main4512()
	{
		n = read<int>();m = read<int>();
		REP(i, 0, n) A[i] = read<int>();
		REP(i, 0, m) B[i] = read<int>();
		Divide(A, n, B, m, D, _R);
		REP(i, 0, n - m) printf("%d%c", D[i], i == end_i ? '\n' : ' ');
		REP(i, 0, m - 1) printf("%d%c", _R[i], i == end_i ? '\n' : ' ');
		return 0;
	}
	int main4721()
	{
		n = read<int>() - 1;
		REP(i, 1, n) B[i] = read<int>();
		cdqFFT(A, B, 0, n);
		REP(i, 0, n) printf("%d%c", A[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main4721_faster()
	{
		n = read<int>() - 1;
		REP(i, 1, n) B[i] = MOD - read<int>();
		B[0] = 1;
		getInv(B, n, A);
		REP(i, 0, n) printf("%d%c", A[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main4723()
	{
		n = read<int>();m = read<int>();
		REP(i, 1, m) B[i] = upd(read<int>());
		REP(i, 0, m - 1) A[i] = upd(read<int>());
		cout << linear_recurrence(A, n, B, m) << endl;
		return 0;
	}
	int main4725()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		getLn(A, n, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main4726()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		getExp(A, n, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main4726_log2()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		getExp_log2(A, n, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main5050() {return FastCalc::main();}
	int main5205()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		getSqrt(A, n, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main5205_log2()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		pow_simple_log2(A, n, inv2, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main5245()
	{
		n = read<int>() - 1;m = read_MOD<int>(MOD);
		REP(i, 0, n) A[i] = read<int>();
		pow_simple(A, n, m, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main5273()
	{
		n = read<int>() - 1;m = read_MOD<int>(MOD);
		REP(i, 0, n) A[i] = read<int>();
		if (very_big >= n + 1 && !A[0])
		{
			REP(i, 0, n) printf("0 ");
			return 0;
		}
		pow(A, n, m, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main5277()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		getSqrt(A, n, C);
		REP(i, 0, n) printf("%d%c", C[i], i == n ? '\n' : ' ');
		return 0;
	}
	int main5383()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		FastCalc :: Main(A, n, n);
		FastCalc :: res[0] = A[0];
		prepare_invs(n);
		int I = 1, fac = 1;
		REP(i, 0, n)
		{
			I = 1ll * I * invs[i] % MOD;
			A[i] = 1ll * I * FastCalc :: res[i] % MOD;
			B[i] = ((i & 1) ? MOD - 1ll : 1ll) * I % MOD;
		}
		int len = 1;
		while (len <= n + n) len <<= 1;
		NTT(A, len, 1);NTT(B, len, 1);
		REP(i, 0, len - 1) A[i] = 1ll * A[i] * B[i] % MOD;
		NTT(A, len, -1);
		REP(i, 0, n) printf("%d%c", A[i], i == end_i ? '\n' : ' ');
		return 0;
	}
}

signed main()
{
#ifdef CraZYali
	file("polynomial");
#endif
	return polynomial::main5383();
}
