/*
	Problem:	4091.cpp
	Time:		2020-03-19 14:56
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <iostream>
#include <cstdio>
#define i64 long long
using namespace std;
const int maxn = 1 << 20, MOD = 998244353;

inline int add(int x, int y) {x += y;return x >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {x -= y;return x <    0 ? x + MOD : x;}
inline i64 mul(i64 x, int y) {x *= y;return x >= MOD ? x % MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}

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

unsigned i64 NTTtmp[maxn];
int R[maxn], lastRN, Wn[40], Invwn[40];
struct __init__
{
	__init__()
	{
		REP(i, 0, 25)
		{
			Wn[i] = power_pow(3, MOD - 1 >> i + 1);
			Invwn[i] = inv(Wn[i]);
		}
	}
}__INIT__;
void NTT(int a[], int n, int flag)
{
	if (lastRN ^ n)
	{
		lastRN = n;
		REP(i, 1, n - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
	}
	REP(i, 0, n - 1)
	{
		if (i < R[i]) swap(a[i], a[R[i]]);
		NTTtmp[i] = a[i];
	}
	for (int i = 2, i2 = 1, ccc = 0; i <= n; i <<= 1, i2 <<= 1, ccc++)
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
		const int Invn = inv(n);
		REP(i, 0, n - 1) a[i] = mul(a[i], Invn);
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

int n, f[maxn], g[maxn], Inv[maxn];

int main()
{
#ifdef CraZYali
	file("4091");
#endif
	n = read<int>();
	Inv[0] = Inv[1] = 1;
	REP(i, 2, n) Inv[i] = mul(MOD - MOD / i, Inv[MOD % i]);
	int lst = 1;
	REP(i, 0, n)
	{
		int tmp = Inv[i];
		if (i) Inv[i] = 1ll * Inv[i] * Inv[i - 1] % MOD;
		f[i] = i & 1 ? MOD - Inv[i] : Inv[i];
		if (i > 1) g[i] = (power_pow(i, n + 1) - 1ll) % MOD * Inv[i] % MOD * lst % MOD;
		lst = tmp;
	}
	g[0] = 1;g[1] = n + 1;
	int l = 1;
	while (l <= n + n) l <<= 1;
#ifdef CraZYali
	REP(i, 0, n) printf("%d%c", f[i], i == n ? '\n' : ' ');
	REP(i, 0, n) printf("%d%c", g[i], i == n ? '\n' : ' ');
#endif
	NTT(f, l, 1);NTT(g, l, 1);
	REP(i, 0, l - 1) f[i] = 1ll * f[i] * g[i] % MOD;
	NTT(f, l, -1);
#ifdef CraZYali
	REP(i, 0, n) printf("%d%c", f[i], i == n ? '\n' : ' ');
#endif
	int ccc = 1, ans = 0;
	REP(i, 0, n)
	{
		inc(ans, 1ll * ccc % MOD * f[i] % MOD);
		ccc = (i + 1ll) * 2 * ccc % MOD;
	}
	cout << ans << '\n';
	return 0;
}
