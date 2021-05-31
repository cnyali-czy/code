/*
	Problem:	633.cpp
	Time:		2021-05-29 20:42
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define poly vector <int>
#define i64 long long
#define u64 unsigned i64
using namespace std;
const int MOD = 998244353, orz = 1e7 + 5;

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)
i64 power_pow(i64 base, int b)
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

int fac[orz], invs[orz], Invs[orz];
void init(int n)
{
	fac[0] = invs[0] = Invs[0] = 1;
	fac[1] = invs[1] = Invs[1] = 1;
	REP(i, 2, n)
	{
		fac[i] = 1ll * i * fac[i - 1] % MOD;
		invs[i] = 1ll * (MOD - MOD / i) * invs[MOD % i] % MOD;
		Invs[i] = 1ll * invs[i] * Invs[i - 1] % MOD;
	}
}

inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Invs[m] % MOD * Invs[n - m] % MOD;}
i64 k, n;
inline void reduce(int &x) {x += x >> 31 & MOD;}

namespace Poly
{
	const int maxn = 1 << 21;
	u64 NTTtmp[maxn];
	int R[maxn];
	void NTT(poly &a, int n, int flag, bool NEED = 1)
	{
		if (a.size() ^ n) a.resize(n);
		if (flag < 0) reverse(a.begin() + 1, a.end());
		static int *w[30], pool[maxn << 1 | 10];
		static bool vis[30];
		w[0] = pool;
		REP(i, 0, n - 1)
		{
			R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
			if (i < R[i]) swap(a[i], a[R[i]]);
		}
		REP(i, 0, n - 1) NTTtmp[i] = a[i];
		bool fff = (flag > 0);
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
					u64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % MOD);
					NTTtmp[k + l] = x + y;
					NTTtmp[k + l + i] = MOD + x - y;
				}
		}
		if (!NEED) return;
		REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
		if (flag < 0)
		{
			const int invn = inv(n);
			REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
		}
	}
}

using Poly :: NTT;
inline int deg(const poly &a) {return a.size() - 1;}
inline poly operator * (poly a, poly b)
{
	int l = 1, n = deg(a), m = deg(b);
	while (l <= n + m) l <<= 1;
	NTT(a, l, 1);NTT(b, l, 1);
	REP(i, 0, l - 1) a[i] = 1ll * a[i] * b[i] % MOD;
	NTT(a, l, -1);
	a.resize(n + m + 1);
	return a;
}
namespace bf
{
	const int maxn = 1e5 + 10;
	//	int dp[maxn][maxn][maxn];
	int f[maxn];

	int main()
	{
		init(n);
		/*
		   REP(i, 1, n) dp[k][i][1] = 1;
		   DEP(f, k, 2) REP(lstr, 1, n) REP(lstu, 0, n) if (dp[f][lstr][lstu])
		   REP(r, 1, lstr - 1)
		   {
		   int left = n - r - lstu, u = lstu + 1;
		   REP(i, 0, left / 2)
		   {
		   dp[f - 1][r][u] = (dp[f - 1][r][u] + 1ll * C(left, u - 1 - lstu) * dp[f][lstr][lstu]) % MOD;
		   u += 2;
		   }
		   }
		   cout << dp[1][1][n] << endl;
		   */
		f[0] = 1;
		int len = 1;
		while (len <= n + n) len <<= 1;
		poly A(n + 1, 0);
		REP(i, 0, n / 2) A[i * 2] = Invs[i * 2];
		NTT(A, len, 1);

		REP(_k, 2, k)
		{
			poly B(n + 1, 0);
			REP(i, 1, n) B[i] = 1ll * f[i - 1] * invs[i] % MOD;
			NTT(B, len, 1);
			REP(i, 0, len - 1) B[i] = 1ll * A[i] * B[i] % MOD;
			NTT(B, len, -1);
			REP(i, 0, n) f[i] = B[i];
		}
		cout << 1ll * fac[n - 1] * f[n - 1] % MOD << endl;
		return 0;
	}
}


signed main()
{
#ifdef CraZYali
	file("633");
#endif
	cin >> k >> n;
	return bf :: main();
	return 0;
}
