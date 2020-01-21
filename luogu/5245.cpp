/*
 * File Name:	5245.cpp
 * Author	:	CraZYali
 * Time		:	2020.01.19 16:11
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <random>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 1 << 22, MOD = 998244353, inv2 = MOD + 1 >> 1;

int add() {return 0;}
	template <typename ...T>
int add(int x, T... y)
{
	int res = x + add(y...);
	if (res >= MOD) res -= MOD;
	return res;
}

int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}

int mul() {return 1;}
	template <typename ...T>
int mul(int x, T... y)
{
	long long res = (long long)x * mul(y...);
	if (res >= MOD) res %= MOD;
	return res;
}

int power_pow(int base, int b)
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
		inline num operator * (num B) {return num(add(mul(x, B.x), mul(II, y, B.y)), add(mul(x, B.y), mul(y, B.x)));}
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
namespace poly
{
	int wn[40], invwn[30];
	struct __init__
	{
		__init__()
		{
			REP(i, 0, 29)
			{
				wn[i] = power_pow(3, (MOD - 1) / (1 << i + 1));
				invwn[i] = inv(wn[i]);
			}
		}
	}__INIT__;
	int R[maxn];
	void NTT(int a[], int n, int flag)
	{
		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		for (int i = 1, ccc = 0; i < n; i <<= 1, ccc++)
		{
			int wn = (flag > 0 ? poly::wn[ccc] : invwn[ccc]);
			for (int k = 0; k < n; k += i << 1)
				for (int l = 0, w = 1; l < i; l++, w = mul(w, wn))
				{
					int x(a[k + l]), y(mul(w, a[k + l + i]));
					a[k + l] = add(x, y);
					a[k + l + i] = sub(x, y);
				}
		}
		if (flag < 0)
		{
			const int invn = inv(n);
			REP(i, 0, n - 1) a[i] = mul(a[i], invn);
		}
	}
	
	int tmp[maxn];
	void getInv(int F[], int A[], int n) // mod x ^ n
	{
		if (n == 1) return void(A[0] = inv(F[0]));
		getInv(F, A, n >> 1);
		copy(F, F + n, tmp);
		REP(i, n, n + n - 1) tmp[i] = 0 ;
		NTT(tmp, n + n, 1);
		NTT(A, n + n, 1);
		REP(i, 0, n + n - 1) A[i] = mul(A[i], sub(2, mul(A[i], tmp[i])));
		NTT(A, n + n, -1);
		REP(i, n, n + n - 1) tmp[i] = A[i] = 0;
	}
	int df[maxn], invf[maxn];
	void getLn(int F[], int ln[], int n) // deg(F) = n
	{
		int l = 1;
		while (l <= n + n) l <<= 1;
		REP(i, 0, l - 1) invf[i] =0 ;
		REP(i, n + 1, l - 1) F[i] = df[i] = 0;
		df[n] = 0;
		REP(i, 0, n - 1) df[i] = mul(i + 1, F[i + 1]);
		getInv(F, invf, l >> 1);
		NTT(invf, l, 1);
		NTT(df, l, 1);
		REP(i, 0, l - 1) ln[i] = mul(df[i], invf[i]);
		NTT(ln, l, -1);
		DEP(i, n, 1) ln[i] = mul(ln[i-1], inv(i));
		ln[0] = 0;
	}
	int Expln[maxn], ExpF[maxn];
	void getExp(int F[], int A[], int n) // mod x ^ n
	{
		if (n == 1) return void(A[0] = 1);
		getExp(F, A, n >> 1);
		getLn(A, Expln, n / 2 + 1);
		REP(i, n / 2 + 1, n - 1) Expln[i] = 0;
		copy(F, F + n, ExpF);
		NTT(A, n + n, 1);
		NTT(ExpF, n + n, 1);
		NTT(Expln, n + n, 1);
		REP(i, 0, n + n - 1) A[i] = sub(A[i], mul(A[i], sub(Expln[i], ExpF[i])));
		//REP(i, 0, n + n - 1) A[i] = sub(A[i], mul(A[i], sub(Expln[i], ExpF[i])));
		NTT(A, n + n, -1);
		REP(i, n, n + n - 1) A[i] = Expln[i] = ExpF[i] = 0;
	}
	int sqrtinv[maxn], sqrttmp[maxn];
	void getSqrt(int F[], int A[], int n)
	{
		if (n == 1) return void(A[0] = Less::solve(F[0]));
		getSqrt(F, A, n >> 1);
		copy(F, F + n, sqrttmp);
		REP(i, 0, n - 1) sqrtinv[i] = 0;
		getInv(A, sqrtinv, n);
		NTT(sqrtinv, n + n, 1);
		NTT(A, n + n, 1);
		NTT(sqrttmp, n + n, 1);
		REP(i, 0, n + n - 1) A[i] = mul(add(mul(A[i], A[i]), sqrttmp[i]), inv2, sqrtinv[i]);
		NTT(A, n + n, -1);
		REP(i, n, n + n - 1) sqrtinv[i] = sqrttmp[i] = A[i] = 0;
	}
}

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = MOD - 1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = add(sub(c, 48), mul(ans, 10));
		c = getchar();
	}
	return mul(ans, flag);
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);

int n, F[maxn], ln[maxn], Exp[maxn];

int main()
{
#ifdef CraZYali
	file("5245");
#endif
	n = read<int>() - 1;
	int k = read<int>();
	int l = 1;while (l <= n + n) l <<= 1;
	REP(i, 0, n) F[i] = read<int>();
	poly::getLn(F, ln, n);
	REP(i, 0, n) ln[i] = mul(ln[i], k);
	poly::getExp(ln, Exp, l);
//	x = Less::solve(x);
//	REP(i, 0, n) Exp[i] = mul(Exp[i], x);

	REP(i, 0, n) printf("%d%c", Exp[i], i == n ? '\n' : ' ');
	return 0;
}
