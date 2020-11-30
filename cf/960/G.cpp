/*
	Problem:	5408.cpp
	Time:		2020-02-19 22:26
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1 << 19;

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

namespace shit_mountain
{
	const int MOD = 998244353;
	typedef long long i64;
	inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
	inline int sub(int x, int y) {register int res = x - y;return res <    0 ? res + MOD : res;}
	inline i64 mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}
	inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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

	int n, a, b;
	int fac[maxn], Inv[maxn];

	struct __init__
	{
		__init__(const int N = maxn - 1)
		{
			fac[0] = 1;
			REP(i, 1, N) fac[i] = mul(fac[i-1], i);
			Inv[N] = inv(fac[N]);
			DEP(i, N - 1, 0) Inv[i] = mul(Inv[i + 1], i + 1);
		}
	}__INIT__;
	inline int C(int n, int m) {return mul(fac[n], mul(Inv[m], Inv[n - m]));}

	int Wn[30], InvWn[30];
	struct ___init___
	{
		___init___()
		{
			REP(i, 0, 29)
			{
				Wn[i] = power_pow(3, (MOD - 1) / (1 << i + 1));
				InvWn[i] = inv(Wn[i]);
			}
		}
	}___INIT___;

	int R[maxn];
	void NTT(int a[], int n, int flag)
	{
		REP(i, 1, n - 1)
			if (i < R[i]) swap(a[i], a[R[i]]);
		for (int ccc = 0, i = 1; i < n; i <<= 1, ccc++)
		{
			int wn = flag > 0 ? Wn[ccc] : InvWn[ccc];
			for (int k = 0; k < n; k += i << 1)
				for (int l = 0, w = 1, x, y; l < i; l++, w = mul(w, wn))
				{
					x = a[k + l], y = mul(w, a[k + l + i]);
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
	void NTT_both(int a[], int b[], int n, int flag)
	{
		REP(i, 1, n - 1)
			if (i < R[i])
			{
				swap(a[i], a[R[i]]);
				swap(b[i], b[R[i]]);
			}
		for (int ccc = 0, i = 1; i < n; i <<= 1, ccc++)
		{
			int wn = flag > 0 ? Wn[ccc] : InvWn[ccc];
			for (int k = 0; k < n; k += i << 1)
				for (int l = 0, w = 1, x, y; l < i; l++, w = mul(w, wn))
				{
					x = a[k + l], y = mul(w, a[k + l + i]);
					a[k + l] = add(x, y);
					a[k + l + i] = sub(x, y);
					x = b[k + l], y = mul(w, b[k + l + i]);
					b[k + l] = add(x, y);
					b[k + l + i] = sub(x, y);
				}
		}
		if (flag < 0)
		{
			const int invn = inv(n);
			REP(i, 0, n - 1) a[i] = mul(a[i], invn), b[i] = mul(b[i], invn);
		}
	}

	int tmp[maxn], bin[maxn];
	void calc(int n, int res[])
	{
		if (n == 1) return void(res[1] = 1);
		if (n & 1)
		{
			calc(n - 1, res);
			copy(res, res + n, tmp);tmp[n] = 0;
			DEP(i, n, 1) res[i] = res[i-1];res[0] = 0;
			REP(i, 0, n) inc(res[i], mul(n - 1, tmp[i]));
			return;
		}
		int L = 1;
		while (L <= n) L <<= 1;
		REP(i, 1, L - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? L >> 1 : 0);
		calc(n >> 1, res);
		REP(i, 0, n >> 1) tmp[i] = mul(fac[i], res[i]);
		REP(i, (n >> 1) + 1, L - 1) tmp[i] = bin[i] = 0;
		bin[0] = 1;
		REP(i, 1, (n >> 1) + 1)
		{
			bin[i] = mul(n >> 1, bin[i-1]);
			bin[i - 1] = mul(bin[i - 1], Inv[i - 1]);
		}
		bin[(n >> 1) + 1] = 0;
		reverse(bin, bin + (n >> 1) + 1);
		NTT_both(bin, tmp, L, 1);
		REP(i, 0, L - 1) tmp[i] = mul(tmp[i], bin[i]);
		NTT(tmp, L, -1);
		REP(i, 0, n >> 1) tmp[i] = mul(Inv[i], tmp[i + (n >> 1)]);
		L <<= 1;
		REP(i, (n >> 1) + 1, L - 1) tmp[i] = 0;
		REP(i, 1, L - 1)
			R[i] = (R[i >> 1] >> 1) | (i & 1 ? L >> 1 : 0);
		NTT_both(tmp, res, L, 1);
		REP(i, 0, L - 1) res[i] = mul(res[i], tmp[i]);
		NTT(res, L, -1);
		REP(i, n + 1, L - 1) res[i] = 0;
	}
}
using shit_mountain :: C;
using shit_mountain :: mul;

int Str[maxn];

int main()
{
#ifdef CraZYali
	file("G");
#endif
	int n = read<int>(), a = read<int>(), b = read<int>();
	if (n == 1)
	{
		printf("%d\n", a == 1 && b == 1);
		return 0;
	}
	shit_mountain::calc(n - 1, Str);
	if (a + b - 2 > n - 1)
	{
		cout << 0 << endl;
		return 0;
	}
	cout << mul(Str[a + b - 2], C(a + b - 2, a - 1)) << endl;
	return 0;
}
