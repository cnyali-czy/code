#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int MOD = 998244353, maxn = 1 << 18, len = maxn;

int power_pow(int base, int b)
{
	int ans(1);
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
const int invN = inv(len);

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int D, n, m;

int R[maxn];
inline void NTT(int a[], int flag)
{
	REP(i, 1, len - 1) if (i < R [ i ]) swap(a[i], a[R[i]]);
	for (int i = 1; i < len; i <<= 1)
	{
		int wn = power_pow(3, (MOD - 1) / (i << 1));
		if (flag < 0) wn = inv(wn);
		for (int k = 0; k < len; k += i << 1)
			for (int l = 0, w = 1; l < i; l++, (w *= wn) %= MOD)
			{
				int x(a[k + l]), y(a[k + l + i] * w % MOD);
				a[k + l] = (x + y) % MOD;
				a[k + l + i] = (x - y) % MOD;
			}
	}
	if (flag < 0) REP(i, 0, len - 1) (a[i] *= invN) %= MOD;
}

int f[maxn], g[maxn];
int fac[maxn], Inv[maxn], bin[maxn];
inline void init()
{
	REP(i, 1, len - 1) R[i] = (R[i >> 1] >> 1) | ((i & 1) << 17);
	fac[0] = 1;
	REP(i, 1, D+D) fac[i] = fac[i-1] * i % MOD;
	Inv[D+D] = inv(fac[D+D]);
	DREP(i, D+D - 1, 0) Inv[i] = Inv[i+1] * (i+1) % MOD;
	bin[0] = 1;
	REP(i, 1, D+D) bin[i] = bin[i-1] * 2 % MOD;
}
inline int C(int n, int m) {return n < m ? 0 : fac[n] * Inv[m] % MOD * Inv[n-m] % MOD;}
inline int F(int d) {return d ? ((n - m - m) & 1 ? -1 : 1) * C(d-1, n - m - m) : 1;}

signed main()
{
#ifdef CraZYali
	freopen("3120.in", "r", stdin);
	freopen("3120.out", "w", stdout);
#endif
	cin >> D >> n >> m;
	init();
	if (n < m + m) cout << 0 << endl;
	else if (D <= (n - m - m + 1)) cout << (power_pow(D, n) + MOD) % MOD << endl;
	else
	{
		REP(i, 0, D) f[i] = power_pow(i + i - D, n) * Inv[D-i] % MOD;
		REP(i, 0, D) g[i] = bin[D-i] * Inv[D-i] % MOD * F(i) % MOD;
#ifdef CraZYali
		FILE* lkakioi = fopen("std.lkakioi", "w");
		REP(i, 0, D) fprintf(lkakioi,"%lld%c", (f[i]+MOD)%MOD, i == D ? '\n' : ' ');
		REP(i, 0, D) fprintf(lkakioi,"%lld%c", (g[i]+MOD)%MOD, i == D ? '\n' : ' ');
#endif
		NTT(f, 1);NTT(g, 1);
		REP(i, 0, len - 1) (f[i] *= g[i]) %= MOD;
		NTT(f, -1);
#ifdef CraZYali
		REP(i, 0, D + D) fprintf(lkakioi,"%lld%c", (f[i] + MOD) % MOD, i == D + D ? '\n' : ' ');
#endif
		int ans(0);
		REP(k, D, D + D) (ans += f[k] * (k & 1 ? -1 : 1) * Inv[k-D] % MOD) %= MOD;
		(ans *= inv(bin[D]) * fac[D] % MOD * (D & 1 ? -1 : 1)) %= MOD;
		cout << (ans + MOD) % MOD << endl;
	}
	return 0;
}
