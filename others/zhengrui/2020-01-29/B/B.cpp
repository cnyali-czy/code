/*
 * File Name:	B.cpp
 * Author	:	CraZYali
 * Time		:	2020.02.05 20:30
 * Email	:	yms-chenziyang@outlook.com
 */

#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a) 
#define chkmin(a, b) (a > (b) ? a = (b) : a) 

#include <algorithm>
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int MOD = 998244353, maxn = 1 << 9, N = maxn, llim = 100 * MOD;

inline int add(int x, int y)
{
	int res = x + y;
	if (res >= MOD) res -= MOD;
	return res;
}
inline void inc(int &x, int y)
{
	(x += y) %= MOD;
}
int sub(int x, int y)
{
	int res = x - y;
	if (res < 0) res += MOD;
	return res;
}
inline int mul(int x, int y)
{
	return 1ll * x * y % MOD;
}
inline int mul(int x, int y, int z)
{
	return 1ll * x * y % MOD * z % MOD;
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
const int Invn = inv(N);
int Wn[40], InvWn[40];
struct __init__
{
	__init__()
	{
		REP(i, 0, 10)
		{
			Wn[i] = power_pow(3, (MOD - 1) / (1 << i + 1));
			InvWn[i] = inv(Wn[i]);
		}
	}
}__INIT__;

int R[maxn];
void NTT(int a[], int flag)
{
	REP(i, 1, N - 1) if (i < R[i]) swap(a[i], a[R[i]]);
	for (int i = 1, ccc = 0; i < N; i <<= 1, ccc++)
	{
		int wn = (flag > 0 ? Wn[ccc] : InvWn[ccc]);
		for (int k = 0; k < N; k += i << 1)
			for (int l = 0, w = 1; l < i; l++, w = mul(w, wn))
			{
				int x = a[k + l], y = mul(w, a[k + l + i]);
				a[k + l] = add(x, y);
				a[k + l + i] = sub(x, y);
			}
	}
	if (flag < 0) REP(i, 0, N - 1) a[i] = mul(a[i], Invn);
}

template <typename T> inline T read()
{
	T ans(0), flag(1);
	char c(getchar());
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

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout);
int f[601][maxn], g[601][maxn];
signed main()
{
#ifdef CraZYali
	file("B");
#endif
	REP(i, 1, N - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
	int n = read<int>();
	g[1][0] = 1;
	NTT(g[1], 1);
	int wn = power_pow(3, (MOD - 1) / N);
	REP(i, 2, n)
		REP(k, 1, i - 1)
		{
			int w = 1;
			REP(j, 0, N - 1)
			{
				inc(f[i][j], mul(g[i-k][j], g[k][j], w));
				inc(f[i][j], mul(f[i-k][j], g[k][j] + f[k][j]));
				inc(g[i][j], mul(g[i-k][j], f[k][j]));
				w = mul(w, wn);
			}
		}
	REP(i, 1, n)
	{
		NTT(f[i], -1);NTT(g[i], -1);
		REP(j, 0, i) printf("%lld ", (f[i][i-j] + g[i][i-j]) % MOD);
		REP(j, i + 1, n) putchar('0'), putchar(' ');
		putchar(10);
	}
	return 0;
}
