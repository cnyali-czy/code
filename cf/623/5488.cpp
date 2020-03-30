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
#define MOD 1004535809
#define inv2 502267905
#define inv3 334845270
inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline int power_pow(int base, int b)
{
	int ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
namespace polynomial
{
	const int maxn = 1 << 18;
	int R[maxn], Wn[30], Invwn[30], lastRN;
	struct __init__
	{
		__init__()
		{
			REP(i, 0, 29)
			{
				Wn[i] = power_pow(prime_g, (MOD - 1) / (1 << i + 1));
				Invwn[i] = inv(Wn[i]);
			}
		}
	}__INIT__;
	unsigned i64 NTTtmp[maxn];
	void NTT(int a[], int n, int flag)
	{
		if (lastRN ^ n)
		{
			lastRN = n;
			REP(i, 1, n - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
		}
		REP(i, 1, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
		copy(a, a + n, NTTtmp);
		for (int ccc = 0, i = 2, i2 = 1; i <= n; i <<= 1, i2 <<= 1, ccc++)
		{
			const int wn = (flag > 0 ? Wn[ccc] : Invwn[ccc]);
			for (int k = 0; k < n; k += i)
				for (int l = 0, w = 1; l < i2; l++, w = 1ll * w * wn % MOD)
				{
					unsigned i64 x(NTTtmp[k + l]), y(w * NTTtmp[k + l + i2] % MOD);
					NTTtmp[k + l] = x + y;
					NTTtmp[k + l + i2] = MOD + x - y;
				}
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
	int mul_tmp_A[maxn], mul_tmp_B[maxn];
	void Mul(int A[], int n, int B[], int m, int C[]) // deg(A) = n, deg(B) = m
	{
#define tmpA mul_tmp_A
#define tmpB mul_tmp_B
		int l = 1;
		while (l <= n + m) l <<= 1;
		NTT(A, l, 1);NTT(B, l, 1);
		REP(i, 0, l - 1) C[i] = 1ll * A[i] * B[i] % MOD;
		NTT(C, l, -1);return;
		copy(A, A + n + 1, tmpA);REP(i, n + 1, l - 1) mul_tmp_A[i] = 0;
		copy(B, B + m + 1, tmpB);REP(i, m + 1, l - 1) mul_tmp_B[i] = 0;
		NTT(tmpA, l, 1);NTT(tmpB, l, 1);
		REP(i, 0, l - 1) C[i] = mul(tmpA[i], tmpB[i]);
		NTT(C, l, -1);
		REP(i, n + m + 1, l - 1) C[i] = 0;
#undef tmpA
#undef tmpB
	}
	int getInv_F[maxn];
	void getInv(int A[], int n, int C[]) //deg(A) = n
	{
#define F getInv_F
		int l = 1;
		while (l <= n) l <<= 1;
		REP(i, 0, l + l - 1) F[i] = C[i] = 0;
		C[0] = inv(A[0]);
		for (int N = 2; N <= l; N <<= 1)
		{
			copy(A, A + N, F);
			NTT(F, N + N, 1);NTT(C, N + N, 1);
			REP(i, 0, N + N - 1) C[i] = C[i] * (2ll - 1ll * C[i] * F[i] % MOD + MOD) % MOD;
			NTT(C, N + N, -1);
			REP(i, N, N + N - 1) C[i] = 0;
		}
		REP(i, n + 1, l - 1) C[i] = 0;
#undef F
	}
	int getLn_df[maxn], getLn_Inv[maxn], invs[maxn], lastinvn = 1;
	void getLn(int A[], int n, int ln[])
	{
#define df getLn_df
#define Inv getLn_Inv
		REP(i, 0, n - 1) df[i] = mul(A[i + 1], i + 1);df[n] = 0;
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
#undef df
#undef Inv
	}
	int getExp_tmp_F[maxn], getExp_tmp_ln[maxn];
	void getExp(int A[], int n, int C[])
	{
#define F getExp_tmp_F
#define ln getExp_tmp_ln
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
#undef F
#undef ln
	}
}
using polynomial::maxn;
using polynomial::lastinvn;
using polynomial::invs;
int n, a[maxn], b[maxn], c[maxn], ans[maxn], k, t;

int main()
{
#ifdef CraZYali
	file("5488");
#endif
	n = read<int>() - 1;k = read_MOD<int>(MOD); t = read<int>();
	REP(i, 0, n) a[i] = read<int>();
	b[1] = 1;
	invs[0] = invs[1] = 1;
	lastinvn = n;
	REP(i, 2, n)
		invs[i] = b[i] = 1ll * (MOD - MOD / i) * b[MOD % i] % MOD;
	if (t) REP(i, 1, n) b[i] = MOD - b[i];
	REP(i, 0, n) b[i] = mul(b[i], k);
	polynomial::getExp(b, n, c);
	polynomial::Mul(a, n, c, n, ans);
	REP(i, 0, n) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
