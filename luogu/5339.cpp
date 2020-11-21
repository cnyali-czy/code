/*
	Problem:	5339.cpp
	Time:		2020-11-21 23:00
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#define i64 long long
#define ui64 unsigned long long
#define poly vector <int>

using namespace std;
const int maxn = 2000 + 10, MOD = 998244353;

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
inline void init(int n)
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = 1ll * i * fac[i - 1] % MOD;
	Inv[n] = inv(fac[n]);
	DEP(i, n - 1, 0) Inv[i] = (i + 1ll) * Inv[i + 1] % MOD;
}
inline i64 C(int n, int m) {return n < m || m < 0 ? 0 : 1ll * fac[n] * Inv[m] % MOD * Inv[n - m] % MOD;}

void NTT(poly &a, int n, int flag)
{
	const int maxn = 1 << 21;
	static ui64 NTTtmp[maxn];
	static int R[maxn];
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
				ui64 x(NTTtmp[k + l]), y(NTTtmp[k + l + i] * w[ccc][l] % MOD);
				NTTtmp[k + l] = x + y;
				NTTtmp[k + l + i] = MOD + x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = NTTtmp[i] % MOD;
	if (flag < 0)
	{
		const int invn = inv(n);
		REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % MOD;
	}
}
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

i64 calc(int n, int a, int b, int c, int d)
{
	if (n < 0 || a + b + c + d < n) return 0;
	i64 res = 0;
	/*
	REP(i, 0, a) REP(j, 0, b) REP(k, 0, c)
	{
		int l = n - i - j - k;
		if (l < 0 || l > d) continue;
		res = (res + 1ll * fac[n] * Inv[i] % MOD * Inv[j] % MOD * Inv[k] % MOD * Inv[l]) % MOD;
	}
	*/
	poly A(a + 1), B(b + 1), C(c + 1), D(d + 1);
	REP(i, 0, a) A[i] = Inv[i];
	REP(i, 0, b) B[i] = Inv[i];
	REP(i, 0, c) C[i] = Inv[i];
	REP(i, 0, d) D[i] = Inv[i];
	A = A * B;C = C * D;
	A.resize(n + 1);C.resize(n + 1);
	REP(i, 0, n) res = (res + 1ll * A[i] * C[n - i]) % MOD;
	return res * fac[n] % MOD;
}



int n, a, b, c, d, M;
i64 sgn(int x) {return x & 1 ? -1 : 1;}

int f[maxn][maxn];

int main()
{
#ifdef CraZYali
	file("5339");
#endif
	cin >> n >> a >> b >> c >> d;
	M = min(min(a, b), min(c, d));M = min(M, n / 4);
	init(a + b + c + d);
	f[0][0] = 1;
	REP(i, 1, n)
	{
		f[i][0] = 1;
		REP(j, 1, min(i / 4, M)) f[i][j] = (f[i - 1][j] + (i >= 4 ? f[i - 4][j - 1] : 0)) % MOD;
	}
	i64 ans = 0;
	REP(i, 0, M)
		ans = (ans + sgn(i) * f[n][i] * calc(n - 4 * i, a - i, b - i, c - i, d - i)) % MOD;
	ans = (ans % MOD + MOD) % MOD;
	cout << ans << endl;
	return 0;
}
