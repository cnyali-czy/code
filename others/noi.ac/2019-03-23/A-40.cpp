#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstdio>

#define int long long

using namespace std;
const int maxn = 1e6 + 10, MOD = 998244353;

int power_pow(int a, int b)
{
	int ans(1), base(a);
	while (b)
	{
		if (b & 1) ans = ans * base % MOD;
		base = base * base % MOD;
		b >>= 1;
	}
	return (ans + MOD) % MOD;
}
#define inv(x) power_pow(x, MOD - 2)

int n, k, T, ans;

int fac[maxn], Inv[maxn];
int C(int n, int m) {return fac[n] * Inv[m] % MOD * Inv[n-m] % MOD;}

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	cin >> n >> k >> T;
	if (T == 1) {cout << 1 << endl;return 0;}
	fac[0] = 1;
	REP(i, 1, n) fac[i] = fac[i-1] * i % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n - 1, 0) Inv[i] = Inv[i+1] * (i + 1) % MOD;

	REP(Min, 1, n - k + 1) ans = (ans + power_pow(T, Min) * C(n - Min, k-1) % MOD ) % MOD;
	cout << (ans * inv(C(n, k)) % MOD + MOD) % MOD << endl;
	return 0;
}
