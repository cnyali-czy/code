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
#define poly vector <int>
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

#define prime_g 3
#define MOD 998244353
#define inv2 499122177
#define inv3 332748118
inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline int upd(i64 x) {if (x <= -MOD || x >= MOD) x %= MOD;if (x < 0) x += MOD;return x;}
inline i64 power_pow(i64 base, int b)
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
namespace polynomial
{
	const int maxn = 1 << 18;
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
	namespace FastCalc1
	{
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
		int Main(int a[], int nn, int b[], int mm)//get 1 ... m
		{
			n = nn;m = mm;
			REP(i, 0, n) A[i] = a[i];
			REP(i, 1, m) B[i] = b[i];
			Init(1, 1, m);
			Work(A, n, 1, 1, m);
			return 0;
		}
	}
	namespace FastCalc2
	{
		int A[maxn], B[maxn], *QAQ[maxn], n, m, res[maxn], nowN;
		const int End = 250;
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
		int Main(int a[], int nn, int b[], int mm)//get 1 ... m
		{
			n = nn;m = mm;
			REP(i, 0, n) A[i] = a[i];
			REP(i, 1, m) B[i] = b[i];
			Init(1, 1, m);
			Work(A, n, 1, 1, m);
			return 0;
		}
	}
	void NTT(poly &f, int n, int flag)
	{
		if (f.size() ^ n) f.resize(n);
		static int tmp[maxn];
		REP(i, 0, n - 1) tmp[i] = f[i];
		NTT(tmp, n, flag);
		REP(i, 0, n - 1) f[i] = tmp[i];
	}
	int deg(const poly &f) {return (int)f.size() - 1;}
	poly operator * (poly A, poly B)
	{
		int n(deg(A)), m(deg(B));
		int len = 1;
		while (len <= n + m) len <<= 1;
		NTT(A, len, 1);NTT(B, len, 1);
		REP(i, 0, len - 1) A[i] = 1ll * A[i] * B[i] % MOD;
		NTT(A, len, -1);
		A.resize(n + m + 1);
		return A;
	}
	poly der(const poly& f)
	{
		int n = deg(f);
		poly g(n, 0);
		REP(i, 0, n - 1) 
			g[i] = (i + 1ll) * f[i + 1] % MOD;
		return g;
	}
	namespace real
	{
		int A[maxn], iA[maxn], C[maxn], DP[maxn];
		poly cdq(int l, int r)
		{
			if (l == r)
			{
				poly res(2, 0);
				res[0] = 1;
				res[1] = MOD - A[l];
				return res;
			}
			int mid = l + r >> 1;
			return cdq(l, mid) * cdq(mid + 1, r);
		}
		int main()
		{
			int n = read<int>() - 1;
			static int pre[maxn];
			REP(i, 0, n)
			{
				A[i] = read<int>();
				pre[i] = 1ll * (i ? pre[i - 1] : 1) * A[i] % MOD;
			}
			iA[n] = inv(pre[n]);
			DEP(i, n - 1, 0)
				iA[i] = 1ll * iA[i + 1] * A[i + 1] % MOD;
			REP(i, 1, n)
				iA[i] = 1ll * pre[i - 1] * iA[i] % MOD;
			poly c(n + 1), P = cdq(0, n);
			REP(i, 0, n)
				c[i] = read<int>();
			c = c * P;
			c.resize(n + 1);
			REP(i, 0, n) C[i] = c[i];
			poly dP = der(P);
			REP(i, 0, n) DP[i] = dP[i];
			FastCalc1 :: Main(C, n, iA - 1, n + 1);
			FastCalc2 :: Main(DP,n, iA - 1, n + 1);
			REP(i, 0, n)
			{
				int LHS = FastCalc1 :: res[i + 1];
				int RHS = 1ll * FastCalc2 :: res[i + 1] * (MOD - iA[i]) % MOD;
				printf("%lld%c", LHS * inv(RHS) % MOD, i == end_i ? '\n' : ' ');
			}
			return 0;
		}
	}

}

signed main()
{
#ifdef CraZYali
	file("A");
#endif
	return polynomial :: real :: main();
}
