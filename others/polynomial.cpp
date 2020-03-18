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
#define MOD 998244353
#define inv2 499122177
#define inv3 332748118
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
			II = sub(mul(a, a), n);
			if (a && ::power_pow(II, MOD - 1 >> 1) == MOD - 1) break;
			a = hh() % MOD;
		}
		int ans1 = power_pow(num(a, 1), MOD + 1 >> 1).x, ans2 = sub(0, ans1);
		return min(ans1, ans2);
	}
}
namespace polynomial
{
	const int maxn = 1 << 21;
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
				for (int l = 0, w = 1; l < i2; l++, w = mul(w, wn))
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
			REP(i, 0, n - 1) a[i] = mul(a[i], invn);
		}
	}
	int mul_tmp_A[maxn], mul_tmp_B[maxn];
	void Mul(int A[], int n, int B[], int m, int C[]) // deg(A) = n, deg(B) = m
	{
#define tmpA mul_tmp_A
#define tmpB mul_tmp_B
		int l = 1;
		while (l <= n + m) l <<= 1;
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
			REP(i, 0, N + N - 1) C[i] = mul(C[i], sub(2, mul(C[i], F[i])));
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
		invs[0] = invs[1] = 1;
		REP(i, lastinvn + 1, n) invs[i] = mul(MOD - MOD / i, invs[MOD % i]);
		chkmax(lastinvn, n);
		REP(i, 0, n - 1) df[i] = mul(A[i + 1], i + 1);df[n] = 0;
		getInv(A, n, Inv);
		int l = 1;
		while (l <= n + n) l <<= 1;
		REP(i, n + 1, l - 1) df[i] = Inv[i] = 0;
		NTT(df, l, 1);NTT(Inv, l, 1);
		REP(i, 0, l - 1) ln[i] = mul(df[i], Inv[i]);
		NTT(ln, l, -1);
		REP(i, n + 1, l - 1) ln[i] = 0;
		DEP(i, n, 1) ln[i] = mul(ln[i - 1], invs[i]);ln[0] = 0;
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
			REP(i, 0, N + N - 1) C[i] = mul(C[i], MOD + 1 - sub(ln[i], F[i]));
			NTT(C, N + N, -1);
			REP(i, N, N + N - 1) C[i] = 0;
		}
		REP(i, n + 1, l - 1) C[i] = 0;
#undef F
#undef ln
	}
	int pow_simple_B[maxn];
	void pow_simple(int A[], int n, int k, int C[])
	{
#define B pow_simple_B
		getLn(A, n, B);
		REP(i, 0, n) B[i] = mul(B[i], k);
		getExp(B, n, C);
#undef B
	}
	int getSqrt_F[maxn], getSqrt_Inv[maxn];
	void getSqrt(int A[], int n, int C[])
	{
#define F getSqrt_F
#define Inv getSqrt_Inv
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
			REP(i, 0, N + N - 1) F[i] = mul(F[i], Inv[i]);
			NTT(F, N + N, -1);
			REP(i, 0, N - 1) C[i] = mul(inv2, add(C[i], F[i]));
			REP(i, N, N + N - 1) C[i] = 0;
		}
		REP(i, n + 1, l - 1) C[i] = 0;
#undef F
#undef Inv
	}
	int Divide_tmp_F[maxn], Divide_tmp_G[maxn], Divide_Inv_G[maxn];
	void Divide(int F[], int n, int G[], int m, int D[], int R[])
	{
#define tF Divide_tmp_F
#define tG Divide_tmp_G
#define Inv Divide_Inv_G
		copy(F, F + 1 + n, tF);reverse(tF, tF + 1 + n);
		copy(G, G + 1 + m, tG);reverse(tG, tG + 1 + m);
		int l = 1;
		while (l <= n - m + n - m) l <<= 1;
		REP(i, n - m + 1, l - 1) tF[i] = tG[i] = 0;
		getInv(tG, n - m, Inv);
		NTT(Inv, l, 1);NTT(tF, l, 1);
		REP(i, 0, l - 1) D[i] = mul(Inv[i], tF[i]);
		NTT(D, l, -1);
		REP(i, n - m + 1, l - 1) D[i] = 0;
		reverse(D, D + n - m + 1);
		l = 1;
		while (l <= n) l <<= 1;
		copy(G, G + 1 + m, tG);REP(i, m + 1, l - 1) tG[i] = 0;
		copy(D, D + 1 + n - m, tF);REP(i, n - m + 1, l - 1) tF[i] = 0;
		NTT(tG, l, 1);NTT(tF, l, 1);
		REP(i, 0, l - 1) tG[i] = mul(tG[i], tF[i]);
		NTT(tG, l, -1);
		REP(i, 0, m - 1) R[i] = sub(F[i], tG[i]);
#undef tF
#undef tG
#undef Inv
	}
	void pow(int A[], int n, int k, int C[])
	{
		REP(i, 0, n) C[i] = 0;
		int s = 0;
		while (s <= n && !A[s]) s++;
		if (s == n + 1 || 1ll * s * k > n) return;
		int qaq = A[s], iq = inv(qaq), pw = power_pow(qaq, very_shit);
		REP(i, s, n) A[i] = mul(A[i], iq);
		pow_simple(A + s, n - s, k, C + s * k);
		REP(i, s * k, n) C[i] = mul(C[i], pw);
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
	int main5205()
	{
		n = read<int>() - 1;
		REP(i, 0, n) A[i] = read<int>();
		getSqrt(A, n, C);
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
}

int main()
{
#ifdef CraZYali
	file("polynomial");
#endif
	return polynomial::main5205();
}
