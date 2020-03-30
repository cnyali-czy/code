/*
	Problem:	4389.cpp
	Time:		2020-03-17 19:54
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
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
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
	int invs[maxn], lastinvn = 1;
	void prepare_invs(int n)
	{
		invs[0] = invs[1] = 1;
		REP(i, lastinvn + 1, n)
			invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		chkmax(lastinvn, n);
	}
	void cdqExp(int f[], int g[], int l, int r)
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
		static int A[maxn], B[maxn];
		REP(i, 0, mid - l) A[i] = g[i + l];REP(i, mid - l + 1, L - 1) A[i] = 0;
		REP(i, 0, r - l - 1) B[i] = f[i];REP(i, r - l, L - 1) B[i] = 0;
		NTT(A, L, 1);NTT(B, L, 1);
		REP(i, 0, L - 1) A[i] = 1ll * A[i] * B[i] % MOD;
		NTT(A, L, -1);
		REP(i, mid - l, r - l - 1) inc(g[i + l + 1], A[i]);
		cdqExp(f, g, mid + 1, r);
	}
	void getExp_log2(int A[], int n, int C[])
	{
		prepare_invs(n);
		static int f[maxn];
		REP(i, 0, n - 1) f[i] = (i + 1ll) * A[i + 1] % MOD;
		REP(i, 0, n) C[i] = 0;
		cdqExp(f, C, 0, n);
	}
}
using polynomial::invs;
using polynomial::maxn;

int Exp[maxn], f[maxn], cnt[maxn], n, m;

int main()
{
#ifdef CraZYali
	file("4389");
#endif
	n = read<int>();m = read<int>();
	while (n--) cnt[read<int>()]++;
	polynomial::prepare_invs(m);
	REP(i, 1, m) if (cnt[i])
		REP(j, 1, m / i) inc(f[i * j], 1ll * cnt[i] * invs[j] % MOD);
	polynomial::getExp_log2(f, m, Exp);
	REP(i, 1, m) cout << Exp[i] << '\n';
	return 0;
}
