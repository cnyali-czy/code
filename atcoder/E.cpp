#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#define int long long
using namespace std;
const int maxn = 3000 + 10;
int n, MOD;

inline int power_pow(int base, int b, const int MOD = ::MOD)
{
	int ans(1);
	while (b)
	{
		if (b & 1) (ans *= base) %= MOD;
		(base *= base) %= MOD;
		b >>= 1;
	}
	return ans;
}
#define inv(x) power_pow(x, MOD - 2)
int fac[maxn], Inv[maxn], s[maxn][maxn];
inline void init(const int MOD = ::MOD)
{
	fac[0] = 1;
	REP(i, 1, n) fac[i] = fac[i-1] * i % MOD;
	Inv[n] = inv(fac[n]);
	DREP(i, n-1, 0) Inv[i] = Inv[i+1] * (i+1) % MOD;
	REP(i, 0, n) s[i][0] = 1;
	REP(i, 1, n)
		REP(j, 1, i)
		s[i][j] = (s[i-1][j] * (j + 1) % MOD + s[i-1][j-1]) % MOD;
}
#define C(n, m) (0 <= m && m <= n ? fac[n] * Inv[m] % mod * Inv[n-m] % mod : 0)
signed main()
{
#ifdef CraZYali
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif
	cin >> n >> MOD;
	const int mod = MOD;
	init();
	int ans = power_pow(2, power_pow(2, n, MOD - 1));
	REP(i, 1, n)
	{
		int f(0);
		REP(j, 0, i)
			(f += s[i][j] * power_pow(power_pow(2, n - i), j) % mod) %= mod;
		(f *= power_pow(2, power_pow(2, n-i, MOD-1))) %= mod;
		(ans += (i & 1? -f : f) * C(n, i) % mod) %= mod;
	}
	cout << (ans % mod + mod) % mod << endl;
	return 0;
}
