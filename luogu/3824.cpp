#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int MOD = 998244353, maxn = 1000 + 10, maxk = 1000 + 10;
#define i64 long long
inline int add(int x, int y) {return (x += y) >= MOD ? x - MOD : x;}
inline int sub(int x, int y) {return (x -= y) <    0 ? x + MOD : x;}
inline void inc(int &x, int y) {x += y;if (x >= MOD) x -= MOD;}
inline void dec(int &x, int y) {x -= y;if (x <    0) x += MOD;}

template <typename T> T read()
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

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int n, k, N, x, y, p, bin[maxn];
int dp[maxn][maxn];
int power_pow(i64 base, int b)
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

namespace polynomial
{
	const int maxn = 1 << 20;
	int R[maxn], lastRN;
	vector <int> w[30][2];
	struct __init__
	{
		__init__()
		{
			REP(i, 0, 18)
			{
				int Wn = power_pow(3, (MOD - 1) / (1 << i + 1));
				int InvWn = inv(Wn);
				i64 w0 = 1, w1 = 1;
				REP(j, 0, (1 << i) - 1)
				{
					w[i][0].emplace_back(w0);(w0 *= Wn) %= MOD;
					w[i][1].emplace_back(w1);(w1 *= InvWn) %= MOD;
				}
			}
		}
	}__INIT__;
	unsigned i64 NTTtmp[maxn];
	void NTT(int a[], int n, int flag)
	{
		bool fff = (flag > 0);
		if (lastRN ^ n)
		{
			lastRN = n;
			REP(i, 1, n - 1) R[i] = (R[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);
		}
		REP(i, 1, n - 1) if (i < R[i]) swap(a[i], a[R[i]]);
		copy(a, a + n, NTTtmp);
		for (int ccc = 0, i = 2, i2 = 1; i <= n; i <<= 1, i2 <<= 1, ccc++)
			for (int k = 0; k < n; k += i)
				REP(l, 0, i2 - 1)
				{
					unsigned i64 x(NTTtmp[k + l]), y(1ll * w[ccc][fff][l] * NTTtmp[k + l + i2] % MOD);
					NTTtmp[k + l] = x + y;
					NTTtmp[k + l + i2] = MOD + x - y;
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
	void getInv(int A[], int n, int C[]) //deg(A) = n
	{
		static int F[maxn];
		int l = 1;
		while (l <= n) l <<= 1;
		REP(i, 0, l + l - 1) F[i] = C[i] = 0;
		C[0] = inv(A[0]);
		for (int N = 2; N <= l; N <<= 1)
		{
			copy(A, A + N, F);
			NTT(F, N + N, 1);NTT(C, N + N, 1);
			REP(i, 0, N + N - 1) C[i] = C[i] * (2ll + MOD - 1ll * C[i] * F[i] % MOD) % MOD;
			NTT(C, N + N, -1);
			REP(i, N, N + N - 1) C[i] = 0;
		}
		REP(i, n + 1, l - 1) C[i] = 0;
	}
	void Divide(int F[], int n, int G[], int m, int D[], int R[])
	{
		static int tF[maxn], tG[maxn], Inv[maxn];
		copy(F, F + 1 + n, tF);reverse(tF, tF + 1 + n);
		copy(G, G + 1 + m, tG);reverse(tG, tG + 1 + m);
		int l = 1;
		while (l <= n - m + n - m) l <<= 1;
		REP(i, n - m + 1, l - 1) tF[i] = tG[i] = 0;
		getInv(tG, n - m, Inv);
		NTT(Inv, l, 1);NTT(tF, l, 1);
		REP(i, 0, l - 1) D[i] = 1ll * Inv[i] * tF[i] % MOD;
		NTT(D, l, -1);
		REP(i, n - m + 1, l - 1) D[i] = 0;
		reverse(D, D + n - m + 1);
		l = 1;
		while (l <= n) l <<= 1;
		copy(G, G + 1 + m, tG);REP(i, m + 1, l - 1) tG[i] = 0;
		copy(D, D + 1 + n - m, tF);REP(i, n - m + 1, l - 1) tF[i] = 0;
		NTT(tG, l, 1);NTT(tF, l, 1);
		REP(i, 0, l - 1) tG[i] = 1ll * tG[i] * tF[i] % MOD;
		NTT(tG, l, -1);
		REP(i, 0, m - 1) R[i] = sub(F[i], tG[i]);
	}
	int linear_recurrence(int f[], int n, int a[], int k)
	{
		static int g[maxn], A[maxn], B[maxn], tmp[maxn], R[maxn];
		int l = 1;
		while (l <= k + k) l <<= 1;
		REP(i, 0, l - 1) g[i] = A[i] = B[i] = 0;
		g[k] = 1;
		REP(i, 0, k - 1) if (a[k - i]) g[i] = MOD - a[k - i];
		B[1] = 1;A[0] = 1;
		while (n)
		{
			if (n & 1)
			{
				copy(B, B + l, tmp);
				//ans *= base
				NTT(A, l, 1);NTT(tmp, l, 1);
				REP(i, 0, l - 1) A[i] = 1ll * A[i] * tmp[i] % MOD;
				NTT(A, l, -1);
				Divide(A, k - 1 + k - 1, g, k, tmp, R);
				REP(i, 0, k) A[i] = R[i];
				if (n == 1) break;
				REP(i, k + 1, l - 1) A[i] = 0;
			}
			//base *= base
			NTT(B, l, 1);
			REP(i, 0, l - 1) B[i] = 1ll * B[i] * B[i] % MOD;
			NTT(B, l, -1);
			Divide(B, k - 1 + k - 1, g, k, tmp, R);
			REP(i, 0, k) B[i] = R[i];
			REP(i, k + 1, l - 1) B[i] = 0;
			n >>= 1;
		}
		int ans = 0;
		REP(i, 0, k - 1) inc(ans, 1ll * A[i] * f[i] % MOD);
		return ans;
	}
}

int f[maxn], g[maxn];

int solve(int k)
{
	memset(dp, 0, sizeof dp);
	REP(i, 0, maxn - 1) dp[0][i] = 1;
	DEP(j, k, 0)
		REP(i, 1, j ? (k - 1) / j: k) 
		{
			dp[i][j] = 1ll * bin[i] * dp[i][j + 1] % MOD;
			REP(k, 0, i - 1)
				inc(dp[i][j], 1ll * bin[k] * dp[k][j + 1] % MOD * (MOD + 1 - p) % MOD * dp[i - k - 1][j] % MOD);
		}
	REP(i, 1, k + 1) g[i] = (MOD + 1ll - p) * bin[i - 1] % MOD * dp[i - 1][1] % MOD;
	memset(f, 0, sizeof f);
	REP(i, 0, k) f[i] = dp[i][0];
	return polynomial :: linear_recurrence(f, n, g, k + 1);
}

int main()
{
#ifdef CraZYali
	file("3824");
#endif
	n = read<int>();k = read<int>();x = read<int>();y = read<int>();
	N = max(n, k);
	p = 1ll * x * inv(y) % MOD;
	bin[0] = 1;
	REP(i, 1, k) bin[i] = bin[i - 1] * 1ll * p % MOD;
	cout << sub(solve(k + 1), solve(k)) << endl;
	return 0;
}
