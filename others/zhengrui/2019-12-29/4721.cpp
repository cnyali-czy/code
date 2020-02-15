/*
	Problem:	4721.cpp
	Time:		2020-02-15 23:07
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
#define i64 long long
using namespace std;
const int maxn = 1 << 19, MOD = 998244353;

inline int add(int x, int y) {register int res = x + y;return res >= MOD ? res - MOD : res;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline int sub(int x, int y) {register int res = x - y;return res <  0   ? res + MOD : res;}
inline int mul(i64 x, int y) {register i64 res = x * y;return res >= MOD ? res % MOD : res;}

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

int R[maxn];
void NTT(int a[], int n, int flag)
{
	REP(i, 1, n - 1)
		if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1; i < n; i <<= 1)
	{
		int wn = power_pow(3, (MOD - 1) / (i << 1));
		if (flag < 0) wn = inv(wn);
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
		const int Invn = inv(n);
		REP(i, 0, n - 1) a[i] = mul(a[i], Invn);
	}
}
void NTT_both(int a[], int b[], int n, int flag)
{
	REP(i, 1, n - 1)
		if (i < R[i]) {swap(a[i], a[R[i]]);swap(b[i], b[R[i]]);}
	for (int i = 1; i < n; i <<= 1)
	{
		int wn = power_pow(3, (MOD - 1) / (i << 1));
		if (flag < 0) wn = inv(wn);
		for (int k = 0; k < n; k += i << 1)
			for (int x, y, l = 0, w = 1; l < i; l++, w = mul(w, wn))
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
		const int Invn = inv(n);
		REP(i, 0, n - 1) a[i] = mul(a[i], Invn), b[i] = mul(b[i], Invn);;
	}
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

int n, l, f[maxn], g[maxn], A[maxn], B[maxn];

void cdqFFT(int l, int r)
{
	if (l == r) return void(f[l] += (!l));
	int mid = l + r >> 1;
	cdqFFT(l, mid);
	
	int L = 1;
	while (L <= r - l + 1) L <<= 1;
//	copy(f + l, f + mid + 1,	A);
//	copy(g, g + r - l + 1,		B);
	REP(i, 0, mid - l)	A[i] = f[i + l];
	REP(i, mid - l + 1, L - 1)	A[i] = 0;
	REP(i, 0, r - l)	B[i] = g[i];
	REP(i, r - l + 1,	L - 1)	B[i] = 0;
	REP(i, 1, L - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? L >> 1 : 0);

	NTT_both(A, B, L, 1);
	REP(i, 0, L - 1) A[i] = mul(A[i], B[i]);
	NTT(A, L, -1);
	REP(i, mid + 1, r) inc(f[i], A[i - l]);

	cdqFFT(mid + 1, r);
}

int main()
{
#ifdef CraZYali
	file("4721");
#endif
	n = read<int>() - 1;
	REP(i, 1, n) g[i] = read<int>();
	cdqFFT(0, n);
	REP(i, 0, n) printf("%d%c", f[i], i == end_i ? '\n' : ' ');
	return 0;
}
