/*
	Problem:	B.cpp
	Time:		2020-02-19 13:18
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <cstring>
#include <ctime>
#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1e7 + 1e5 + 10, maxm = 1e5 + 10, MOD = 998244353, maxk = 1e5 + 10;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}

int power_pow(i64 base, int b)
{
	i64 ans = 1;
	while (b)
	{
		if (b & 1) ans = mul(ans, base);
		base = mul(base, base);
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
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int fac[maxn], Inv[maxn];
struct __init__
{
	__init__(const int N = 1e7 + 1e5)
	{
		fac[0] = 1;
		REP(i, 1, N) fac[i] = mul(fac[i-1], i);
		Inv[N] = inv(fac[N]);
		DEP(i, N - 1, 0) Inv[i] = mul(Inv[i + 1], i + 1);
	}
}__INIT__;
inline int C(int n, int m) {return n < m || m < 0 ? 0 : mul(fac[n], mul(Inv[m], Inv[n - m]));}

int n, m, k[maxm];

const int L = 1 << 20;
namespace poly
{
	int R[L];
	void NTT(int *a, int n, int flag)
	{
		REP(i, 1, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		for (int i = 1; i < n; i <<= 1)
		{
			int wn = power_pow(3, (MOD - 1) / (i << 1));
			if (flag < 0) wn = inv(wn);
			for (int k = 0; k < n; k += i << 1)
				for (int w = 1, l = 0; l < i; l++, w = mul(w, wn))
				{
					int x = a[k + l], y = mul(w, a[k + l + i]);
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
	int ans[maxn], f[maxn];
}
using poly::ans;
using poly::f;
using poly::NTT;
int *Str[400], A[L], B[L], id[maxk], Id;

void cdq(int l, int r, int res[])
{
	if (l == r)
	{
		int k = ::k[l];
		if (!id[k])
		{
			id[k] = ++Id;
			int L = 1;
			while (L <= k + k) L <<= 1;
			Str[Id] = new int[L];
			REP(j, 0, L - 1) Str[Id][j] = 0;
			if (!k) Str[Id][0] = 1;
			else
			{
				REP(j, 0, L - 1) A[j] = B[j] = 0;
				REP(j, 0, k)	A[j] = mul(j & 1 ? MOD - 1 : 1, Inv[j]);
				REP(j, 0, k)	B[j] = mul(power_pow(j, k), Inv[j]);
				NTT(A, L, 1);NTT(B, L, 1);
				REP(j, 0, L - 1) Str[Id][j] = mul(A[j], B[j]);
				NTT(Str[Id], L, -1);
			}
		}
		REP(i, 0, k) res[i] = mul(fac[i], Str[id[k]][i]);
		return;
	}
	int mid = l + r >> 1;
	int sk = 0;
	REP(i, l, r) sk += k[i];
	int L = 1;
	while (L <= sk + sk) L <<= 1;
	int tmp1[L], tmp2[L];
	REP(i, 0, L - 1) tmp1[i] = tmp2[i] = 0;
	cdq(l, mid, tmp1);cdq(mid + 1, r, tmp2);

	NTT(tmp1, L, 1);NTT(tmp2, L, 1);
	REP(i, 0, L - 1) res[i] = mul(tmp1[i], tmp2[i]);
	NTT(res, L, -1);
	REP(i, sk + 1, L - 1) res[i] = 0;
}

int main()
{
#ifdef CraZYali
	file("B");
#endif
	m = read<int>();n = read<int>();
	int s = 0;
	REP(i, 1, m) s += (k[i] = read<int>());
	cdq(1, m, ans);
	int Res = 0;
	REP(i, 0, s) Res = add(Res, mul(C(n + m - 1, n - i), ans[i]));
	cout << Res << endl;
	cerr << clock() * 1. / CLOCKS_PER_SEC << endl;
	return 0;
}
